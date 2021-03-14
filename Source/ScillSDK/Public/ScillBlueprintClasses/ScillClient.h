// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScillApiWrapper/ScillApiBattlePassesApi.h"
#include "ScillApiWrapper/ScillApiBattlePassesApiOperations.h"
#include "ScillBlueprintClasses/ScillStructs.h"
#include "ScillBlueprintClasses/ScillLevelPersistenceInterface.h"
#include "ScillApiWrapper/ScillApiChallengesApi.h"
#include "ScillApiWrapper/ScillApiChallengesApiOperations.h"
#include "ScillApiWrapper/ScillApiEventsApi.h"
#include "Kismet/GameplayStatics.h"
#include "ScillClient.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FHttpResponseReceived, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FBattlePassArrayReceived, const TArray<FBattlePass>&, BattlePasses, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FBattlePassReceived, const FBattlePass&, BattlePasses, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FBattlePassUnlockInfoReceived, const FBattlePassUnlockInfo&, BattlePasses, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FBattlePassLevelArrayReceived, const TArray<FBattlePassLevel>&, BattlePasses, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FChallengeReceived, const FChallenge&, Challenge, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FChallengeCategoryArrayReceived, const TArray<FChallengeCategory>&, ChallengeCategories, bool, Success);



UCLASS(ClassGroup=(ScillSDK), meta=(BlueprintSpawnableComponent) )
class SCILLSDK_API UScillClient : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScillClient();

	// ----------------------------------------------------
	// Access Token

	/* Sets the access token - normally retreived by the GenerateAccessToken function of the ScillClientBackend-Component. */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly))
		void SetAccessToken(FString newAccessToken);

	/* You can set an access token for testing purposes here, although it is better received by the GenerateAccessToken function of the ScilLClientBackend-Component at runtime. */
	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetAccessToken, BlueprintSetter=SetAccessToken)
		FString AccessToken;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly))
		FString GetAccessToken() const;

	// ----------------------------------------------------
	// User Id

	/* Use the User Id for identification on the Scill API. The User ID does not have to related to your own user management - you can for example build global challenges by assigning the same ID to every player. */
	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetUserId, BlueprintSetter = SetUserId)
		FString UserId;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly))
		FString GetUserId() const;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly))
		void SetUserId(FString newUserId);

	// ----------------------------------------------------
	// App Id

	/* The Id of your App. This can be publicly shared, so you can safely put it in this field and deploy it within your client application. */
	UPROPERTY(EditDefaultsOnly)
		FString AppId;

	// ----------------------------------------------------
	// Battle Passes


	/* Activate a given battle pass level by id
	*/
	UFUNCTION(BlueprintCallable)
		void ActivateBattlePassLevel(FString levelId, FHttpResponseReceived responseReceived);

	/* Claim the battle pass level reward. This will trigger a Webhook that you can use to unlock the reward on server side. If you don't have a server you can also unlock in the client application after receiving a positive response.
	 *
	*/
	UFUNCTION(BlueprintCallable)
		void ClaimBattlePassLevel(FString levelId, FHttpResponseReceived responseReceived);

	/*
	* Using this endpoint you can query all active available Battle Passes for the given app id. Typically this query is used to show Battle Passes the user can purchase. You can use the package_sku field to trigger the corresponding in-app purchase.
	*/
	UFUNCTION(BlueprintCallable)
		void GetActiveBattlePasses(FBattlePassArrayReceived responseReceived);

	/*
	* Get unlocked battle passes for the user
	*/
	UFUNCTION(BlueprintCallable)
		void GetUnlockedPasses(FBattlePassArrayReceived responseReceived);
	
	/*
	*Get all battle pass levels for an app
	*/
	UFUNCTION(meta = (BlueprintInternalUseOnly))
		void GetAllPassLevels(FBattlePassLevelArrayReceived responseReceived);
	/*
	* Get battle pass for the product with id
	*/
	UFUNCTION(BlueprintCallable)
		void GetBattlePass(FString battlePassId, FBattlePassReceived responseReceived);

	/* 
	* Get battle pass levels for a battle pass
	*/
	UFUNCTION(BlueprintCallable)
		void GetBattlePassLevels(FString battlePassId, FBattlePassLevelArrayReceived responseReceived);

	/*
	* Get battle passes for the product
	*/
	UFUNCTION(BlueprintCallable)
		void GetBattlePasses(FBattlePassArrayReceived responseReceived);

	/* Unlock the battle pass for the user
	*
	*/
	UFUNCTION(BlueprintCallable)
		void UnlockBattlePass(FString battlePassId, float purchasePrice, FString purchaseCurrency, FBattlePassUnlockInfoReceived responseReceived);

	// ----------------------------------------------------
	// Challenges

	/*
	 *
	 * Activate a personal challenge by product id and user challenge id
	*/
	UFUNCTION(BlueprintCallable)
		void ActivatePersonalChallenge(FString challengeId, FChallengeReceived responseReceived);

	/* 
	 *
	 * Cancel an active personal challenge by product id and user challenge id
	*/
	UFUNCTION(BlueprintCallable)
		void CancelPersonalChallenge(FString challengeId, FChallengeReceived responseReceived);

	/* Claim the reward of a finished personal challenge
	 *
	 * Claim the reward of a finished personal challenge by product id and user challenge id
	*/
	UFUNCTION(BlueprintCallable)
		void ClaimPersonalChallengeReward(FString challengeId, FChallengeReceived responseReceived);
	
	/*
	 *
	 * Get active personal challenges organized in categories
	*/
	UFUNCTION(BlueprintCallable)
		void GetActivePersonalChallenges(FChallengeCategoryArrayReceived responseReceived);

	/* 
	 *
	 * Get personal challenges organized in categories that are not yet finished
	*/
	UFUNCTION(BlueprintCallable)
		void GetAllPersonalChallenges(FChallengeCategoryArrayReceived responseReceived);

	/* Get personal challenges that are not yet completed.
	 *
	 * Get personal challenges organized in categories
	*/
	UFUNCTION(BlueprintCallable)
		void GetPersonalChallenges(FChallengeCategoryArrayReceived responseReceived);

	/* 
	 *
	 * Get personal challenges organized in categories that are not yet finished
	*/
	UFUNCTION(BlueprintCallable)
		void GetUnresolvedPersonalChallenges(FChallengeCategoryArrayReceived responseReceived);

	/* Get personal challenge by id
	 *
	 * 
	*/
	UFUNCTION(BlueprintCallable)
		void GetPersonalChallengeById(FString challengeId, FChallengeReceived responseReceived);

	/*
	 *
	 * Unlock a personal challenge by product id and challenge id
	*/
	UFUNCTION(BlueprintCallable)
		void UnlockPersonalChallenge(FString challengeId, FChallengeReceived responseReceived);

	// ----------------------------------------------------
	// Events

	UFUNCTION(meta = (BlueprintInternalUseOnly))
		void SendEvent(FScillEventPayload payload, FHttpResponseReceived responseReceived);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	ScillSDK::ScillApiBattlePassesApi battlePassesApi;
	ScillSDK::ScillApiChallengesApi challengesApi;
	ScillSDK::ScillApiEventsApi eventsApi;

	// ----------------------------------------------------------------------------------
	// General Helpers

	mutable TMap<FGuid, FHttpResponseReceived> callbackMapResponseReceived;


	// ----------------------------------------------------------------------------------
	// Battle Passes Handlers

	void ReceiveActivateBattlePassLevelResponse(const ScillSDK::ScillApiBattlePassesApi::ActivateBattlePassLevelResponse& Response, FGuid guid) const;
	void ReceiveClaimBattlePassLevelResponse(const ScillSDK::ScillApiBattlePassesApi::ClaimBattlePassLevelRewardResponse& Response, FGuid guid) const;
	void ReceiveActiveBattlePassesResponse(const ScillSDK::ScillApiBattlePassesApi::GetActiveBattlePassesResponse& Response, FGuid guid) const;
	void ReceiveUnlockedBattlePassesResponse(const ScillSDK::ScillApiBattlePassesApi::GetUnlockedBattlePassesResponse& Response, FGuid guid) const;
	void ReceiveAllBattlePassLevelsResponse(const ScillSDK::ScillApiBattlePassesApi::GetAllBattlePassLevelsResponse& Response, FGuid guid) const;
	void ReceiveBattlePassResponse(const ScillSDK::ScillApiBattlePassesApi::GetBattlePassResponse& Response, FGuid guid) const;
	void ReceiveBattlePassLevelsResponse(const ScillSDK::ScillApiBattlePassesApi::GetBattlePassLevelsResponse& Response, FGuid guid) const;
	void ReceiveBattlePassesResponse(const ScillSDK::ScillApiBattlePassesApi::GetBattlePassesResponse& Response, FGuid guid) const;
	void ReceiveUnlockBattlePassResponse(const ScillSDK::ScillApiBattlePassesApi::UnlockBattlePassResponse& Response, FGuid guid) const;

	// ----------------------------------------------------------------------------------
	// Battle Passes Helpers

	mutable TMap<FGuid, FBattlePassArrayReceived> callbackMapBattlePassArrayReceived;
	mutable TMap<FGuid, FBattlePassReceived> callbackMapBattlePassReceived;
	mutable TMap<FGuid, FBattlePassLevelArrayReceived> callbackMapBattlePassLevelArrayReceived;
	mutable TMap<FGuid, FBattlePassUnlockInfoReceived> callbackMapBattlePassUnlockInfoReceived;

	// ----------------------------------------------------------------------------------
	// Challenges Handlers

	void ReceiveActivatePersonalChallengeResponse(const ScillSDK::ScillApiChallengesApi::ActivatePersonalChallengeResponse& Response, FGuid guid) const;
	void ReceiveCancelPersonalChallengeResponse(const ScillSDK::ScillApiChallengesApi::CancelPersonalChallengeResponse& Response, FGuid guid) const;
	void ReceiveClaimPersonalChallengeRewardResponse(const ScillSDK::ScillApiChallengesApi::ClaimPersonalChallengeRewardResponse& Response, FGuid guid) const;
	void ReceiveGetActivePersonalChallengesResponse(const ScillSDK::ScillApiChallengesApi::GetActivePersonalChallengesResponse& Response, FGuid guid) const;
	void ReceiveGetAllPersonalChallengesResponse(const ScillSDK::ScillApiChallengesApi::GetAllPersonalChallengesResponse& Response, FGuid guid) const;
	void ReceiveGetPersonalChallengesResponse(const ScillSDK::ScillApiChallengesApi::GetPersonalChallengesResponse& Response, FGuid guid) const;
	void ReceiveGetUnresolvedPersonalChallengesResponse(const ScillSDK::ScillApiChallengesApi::GetUnresolvedPersonalChallengesResponse& Response, FGuid guid) const;
	void ReceiveGetPersonalChallengeByIdResponse(const ScillSDK::ScillApiChallengesApi::GetPersonalChallengeByIdResponse& Response, FGuid guid) const;
	void ReceiveUnlockPersonalChallengeResponse(const ScillSDK::ScillApiChallengesApi::UnlockPersonalChallengeResponse& Response, FGuid guid) const;
	
	// ----------------------------------------------------------------------------------
	// Challenges Helpers

	mutable TMap<FGuid, FChallengeReceived> callbackMapChallengeReceived;
	mutable TMap<FGuid, FChallengeCategoryArrayReceived> callbackMapChallengeCategoryArrayReceived;

	// ----------------------------------------------------------------------------------
	// Events Handlers

	void ReceiveSendEventResponse(const ScillSDK::ScillApiEventsApi::SendEventResponse& Response, FGuid guid) const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
