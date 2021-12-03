// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScillBlueprintClasses/ScillStructs.h"

#include "WidgetLeaderboardUserRank.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class SCILLSDK_API UWidgetLeaderboardUserRank : public UUserWidget
{
	GENERATED_BODY()
public:
	/*UPROPERTY(meta = (BindWidgetOptional))
		UImage* UserImage;*/

	UPROPERTY(meta = (BindWidgetOptional))
		UTextBlock* UserName;

	UPROPERTY(meta = (BindWidgetOptional))
		UTextBlock* UserScore;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FLeaderboardV2Member CurrentRanking;
};
