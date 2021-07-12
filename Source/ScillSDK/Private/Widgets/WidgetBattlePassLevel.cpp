// Copyright Epic Games, Inc. All Rights Reserved.


#include "Widgets/WidgetBattlePassLevel.h"

UWidgetBattlePassLevel::UWidgetBattlePassLevel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UWidgetBattlePassLevel::NativeConstruct()
{
	Super::NativeConstruct();

	FScriptDelegate buttonClickedDelegate;
	buttonClickedDelegate.BindUFunction(this, "ShowLevelClicked");
	ShowLevel->OnReleased.Add(buttonClickedDelegate);
}

void UWidgetBattlePassLevel::ShowLevelClicked()
{
	LevelButtonDelegate.ExecuteIfBound(Id);
}