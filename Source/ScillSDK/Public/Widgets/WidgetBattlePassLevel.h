// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "WidgetBattlePassLevel.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FShowLevelButtonDelegate, int, BattlePassId);

/**
 * 
 */
UCLASS()
class SCILLSDK_API UWidgetBattlePassLevel : public UUserWidget
{
	GENERATED_BODY()

public:

	UWidgetBattlePassLevel(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidgetOptional))
	UImage* RewardImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Completed;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* LevelName;
	
	UPROPERTY(meta = (BindWidgetOptional))
	UButton* ShowLevel;

	FShowLevelButtonDelegate LevelButtonDelegate;

	UFUNCTION()
		void ShowLevelClicked();

	int Id;
};
