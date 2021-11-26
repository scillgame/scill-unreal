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
#include "ScillApiWrapper/ScillApiAuthApi.h"
#include "ScillApiWrapper/ScillApiLeaderboardsApi.h"
#include "ScillApiWrapper/ScillApiLeaderboardsV2Api.h"
#include "ScillHelpers/ScillMqtt.h"
#include "Kismet/GameplayStatics.h"
#include "ScillClient.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FHttpResponseReceived, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FBattlePassArrayReceived, const TArray<FBattlePass>&, BattlePasses, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FBattlePassReceived, const FBattlePass&, BattlePass, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FBattlePassUnlockInfoReceived, const FBattlePassUnlockInfo&, BattlePasses, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FBattlePassLevelArrayReceived, const TArray<FBattlePassLevel>&, BattlePasses, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FChallengeReceived, const FChallenge&, Challenge, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FChallengeCategoryArrayReceived, const TArray<FChallengeCategory>&, ChallengeCategories, bool, Success); 
DECLARE_DYNAMIC_DELEGATE_TwoParams(FLeaderboardReceived, const FLeaderboard&, Leaderboard, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FLeaderboardsReceived, const TArray<FLeaderboard>&, Leaderboards, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FLeaderboardRankingReceived, const FLeaderboardMemberRanking&, LeaderboardRanking, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FLeaderboardRankingsReceived, const TArray<FLeaderboardMemberRanking>&, LeaderboardRankings, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FUserInfoReceived, const FUserInfo&, UserInfo, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FLeaderboardReceivedV2, const FLeaderboardV2Results&, Leaderboard, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FLeaderboardRankingReceivedV2, const FLeaderboardV2MemberRanking&, Ranking, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FLeaderboardRankingsReceivedV2, const TArray<FLeaderboardV2MemberRanking>&, Rankings, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FLeaderboardsReceivedV2, const TArray<FLeaderboardV2Results>&, Leaderboard, bool, Success);
DECLARE_DYNAMIC_DELEGATE(FRealtimeConnectionEstablished);


UCLASS(ClassGroup=(ScillSDK), meta=(BlueprintSpawnableComponent), Category = "ScillSDK", Config=Game)
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
	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetAccessToken, BlueprintSetter=SetAccessToken, Category = "ScillSDK")
		FString AccessToken;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly))
		FString GetAccessToken() const;

	// ----------------------------------------------------
	// User Id

	/* Use the User Id for identification on the Scill API. The User ID does not have to related to your own user management - you can for example build global challenges by assigning the same ID to every player. */
	UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetUserId, BlueprintSetter = SetUserId, Category = "ScillSDK")
		FString UserId;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly))
		FString GetUserId() const;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly))
		void SetUserId(FString newUserId);

	// ----------------------------------------------------
	// App Id

	/* The Id of your App. This can be publicly shared, so you can safely put it in this field and deploy it within your client application. */
	UPROPERTY(EditDefaultsOnly, Category = "ScillSDK")
		FString AppId;

	// ----------------------------------------------------
	// Battle Passes


	/* Activate a given battle pass level by id
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void ActivateBattlePassLevel(FString levelId, FHttpResponseReceived responseReceived);

	/* Claim the battle pass level reward. This will trigger a Webhook that you can use to unlock the reward on server side. If you don't have a server you can also unlock in the client application after receiving a positive response.
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void ClaimBattlePassLevel(FString levelId, FHttpResponseReceived responseReceived);

	/*Using this endpoint you can query all active available Battle Passes for the given app id. Typically this query is used to show Battle Passes the user can purchase. You can use the package_sku field to trigger the corresponding in-app purchase.
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void GetActiveBattlePasses(FBattlePassArrayReceived responseReceived);

	/*Get unlocked battle passes for the user
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void GetUnlockedPasses(FBattlePassArrayReceived responseReceived);
	
	/*Get all battle pass levels for an app
	*/
	UFUNCTION(meta = (BlueprintInternalUseOnly), Category = "ScillSDK")
		void GetAllPassLevels(FBattlePassLevelArrayReceived responseReceived);
	/*Get battle pass for the product with id
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void GetBattlePass(FString battlePassId, FBattlePassReceived responseReceived);

	/* Get battle pass levels for a battle pass
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void GetBattlePassLevels(FString battlePassId, FBattlePassLevelArrayReceived responseReceived);

	/*Get battle passes for the product
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void GetBattlePasses(FBattlePassArrayReceived responseReceived);

	/* Unlock the battle pass for the user
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void UnlockBattlePass(FString battlePassId, float purchasePrice, FString purchaseCurrency, FBattlePassUnlockInfoReceived responseReceived);

	// ----------------------------------------------------
	// Challenges

	/*Activate a personal challenge by product id and user challenge id
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void ActivatePersonalChallenge(FString challengeId, FChallengeReceived responseReceived);

	/* Cancel an active personal challenge by product id and user challenge id
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void CancelPersonalChallenge(FString challengeId, FChallengeReceived responseReceived);

	/* Claim the reward of a finished personal challenge by product id and user challenge id
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void ClaimPersonalChallengeReward(FString challengeId, FChallengeReceived responseReceived);
	
	/* Get active personal challenges organized in categories
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void GetActivePersonalChallenges(FChallengeCategoryArrayReceived responseReceived);

	/* Get personal challenges organized in categories that are not yet finished
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void GetAllPersonalChallenges(FChallengeCategoryArrayReceived responseReceived);

	/* Get personal challenges that are not yet completed organized in categories
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void GetPersonalChallenges(FChallengeCategoryArrayReceived responseReceived);

	/*  Get personal challenges organized in categories that are not yet finished
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void GetUnresolvedPersonalChallenges(FChallengeCategoryArrayReceived responseReceived);

	/* Get personal challenge by id
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void GetPersonalChallengeById(FString challengeId, FChallengeReceived responseReceived);

	/*Unlock a personal challenge by product id and challenge id
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void UnlockPersonalChallenge(FString challengeId, FChallengeReceived responseReceived);

	// ----------------------------------------------------
	// Leaderboards


	UFUNCTION(BlueprintCallable, Category = "ScillSDK", meta = (DeprecatedFunction, DeprecationMessage = "The Leaderboard V1 endpoints have been deprecated. Please use the new Leaderboard functions.", DisplayName = "GetLeaderboardV1"))
		void GetLeaderboard(FString BoardId, int CurrentPage, int PageSize, FString Language, FLeaderboardReceived responseReceived);

	UFUNCTION(BlueprintCallable, Category = "ScillSDK", meta = (DeprecatedFunction, DeprecationMessage = "The Leaderboard V1 endpoints have been deprecated. Please use the new Leaderboard functions.", DisplayName = "GetLeaderboardRankingV1"))
		void GetLeaderboardRanking(FString MemberType, FString MemberId, FString LeaderboardId, FString Language, FLeaderboardRankingReceived responseReceived);

	UFUNCTION(BlueprintCallable, Category = "ScillSDK", meta = (DeprecatedFunction, DeprecationMessage = "The Leaderboard V1 endpoints have been deprecated. Please use the new Leaderboard functions.", DisplayName = "GetLeaderboardRankingsV1"))
		void GetLeaderboardRankings(FString MemberType, FString MemberId, FString Language, FLeaderboardRankingsReceived responseReceived);

	UFUNCTION(BlueprintCallable, Category = "ScillSDK", meta = (DeprecatedFunction, DeprecationMessage = "The Leaderboard V1 endpoints have been deprecated. Please use the new Leaderboard functions.", DisplayName = "GetLeaderboardsV1"))
		void GetLeaderboards(int CurrentPage, int PageSize, FString Language, FLeaderboardsReceived responseReceived);

	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void SetUserData(FUserInfo UserInfo, FUserInfoReceived responseReceived);

	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void GetUserData(FUserInfoReceived responseReceived);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FUserInfo CurrentUserInfo;

	UPROPERTY(Config)
		int LeaderboardVersionNumber = 1;

	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		int GetLeaderboardVersionNumber()
	{
		return this->LeaderboardVersionNumber;
	};

	// ----------------------------------------------------
	// Leaderboards V2

	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void GetLeaderboardV2(FString BoardId, FString StartDate, FString EndDate, FString Aggregate, int CurrentPage, int CurrentPosition, int PageSize, FString Language, FLeaderboardReceivedV2 responseReceived);

	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void GetLeaderboardRankingV2(FString MemberType, FString MemberId, FString LeaderboardId, FString StartDate, FString EndDate, FString Aggregate, FString Language, FLeaderboardRankingReceivedV2 responseReceived);

	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void GetLeaderboardRankingsV2(FString MemberType, FString MemberId, FString StartDate, FString EndDate, FString Aggregate, FString Language, FLeaderboardRankingsReceivedV2 responseReceived);

	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void GetLeaderboardsV2( FString StartDate, FString EndDate, FString Aggregate, int CurrentPage, int CurrentPosition, int PageSize, FString Language, FLeaderboardsReceivedV2 responseReceived);
	
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void ResetLeaderboardRankingsV2(FString ApplicationId, FString LeaderboardId, FHttpResponseReceived responseReceived);

	// ----------------------------------------------------------------------------------
	// User Info Helpers
	/*This can be called after receiving a valid access token to make sure that the current user has User Info set for leaderboards.*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void RetrieveUserInfoOrSetToDefault();

	// ----------------------------------------------------
	// Events

		UFUNCTION(meta = (BlueprintInternalUseOnly), Category = "ScillSDK")
		void SendEvent(FScillEventPayload payload, FHttpResponseReceived responseReceived);

	// ----------------------------------------------------
	// Realtime Updates

	/* Start to receive updates from all challenges of the specified battle pass.
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void ReceiveBattlePassUpdates(FString battlePassId, FBattlePassChangeReceived responseReceived);

	/* Start to receive updates from all challenges associated with the current user.
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void ReceiveChallengeUpdates(FChallengeChangeReceived responseReceived);

	/* Start to receive updates from a single leaderboards.
	*/
	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void ReceiveLeaderboardUpdates(FString LeaderboardId, FLeaderboardChangeReceived responseReceived);

	UFUNCTION(BlueprintCallable, Category = "ScillSDK")
		void OnRealtimeConnectionOpen(FRealtimeConnectionEstablished onConnectionEstablished);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	ScillSDK::ScillApiBattlePassesApi battlePassesApi;
	ScillSDK::ScillApiChallengesApi challengesApi;
	ScillSDK::ScillApiEventsApi eventsApi;
	ScillSDK::ScillApiAuthApi authApi;
	ScillSDK::ScillApiLeaderboardsApi leaderboardsApi;
	ScillSDK::ScillApiLeaderboardsV2Api leaderboardsApiV2;
	UScillMqtt* mqtt;

	FTimerHandle PingTimer;
	void MqttPing();

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
	// Leaderboard Helpers

	mutable TMap<FGuid, FLeaderboardReceived> callbackMapLeaderboardReceived;
	mutable TMap<FGuid, FLeaderboardsReceived> callbackMapLeaderboardsReceived;
	mutable TMap<FGuid, FLeaderboardRankingReceived> callbackMapLeaderboardRankingReceived;
	mutable TMap<FGuid, FLeaderboardRankingsReceived> callbackMapLeaderboardRankingsReceived; 
	mutable TMap<FGuid, FUserInfoReceived> callbackMapUserInfoReceived;

	// ----------------------------------------------------------------------------------
	// Leaderboard V2 Helpers

	mutable TMap<FGuid, FLeaderboardReceivedV2> callbackMapLeaderboardReceivedV2;
	mutable TMap<FGuid, FLeaderboardRankingReceivedV2> callbackMapLeaderboardRankingReceivedV2;
	mutable TMap<FGuid, FLeaderboardRankingsReceivedV2> callbackMapLeaderboardRankingsReceivedV2;
	mutable TMap<FGuid, FLeaderboardsReceivedV2> callbackMapLeaderboardsReceivedV2;

	// ----------------------------------------------------------------------------------
	// Leaderboard Handlers

	void ReceiveGetLeaderboardResponse(const ScillSDK::ScillApiLeaderboardsApi::GetLeaderboardResponse& Response, FGuid guid) const;
	void ReceiveGetLeaderboardRankingResponse(const ScillSDK::ScillApiLeaderboardsApi::GetLeaderboardRankingResponse& Response, FGuid guid) const;
	void ReceiveGetLeaderboardRankingsResponse(const ScillSDK::ScillApiLeaderboardsApi::GetLeaderboardRankingsResponse& Response, FGuid guid) const;
	void ReceiveGetLeaderboardsResponse(const ScillSDK::ScillApiLeaderboardsApi::GetLeaderboardsResponse& Response, FGuid guid) const;
	void ReceiveSetUserInfoResponse(const ScillSDK::ScillApiAuthApi::SetUserInfoResponse& Response, FGuid guid) const;
	void ReceiveGetUserInfoResponse(const ScillSDK::ScillApiAuthApi::GetUserInfoResponse& Response, FGuid guid) const;

	// ----------------------------------------------------------------------------------
	// Leaderboard V2 Handlers

	void ReceiveGetLeaderboardResponseV2(const ScillSDK::ScillApiLeaderboardsV2Api::GetLeaderboardV2Response& Response, FGuid guid) const;
	void ReceiveGetLeaderboardRankingResponseV2(const ScillSDK::ScillApiLeaderboardsV2Api::GetLeaderboardV2RankingResponse& Response, FGuid guid) const;
	void ReceiveGetLeaderboardRankingsResponseV2(const ScillSDK::ScillApiLeaderboardsV2Api::GetLeaderboardV2RankingsResponse& Response, FGuid guid) const;
	void ReceiveGetLeaderboardsResponseV2(const ScillSDK::ScillApiLeaderboardsV2Api::GetLeaderboardsV2Response& Response, FGuid guid) const;
	void ReceiveResetLeaderboardRankingsResponseV2(const ScillSDK::ScillApiLeaderboardsV2Api::ResetLeaderboardV2RankingsResponse& Response, FGuid guid) const;

	// ----------------------------------------------------------------------------------
	// Events Handlers

	void ReceiveSendEventResponse(const ScillSDK::ScillApiEventsApi::SendEventResponse& Response, FGuid guid) const;

	// ----------------------------------------------------------------------------------
	// Realtime Updates Handlers

	void ReceiveBattlePassChangeTopic(const ScillSDK::ScillApiAuthApi::GetUserBattlePassNotificationTopicResponse& Response, FGuid guid) const;
	void ReceiveChallengeChangeTopic(const ScillSDK::ScillApiAuthApi::GetUserChallengesNotificationTopicResponse& Response, FGuid guid) const;
	void ReceiveLeaderboardChangeTopic(const ScillSDK::ScillApiAuthApi::GetLeaderboardNotificationTopicResponse& Response, FGuid guid) const;

	UFUNCTION()
		void MqttConnectionOpen(FGuid guid) const;

	// ----------------------------------------------------------------------------------
	// Realtime Updates Helpers

	mutable TMap<FGuid, FBattlePassChangeReceived> callbackMapBattlePassChangeReceived;
	mutable TMap<FGuid, FChallengeChangeReceived> callbackMapChallengeChangeReceived;
	mutable TMap<FGuid, FLeaderboardChangeReceived> callbackMapLeaderboardChangeReceived;
	mutable TMap<FGuid, FRealtimeConnectionEstablished> callbackMqttConnectionEstablished;

	UFUNCTION()
	void UserInfoRetrieved(const FUserInfo& UserInfo, bool Success);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
