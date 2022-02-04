// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ScillBlueprintClasses/ScillClient.h"
#include "ScillBlueprintClasses/ScillStructs.h"
#include "Widgets/WidgetBattlePassLevels.h"
#include "Widgets/WidgetBattlePassChallenges.h"
#include "Components/Button.h"
#include "WidgetBattlePassCanvas.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SCILLSDK_API UWidgetBattlePassCanvas : public UUserWidget
{
	GENERATED_BODY()
public:
	UWidgetBattlePassCanvas(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidgetOptional))
		UButton* UnlockBattlePass;

	UPROPERTY(meta = (BindWidgetOptional))
		UTextBlock* BattlePassName;

	UPROPERTY(meta = (BindWidgetOptional))
		UTextBlock* BattlePassEndDate;

	UPROPERTY(meta = (BindWidgetOptional))
		UTextBlock* BattlePassActiveLevel;

	UPROPERTY(meta = (BindWidgetOptional))
		UWidgetBattlePassLevels* BattlePassLevelsWidget;

	UPROPERTY(meta = (BindWidgetOptional))
		UWidgetBattlePassChallenges* LevelChallengesWidget;

	UPROPERTY()
		UScillClient* ScillClient;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FBattlePass BattlePass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FBattlePassLevel> CurrentBattlePassLevels;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int BattlePassId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool GetBattlePassFromApi = true;

	FBattlePassArrayReceived BattlePassArrayReceived;
	FBattlePassLevelArrayReceived BattlePassLevelsArrayReceived;

	UFUNCTION(BlueprintCallable)
		void PopulateBattlePassData(const FBattlePass& NewBattlePass);

	UFUNCTION(BlueprintCallable)
		void PopulateBattlePassLevelsData(const TArray<FBattlePassLevel>& BattlePassLevels);

protected:

	APlayerController* Controller;

	UFUNCTION()
	void ReceiveBattlePassesResponse(const TArray<FBattlePass>& BattlePasses, bool Success);

	UFUNCTION()
	void ReceiveBattlePassLevelsResponse(const TArray<FBattlePassLevel>& BattlePassLevels, bool Success);

	void QueryBattlePasses();
	void QueryBattlePassLevels(FString ScillBattlePassId);

	UFUNCTION()
		void OnShowLevelButtonClicked(int Id);

	UFUNCTION()
		void UnlockBattlePassHandler();

	UFUNCTION()
		void BattlePassUnlocked(const FBattlePassUnlockInfo& UnlockInfo, bool Success);

	UFUNCTION()
		void SetIsBattlePassActive(bool Completed);

	UFUNCTION()
		void OnClaimRewardClicked(FString LevelId);

		void SubscribeToBattlePassChanges();

	UFUNCTION()
		void ReceiveBattlePassUpdate(BattlePassPayloadType Type, FBattlePassChanged BattlePassChanged, FBattlePassLevelClaimed BattlePassLevelClaimed);
};
