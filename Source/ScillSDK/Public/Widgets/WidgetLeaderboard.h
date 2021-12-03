// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScillBlueprintClasses/ScillClient.h"
#include "Widgets/WidgetLeaderboardUserRank.h"
#include "WidgetLeaderboard.generated.h"

class UScillClient;
/**
 * 
 */
UCLASS()
class SCILLSDK_API UWidgetLeaderboard : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UWidgetLeaderboard(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidgetOptional))
		UPanelWidget* RankingsPanel;

	UPROPERTY(meta = (BindWidgetOptional))
		UTextBlock* LeaderboardName;

	UPROPERTY()
		UScillClient* ScillClient;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool GetLeaderboardsFromApi = true;

	/* Use this to determine which leaderboard to show.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int LeaderboardIndex;

	FLeaderboardsReceived LeaderboardsReceivedDelegate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FLeaderboardV2Results> CurrentLeaderboards;

	UFUNCTION(BlueprintCallable)
		void PopulateLeaderboardsData(const TArray<FLeaderboardV2Results>& Leaderboards);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UWidgetLeaderboardUserRank> RankingWidgetType;

private:
	APlayerController* Controller;

	UFUNCTION()
		void ReceiveLeaderboardsResponse(const TArray<FLeaderboardV2Results>& Leaderboards, bool Success);

	void QueryLeaderboards();

	void PopulateLeaderboardDataToChildrenWidgets();

	void SubscribeToLeaderboardChanges();

	UFUNCTION()
		void ReceiveLeaderboardUpdate(FLeaderboardV2UpdatePayload LeaderboardChanged, FLeaderboardV2Changed LeaderboardInfoChanged);
};
