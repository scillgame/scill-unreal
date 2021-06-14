// Copyright Epic Games, Inc. All Rights Reserved.


#include "Widgets/WidgetBattlePassLevels.h"

UWidgetBattlePassLevels::UWidgetBattlePassLevels(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UWidgetBattlePassLevels::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidgetBattlePassLevels::PopulateBattlePassLevelData(const TArray<FBattlePassLevel>& BattlePassLevels)
{
	LevelsPanel->ClearChildren();

	int i = 0;

	for (FBattlePassLevel l : BattlePassLevels)
	{
		UWidgetBattlePassLevel* LevelWidget = CreateWidget<UWidgetBattlePassLevel>(this, LevelWidgetType);

		if(LevelVisuals.Contains(*(l.RewardAmount)))
			LevelWidget->RewardImage->SetBrushFromTexture(LevelVisuals[*(l.RewardAmount)], true);
		LevelWidget->Id = i;
		LevelWidget->LevelName->SetText(FText::Format(FText::FromString(TEXT("Level {0}")), FText::AsNumber(++i)));
		LevelWidget->LevelButtonDelegate.BindDynamic(this, &UWidgetBattlePassLevels::OnShowLevelButtonClicked);
		LevelWidget->Completed = l.LevelCompleted;

		LevelsPanel->AddChild(LevelWidget);
	}
}

void UWidgetBattlePassLevels::OnShowLevelButtonClicked(int Id)
{
	LevelButtonDelegate.ExecuteIfBound(Id);
}