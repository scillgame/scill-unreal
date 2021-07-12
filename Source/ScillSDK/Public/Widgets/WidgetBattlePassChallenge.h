// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "WidgetBattlePassChallenge.generated.h"

/**
 * 
 */
UCLASS()
class SCILLSDK_API UWidgetBattlePassChallenge : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidgetOptional))
		UProgressBar* ChallengeProgress;

	UPROPERTY(meta = (BindWidgetOptional))
		UTextBlock* ChallengeCurrentScore;

	UPROPERTY(meta = (BindWidgetOptional))
		UTextBlock* ChallengeGoal;

	UPROPERTY(meta = (BindWidgetOptional))
		UTextBlock* ChallengeName;
};
