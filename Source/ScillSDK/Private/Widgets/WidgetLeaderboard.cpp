// Copyright Epic Games, Inc. All Rights Reserved.


#include "Widgets/WidgetLeaderboard.h"

UWidgetLeaderboard::UWidgetLeaderboard(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void UWidgetLeaderboard::NativeConstruct()
{
    Super::NativeConstruct();

    Controller = UGameplayStatics::GetPlayerController(this, 0);
    if (Controller)
    {
        ScillClient = Controller->FindComponentByClass<UScillClient>();
    }

    QueryLeaderboards();
    SubscribeToLeaderboardChanges();
}

void UWidgetLeaderboard::SubscribeToLeaderboardChanges()
{
    for (auto l : CurrentLeaderboards)
    {
        FLeaderboardChangeReceived Delegate;
        Delegate.BindDynamic(this, &UWidgetLeaderboard::ReceiveLeaderboardUpdate);
        ScillClient->ReceiveLeaderboardUpdates(l.LeaderboardId, Delegate);
    }
}

void UWidgetLeaderboard::ReceiveLeaderboardUpdate(FLeaderboardUpdatePayload LeaderboardChanged)
{
    QueryLeaderboards();
}

void UWidgetLeaderboard::QueryLeaderboards()
{
    if (GetLeaderboardsFromApi && ScillClient)
    {
        LeaderboardsReceivedDelegate.BindDynamic(this, &UWidgetLeaderboard::ReceiveLeaderboardsResponse);

        ScillClient->GetLeaderboards(1, 25, TEXT("en"), LeaderboardsReceivedDelegate);
    }
}

void UWidgetLeaderboard::ReceiveLeaderboardsResponse(const TArray<FLeaderboard>& Leaderboards, bool Success)
{
    if (Success)
        PopulateLeaderboardsData(Leaderboards);

}

void UWidgetLeaderboard::PopulateLeaderboardsData(const TArray<FLeaderboard>& Leaderboards)
{
    CurrentLeaderboards = Leaderboards;

    if (LeaderboardIndex >= Leaderboards.Num())
        LeaderboardIndex = Leaderboards.Num() - 1;

    LeaderboardName->SetText(FText::FromString(CurrentLeaderboards[LeaderboardIndex].Name));

    PopulateLeaderboardDataToChildrenWidgets();
}

void UWidgetLeaderboard::PopulateLeaderboardDataToChildrenWidgets()
{
    RankingsPanel->ClearChildren();

    for (auto ranking : CurrentLeaderboards[LeaderboardIndex].GroupedByUsers)
    {
        UWidgetLeaderboardUserRank* RankingWidget = CreateWidget<UWidgetLeaderboardUserRank>(this, RankingWidgetType);

        RankingWidget->UserName->SetText(FText::AsCultureInvariant(ranking.AdditionalInfo.Username));
        RankingWidget->UserScore->SetText(FText::AsNumber(ranking.Score));

        RankingWidget->CurrentRanking = ranking;

        RankingsPanel->AddChild(RankingWidget);
    }
}

//void UWidgetLeaderboard::SubscribeToPersonalChallengesChanges()
//{
//    FChallengeChangeReceived Delegate;
//    Delegate.BindDynamic(this, &UWidgetPersonalChallenges::ReceiveChallengeUpdate);
//    ScillClient->ReceiveChallengeUpdates(Delegate);
//}
//
//void UWidgetLeaderboard::ReceiveChallengeUpdate(FChallengeChanged ChallengeChanged)
//{
//    QueryChallenges();
//}