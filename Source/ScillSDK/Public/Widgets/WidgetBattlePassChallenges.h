// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/WidgetBattlePassChallenge.h"
#include "WidgetBattlePassChallenges.generated.h"

/**
 * 
 */
UCLASS()
class SCILLSDK_API UWidgetBattlePassChallenges : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UWidgetBattlePassChallenge> ChallengeWidgetType;

	UPROPERTY(meta = (BindWidgetOptional))
	UPanelWidget* ChallengesPanel;

	TArray<FBattlePassLevel> CurrentBattlePassLevels;

	int CurrentId;

	UFUNCTION(BlueprintCallable)
	void PopulateBattlePassLevelsData(const TArray<FBattlePassLevel>& BattlePassLevels);

	UFUNCTION(BlueprintCallable)
	void SwitchToBattlePass(int Id);
};
