// Copyright Epic Games, Inc. All Rights Reserved.


#include "Widgets/WidgetPersonalChallenges.h"

UWidgetPersonalChallenges::UWidgetPersonalChallenges(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void UWidgetPersonalChallenges::NativeConstruct()
{
    Super::NativeConstruct();

    Controller = UGameplayStatics::GetPlayerController(this, 0);
    if (Controller)
    {
        ScillClient = Controller->FindComponentByClass<UScillClient>();
    }

    /*FScriptDelegate buttonClickedDelegate;
    buttonClickedDelegate.BindUFunction(this, "UnlockBattlePassHandler");
    UnlockBattlePass->OnReleased.Add(buttonClickedDelegate);

    BattlePassLevelsWidget->LevelButtonDelegate.BindDynamic(this, &UWidgetBattlePassCanvas::OnShowLevelButtonClicked);
    LevelChallengesWidget->ClaimRewardDelegate.BindDynamic(this, &UWidgetBattlePassCanvas::OnClaimRewardClicked);*/

    QueryChallenges();
    SubscribeToPersonalChallengesChanges();
}

void UWidgetPersonalChallenges::QueryChallenges()
{
    if (GetChallengesFromApi && ScillClient)
    {
        ChallengesReceivedDelegate.BindDynamic(this, &UWidgetPersonalChallenges::ReceiveChallengesResponse);

        ScillClient->GetAllPersonalChallenges(ChallengesReceivedDelegate);
    }
}

void UWidgetPersonalChallenges::ReceiveChallengesResponse(const TArray<FChallengeCategory>& ChallengeCategories, bool Success)
{
    if (Success)
        PopulateChallengesData(ChallengeCategories);

}

void UWidgetPersonalChallenges::PopulateChallengesData(const TArray<FChallengeCategory>& ChallengeCategories)
{
    CurrentChallengeCategories = ChallengeCategories;

    int index = 0;
    for (auto cat : CurrentChallengeCategories)
    {
        if (cat.CategorySlug == ChallengeCategorySlug || cat.CategoryId == ChallengeCategorySlug)
        {
            break;
        }
        index++;
    }
    CurrentChallengeCategoryIndex = index;
    if (CurrentChallengeCategoryIndex >= CurrentChallengeCategories.Num())
        CurrentChallengeCategoryIndex = 0;

    PopulateChallengesDataToChildrenWidgets();
}

void UWidgetPersonalChallenges::PopulateChallengesDataToChildrenWidgets()
{
    ChallengesPanel->ClearChildren();

    int i = 0;

    for (auto c : CurrentChallengeCategories[CurrentChallengeCategoryIndex].Challenges)
    {
        UWidgetPersonalChallenge* ChallengeWidget = CreateWidget<UWidgetPersonalChallenge>(this, ChallengeWidgetType);

        ChallengeWidget->CheckStatus(c);

        ChallengeWidget->ChallengeProgress->SetPercent((float)c.UserChallengeCurrentScore / (float)c.ChallengeGoal);
        ChallengeWidget->ChallengeName->SetText(FText::FromString(c.ChallengeName));
        ChallengeWidget->ChallengeCurrentScore->SetText(FText::AsNumber(c.UserChallengeCurrentScore));
        ChallengeWidget->ChallengeGoal->SetText(FText::AsNumber(c.ChallengeGoal));

        ChallengeWidget->UnlockChallengeDelegate.BindDynamic(this, &UWidgetPersonalChallenges::UnlockChallenge);
        ChallengeWidget->ClaimRewardDelegate.BindDynamic(this, &UWidgetPersonalChallenges::ClaimChallengeReward);
        ChallengeWidget->CancelChallengeDelegate.BindDynamic(this, &UWidgetPersonalChallenges::CancelChallenge);
        ChallengeWidget->ActivateChallengeDelegate.BindDynamic(this, &UWidgetPersonalChallenges::ActivateChallenge);

        ChallengeWidget->CurrentChallenge = c;

        ChallengesPanel->AddChild(ChallengeWidget);
    }
}

void UWidgetPersonalChallenges::UnlockChallenge(int Index)
{
    FChallengeReceived Delegate;
    ScillClient->UnlockPersonalChallenge(CurrentChallengeCategories[CurrentChallengeCategoryIndex].Challenges[Index].ChallengeId, Delegate);
}

void UWidgetPersonalChallenges::ClaimChallengeReward(int Index)
{
    FChallengeReceived Delegate;
    ScillClient->ClaimPersonalChallengeReward(CurrentChallengeCategories[CurrentChallengeCategoryIndex].Challenges[Index].ChallengeId, Delegate);
}

void UWidgetPersonalChallenges::CancelChallenge(int Index)
{
    FChallengeReceived Delegate;
    ScillClient->CancelPersonalChallenge(CurrentChallengeCategories[CurrentChallengeCategoryIndex].Challenges[Index].ChallengeId, Delegate);
}

void UWidgetPersonalChallenges::ActivateChallenge(int Index)
{
    FChallengeReceived Delegate;
    ScillClient->ActivatePersonalChallenge(CurrentChallengeCategories[CurrentChallengeCategoryIndex].Challenges[Index].ChallengeId, Delegate);
}

void UWidgetPersonalChallenges::SubscribeToPersonalChallengesChanges()
{
    FChallengeChangeReceived Delegate;
    Delegate.BindDynamic(this, &UWidgetPersonalChallenges::ReceiveChallengeUpdate);
    ScillClient->ReceiveChallengeUpdates(Delegate);
}

void UWidgetPersonalChallenges::ReceiveChallengeUpdate(FChallengeChanged ChallengeChanged)
{
    QueryChallenges();
}