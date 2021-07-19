// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ScillBlueprintClasses/ScillStructs.h"
#include "Widgets/WidgetBattlePassChallenge.h"
#include "WidgetBattlePassChallenges.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FClaimRewardButtonDelegate, FString, LevelId);

/**
 * 
 */
UCLASS()
class SCILLSDK_API UWidgetBattlePassChallenges : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UWidgetBattlePassChallenge> ChallengeWidgetType;

	UPROPERTY(meta = (BindWidgetOptional))
	UPanelWidget* ChallengesPanel;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* ClaimReward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBattlePassLevel> CurrentBattlePassLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentId;

	UFUNCTION(BlueprintCallable)
	void PopulateBattlePassLevelsData(const TArray<FBattlePassLevel>& BattlePassLevels);

	UFUNCTION(BlueprintCallable)
	void SwitchToBattlePass(int Id);

	FClaimRewardButtonDelegate ClaimRewardDelegate;

	UFUNCTION()
		void ClaimRewardHandler();
};
