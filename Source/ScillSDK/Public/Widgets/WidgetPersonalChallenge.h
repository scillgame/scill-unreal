// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "WidgetPersonalChallenge.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FChallengeButtonsDelegate, int, ChallengeIndex);

/**
 * 
 */
UCLASS()
class SCILLSDK_API UWidgetPersonalChallenge : public UUserWidget
{
	GENERATED_BODY()
public:

	UWidgetPersonalChallenge(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	int Index;

	UPROPERTY(meta = (BindWidgetOptional))
		UButton* UnlockChallenge;

	UPROPERTY(meta = (BindWidgetOptional))
		UButton* ActivateChallenge;

	UPROPERTY(meta = (BindWidgetOptional))
		UButton* ClaimReward;

	UPROPERTY(meta = (BindWidgetOptional))
		UButton* CancelChallenge;

	UPROPERTY(meta = (BindWidgetOptional))
		UProgressBar* ChallengeProgress;

	UPROPERTY(meta = (BindWidgetOptional))
		UTextBlock* ChallengeCurrentScore;

	UPROPERTY(meta = (BindWidgetOptional))
		UTextBlock* ChallengeGoal;

	UPROPERTY(meta = (BindWidgetOptional))
		UTextBlock* ChallengeName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FChallenge CurrentChallenge;

	FChallengeButtonsDelegate UnlockChallengeDelegate;
	FChallengeButtonsDelegate ClaimRewardDelegate;
	FChallengeButtonsDelegate CancelChallengeDelegate;
	FChallengeButtonsDelegate ActivateChallengeDelegate;

	UFUNCTION(BlueprintCallable)
		void CheckStatus(FChallenge Challenge);

	bool Unlocked;
	bool Activated;
	bool Finished;
	bool Claimed;

private:

	UFUNCTION()
		void UnlockChallengeClicked();
	UFUNCTION()
		void ClaimRewardClicked();
	UFUNCTION()
		void CancelChallengeClicked();
	UFUNCTION()
		void ActivateChallengeClicked();
	
};
