// Copyright Epic Games, Inc. All Rights Reserved.


#include "Widgets/WidgetPersonalChallenge.h"
#include "..\..\Public\Widgets\WidgetPersonalChallenge.h"

UWidgetPersonalChallenge::UWidgetPersonalChallenge(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UWidgetPersonalChallenge::NativeConstruct()
{
	Super::NativeConstruct();

	FScriptDelegate ucButtonDelegate;
	ucButtonDelegate.BindUFunction(this, "UnlockChallengeClicked");
	UnlockChallenge->OnReleased.Add(ucButtonDelegate);

	FScriptDelegate crButtonDelegate;
	crButtonDelegate.BindUFunction(this, "ClaimRewardClicked");
	ClaimReward->OnReleased.Add(crButtonDelegate);

	FScriptDelegate ccButtonDelegate;
	ccButtonDelegate.BindUFunction(this, "CancelChallengeClicked");
	CancelChallenge->OnReleased.Add(ccButtonDelegate);

	FScriptDelegate acButtonDelegate;
	acButtonDelegate.BindUFunction(this, "ActivateChallengeClicked");
	ActivateChallenge->OnReleased.Add(acButtonDelegate);
}

void UWidgetPersonalChallenge::UnlockChallengeClicked()
{
	UnlockChallengeDelegate.ExecuteIfBound(Index);
}

void UWidgetPersonalChallenge::ClaimRewardClicked()
{
	UnlockChallengeDelegate.ExecuteIfBound(Index);
}

void UWidgetPersonalChallenge::CancelChallengeClicked()
{
	CancelChallengeDelegate.ExecuteIfBound(Index);
}

void UWidgetPersonalChallenge::ActivateChallengeClicked()
{
	ActivateChallengeDelegate.ExecuteIfBound(Index);
}

void UWidgetPersonalChallenge::CheckStatus(FChallenge Challenge)
{
	CurrentChallenge = Challenge;
	
	// Not yet unlocked
	if (CurrentChallenge.Type.Equals(TEXT("unlock"), ESearchCase::IgnoreCase))
	{
		UnlockChallenge->SetVisibility(ESlateVisibility::Visible);

		ActivateChallenge->SetVisibility(ESlateVisibility::Collapsed);
		ClaimReward->SetVisibility(ESlateVisibility::Collapsed);
		CancelChallenge->SetVisibility(ESlateVisibility::Collapsed);
		ChallengeProgress->SetVisibility(ESlateVisibility::Collapsed);
		ChallengeCurrentScore->SetVisibility(ESlateVisibility::Collapsed);
		ChallengeGoal->SetVisibility(ESlateVisibility::Collapsed);
	}
	//unlocked but not activated
	else if (CurrentChallenge.Type.Equals(TEXT("unlocked"), ESearchCase::IgnoreCase))
	{
		ActivateChallenge->SetVisibility(ESlateVisibility::Visible);

		UnlockChallenge->SetVisibility(ESlateVisibility::Collapsed);
		ClaimReward->SetVisibility(ESlateVisibility::Collapsed);
		CancelChallenge->SetVisibility(ESlateVisibility::Collapsed);
		ChallengeProgress->SetVisibility(ESlateVisibility::Collapsed);
		ChallengeCurrentScore->SetVisibility(ESlateVisibility::Collapsed);
		ChallengeGoal->SetVisibility(ESlateVisibility::Collapsed);
	}
	// activated but not completed
	else if (CurrentChallenge.Type.Equals(TEXT("in-progress"), ESearchCase::IgnoreCase))
	{
		ActivateChallenge->SetVisibility(ESlateVisibility::Collapsed);
		UnlockChallenge->SetVisibility(ESlateVisibility::Collapsed);
		ClaimReward->SetVisibility(ESlateVisibility::Collapsed);
		CancelChallenge->SetVisibility(ESlateVisibility::Visible);
		ChallengeProgress->SetVisibility(ESlateVisibility::Visible);
		ChallengeCurrentScore->SetVisibility(ESlateVisibility::Visible);
		ChallengeGoal->SetVisibility(ESlateVisibility::Visible);
	}
	else if (CurrentChallenge.Type.Equals(TEXT("unclaimed"), ESearchCase::IgnoreCase))
	{
		ActivateChallenge->SetVisibility(ESlateVisibility::Collapsed);
		UnlockChallenge->SetVisibility(ESlateVisibility::Collapsed);
		ClaimReward->SetVisibility(ESlateVisibility::Visible);
		CancelChallenge->SetVisibility(ESlateVisibility::Collapsed);
		ChallengeProgress->SetVisibility(ESlateVisibility::Collapsed);
		ChallengeCurrentScore->SetVisibility(ESlateVisibility::Collapsed);
		ChallengeGoal->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		ActivateChallenge->SetVisibility(ESlateVisibility::Collapsed);
		UnlockChallenge->SetVisibility(ESlateVisibility::Collapsed);
		ClaimReward->SetVisibility(ESlateVisibility::Collapsed);
		CancelChallenge->SetVisibility(ESlateVisibility::Collapsed);
		ChallengeProgress->SetVisibility(ESlateVisibility::Collapsed);
		ChallengeCurrentScore->SetVisibility(ESlateVisibility::Collapsed);
		ChallengeGoal->SetVisibility(ESlateVisibility::Collapsed);
	}
}
