// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "WidgetChallenge.generated.h"

/**
 * 
 */
UCLASS()
class SCILLSDK_API UWidgetChallenge : public UUserWidget
{
	GENERATED_BODY()

public:
	UWidgetChallenge(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidgetOptional))
		UButton* TestButton;
};
