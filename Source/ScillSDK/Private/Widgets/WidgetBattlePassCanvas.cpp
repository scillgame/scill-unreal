// Copyright Epic Games, Inc. All Rights Reserved.

#include "Widgets/WidgetBattlePassCanvas.h"
#include "Misc/DateTime.h"

UWidgetBattlePassCanvas::UWidgetBattlePassCanvas(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void UWidgetBattlePassCanvas::NativeConstruct()
{
    Super::NativeConstruct();

    Controller = UGameplayStatics::GetPlayerController(this, 0);
    if (Controller)
    {
        ScillClient = Controller->FindComponentByClass<UScillClient>();
    }

    FScriptDelegate buttonClickedDelegate;
    buttonClickedDelegate.BindUFunction(this, "UnlockBattlePassHandler");
    UnlockBattlePass->OnReleased.Add(buttonClickedDelegate);

    BattlePassLevelsWidget->LevelButtonDelegate.BindDynamic(this, &UWidgetBattlePassCanvas::OnShowLevelButtonClicked);
    LevelChallengesWidget->ClaimRewardDelegate.BindDynamic(this, &UWidgetBattlePassCanvas::OnClaimRewardClicked);

    QueryBattlePasses();
}

void UWidgetBattlePassCanvas::OnShowLevelButtonClicked(int Id)
{
    LevelChallengesWidget->SwitchToBattlePass(Id);
}

void UWidgetBattlePassCanvas::ReceiveBattlePassesResponse(const TArray<FBattlePass>& BattlePasses, bool Success)
{
    if (Success && BattlePasses.Num() > 0)
    {
        PopulateBattlePassData(BattlePasses[BattlePassId]);
    }
}

void UWidgetBattlePassCanvas::PopulateBattlePassLevelsData(const TArray<FBattlePassLevel>& BattlePassLevels)
{
    CurrentBattlePassLevels = BattlePassLevels;

    int currentLevel = 0;
    for (int i = 0; i < BattlePassLevels.Num(); i++)
    {
        BattlePassActiveLevel->SetText(FText::AsNumber(i + 1));
        currentLevel = i;
        if (!BattlePassLevels[i].LevelCompleted)
        {
            break;
        }
    }

    LevelChallengesWidget->PopulateBattlePassLevelsData(BattlePassLevels);
    LevelChallengesWidget->SwitchToBattlePass(currentLevel);
    BattlePassLevelsWidget->PopulateBattlePassLevelData(BattlePassLevels);
}

void UWidgetBattlePassCanvas::QueryBattlePasses()
{
    if (GetBattlePassFromApi && ScillClient)
    {
        BattlePassArrayReceived.BindDynamic(this, &UWidgetBattlePassCanvas::ReceiveBattlePassesResponse);

        ScillClient->GetBattlePasses(BattlePassArrayReceived);
    }
}

void UWidgetBattlePassCanvas::QueryBattlePassLevels(FString ScillBattlePassId)
{
    if (GetBattlePassFromApi && ScillClient)
    {
        BattlePassLevelsArrayReceived.BindDynamic(this, &UWidgetBattlePassCanvas::ReceiveBattlePassLevelsResponse);

        ScillClient->GetBattlePassLevels(ScillBattlePassId, BattlePassLevelsArrayReceived);
    }
}

void UWidgetBattlePassCanvas::ReceiveBattlePassLevelsResponse(const TArray<FBattlePassLevel>& BattlePassLevels, bool Success)
{
    if (Success)
    {
        PopulateBattlePassLevelsData(BattlePassLevels);
    }
}

void UWidgetBattlePassCanvas::PopulateBattlePassData(const FBattlePass& NewBattlePass)
{
    BattlePass = NewBattlePass;

    SubscribeToBattlePassChanges();

    SetIsBattlePassActive(!BattlePass.UnlockedAt.IsEmpty());
    
    QueryBattlePassLevels(BattlePass.BattlePassId);
}

void UWidgetBattlePassCanvas::UnlockBattlePassHandler()
{
    FBattlePassUnlockInfoReceived Delegate;
    Delegate.BindDynamic(this, &UWidgetBattlePassCanvas::BattlePassUnlocked);
    ScillClient->UnlockBattlePass(BattlePass.BattlePassId, 0, TEXT(""), Delegate);
}

void UWidgetBattlePassCanvas::BattlePassUnlocked(const FBattlePassUnlockInfo& UnlockInfo, bool Success)
{
    QueryBattlePasses();
}

void UWidgetBattlePassCanvas::SetIsBattlePassActive(bool Active)
{
    BattlePassName->SetText(FText::AsCultureInvariant(BattlePass.BattlePassName));
    FDateTime date;
    FDateTime::ParseIso8601(*BattlePass.EndDate, date);
    BattlePassEndDate->SetText(FText::AsDate(date));

    if (Active)
    {
        UnlockBattlePass->SetVisibility(ESlateVisibility::Collapsed);
        BattlePassActiveLevel->SetVisibility(ESlateVisibility::Visible);
        BattlePassLevelsWidget->SetVisibility(ESlateVisibility::Visible);
        LevelChallengesWidget->SetVisibility(ESlateVisibility::Visible);

    }
    else
    {
        UnlockBattlePass->SetVisibility(ESlateVisibility::Visible);
        BattlePassActiveLevel->SetVisibility(ESlateVisibility::Collapsed);
        BattlePassLevelsWidget->SetVisibility(ESlateVisibility::Collapsed);
        LevelChallengesWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UWidgetBattlePassCanvas::OnClaimRewardClicked(FString LevelId)
{
    FHttpResponseReceived Delegate;
    ScillClient->ClaimBattlePassLevel(LevelId, Delegate);
}

void UWidgetBattlePassCanvas::SubscribeToBattlePassChanges()
{
    FBattlePassChangeReceived Delegate;
    Delegate.BindDynamic(this, &UWidgetBattlePassCanvas::ReceiveBattlePassUpdate);
    ScillClient->ReceiveBattlePassUpdates(BattlePass.BattlePassId, Delegate);
}

void UWidgetBattlePassCanvas::ReceiveBattlePassUpdate(BattlePassPayloadType Type, FBattlePassChanged BattlePassChanged, FBattlePassLevelClaimed BattlePassLevelClaimed, FBattlePassExpired BattlePassExpired)
{
    if(Type == BattlePassPayloadType::ChallengeChanged)
    {
        QueryBattlePasses();
    }
}