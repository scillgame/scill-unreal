// Copyright Epic Games, Inc. All Rights Reserved.


#include "Widgets/WidgetBattlePassChallenges.h"

void UWidgetBattlePassChallenges::NativeConstruct()
{
	Super::NativeConstruct();

	FScriptDelegate buttonClickedDelegate;
	buttonClickedDelegate.BindUFunction(this, "ClaimRewardHandler");
	ClaimReward->OnReleased.Add(buttonClickedDelegate);
}

void UWidgetBattlePassChallenges::PopulateBattlePassLevelsData(const TArray<FBattlePassLevel>& BattlePassLevels)
{
	CurrentBattlePassLevels.Empty(BattlePassLevels.Num());

	for (FBattlePassLevel l : BattlePassLevels)
	{
		CurrentBattlePassLevels.Add(l);
	}
}

void UWidgetBattlePassChallenges::SwitchToBattlePass(int Id)
{
	ChallengesPanel->ClearChildren();

	CurrentId = Id;

	for (FBattlePassLevelChallenge challenge : CurrentBattlePassLevels[Id].Challenges)
	{
		UWidgetBattlePassChallenge* ChallengeWidget = CreateWidget<UWidgetBattlePassChallenge>(this, ChallengeWidgetType);

		ChallengeWidget->ChallengeName->SetText(FText::FromString(challenge.ChallengeName));
		ChallengeWidget->ChallengeProgress->SetPercent((float)challenge.UserChallengeCurrentScore / (float)challenge.ChallengeGoal);
		ChallengeWidget->ChallengeCurrentScore->SetText(FText::AsNumber(challenge.UserChallengeCurrentScore));
		ChallengeWidget->ChallengeGoal->SetText(FText::AsNumber(challenge.ChallengeGoal));

		ChallengesPanel->AddChild(ChallengeWidget);
	}
}

void UWidgetBattlePassChallenges::ClaimRewardHandler()
{
	ClaimRewardDelegate.ExecuteIfBound(CurrentBattlePassLevels[CurrentId].LevelId);
}