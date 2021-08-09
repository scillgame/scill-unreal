// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/WidgetBattlePassLevel.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "ScillBlueprintClasses/ScillStructs.h"

#include "WidgetBattlePassLevels.generated.h"

/**
 * 
 */
UCLASS()
class SCILLSDK_API UWidgetBattlePassLevels : public UUserWidget
{
	GENERATED_BODY()


public:
	UWidgetBattlePassLevels(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidgetOptional))
	UPanelWidget* LevelsPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UTexture2D*> LevelVisuals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UWidgetBattlePassLevel> LevelWidgetType;

	UFUNCTION(BlueprintCallable)
		void PopulateBattlePassLevelData(const TArray<FBattlePassLevel>& BattlePassLevels);

	UFUNCTION()
		void OnShowLevelButtonClicked(int Id);

	FShowLevelButtonDelegate LevelButtonDelegate;
};
