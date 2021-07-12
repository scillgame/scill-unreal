// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/WidgetPersonalChallenge.h"
#include "WidgetPersonalChallenges.generated.h"

/**
 * 
 */
UCLASS()
class SCILLSDK_API UWidgetPersonalChallenges : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UWidgetPersonalChallenges(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidgetOptional))
		UPanelWidget* ChallengesPanel;

	UPROPERTY()
		UScillClient* ScillClient;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool GetChallengesFromApi = true;

	/* Use this to determine which challenge category to show. Can be equal to the Slug or the Challenge Id.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString ChallengeCategorySlug;

	FChallengeCategoryArrayReceived ChallengesReceivedDelegate;

	TArray<FChallengeCategory> CurrentChallengeCategories;
	int CurrentChallengeCategoryIndex;

	UFUNCTION(BlueprintCallable)
		void PopulateChallengesData(const TArray<FChallengeCategory>& ChallengeCategories);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UWidgetPersonalChallenge> ChallengeWidgetType;

private:
	APlayerController* Controller;

	UFUNCTION()
	void ReceiveChallengesResponse(const TArray<FChallengeCategory>& ChallengeCategories, bool Success);

	void QueryChallenges();

	void PopulateChallengesDataToChildrenWidgets();

	UFUNCTION()
	void UnlockChallenge(int Index);

	UFUNCTION()
	void ClaimChallengeReward(int Index);

	UFUNCTION()
	void CancelChallenge(int Index);

	UFUNCTION()
	void ActivateChallenge(int Index);

	void SubscribeToPersonalChallengesChanges();

	UFUNCTION()
	void ReceiveChallengeUpdate(FChallengeChanged ChallengeChanged);
};
