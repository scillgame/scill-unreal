// Fill out your copyright notice in the Description page of Project Settings.


#include "ScillBlueprintClasses/ScillClient.h"

// Sets default values for this component's properties
UScillClient::UScillClient()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	mqtt = NewObject<UScillMqtt>();

	// ...
}

void UScillClient::SetAccessToken(FString newAccessToken)
{
	this->battlePassesApi.AddHeaderParam("Authorization", "Bearer " + newAccessToken);
	this->challengesApi.AddHeaderParam("Authorization", "Bearer " + newAccessToken);
	this->eventsApi.AddHeaderParam("Authorization", "Bearer " + newAccessToken);
	this->authApi.AddHeaderParam("Authorization", "Bearer " + newAccessToken);
	this->AccessToken = newAccessToken;
	
	auto gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (gameInstance->Implements<UScillLevelPersistenceInterface>())
	{
		IScillLevelPersistenceInterface::Execute_SetAccessToken(gameInstance, newAccessToken);
	}
}

FString UScillClient::GetAccessToken() const
{
	auto value = FString();

	auto gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (gameInstance->Implements<UScillLevelPersistenceInterface>())
	{
		IScillLevelPersistenceInterface::Execute_GetAccessToken(gameInstance, value);
	}

	return value;
}

FString UScillClient::GetUserId() const
{
	auto value = FString();

	auto gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (gameInstance->Implements<UScillLevelPersistenceInterface>())
	{
		IScillLevelPersistenceInterface::Execute_GetUserId(gameInstance, value);
	}

	return value;
}

void UScillClient::SetUserId(FString newUserId)
{
	this->UserId = newUserId;

	auto gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (gameInstance->Implements<UScillLevelPersistenceInterface>())
	{
		IScillLevelPersistenceInterface::Execute_SetUserId(gameInstance, newUserId);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------
// Battle Passes
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ActivateBattlePassLevel(FString levelId, FHttpResponseReceived responseReceived)
{
	auto activateBattlePassRequest = ScillSDK::ScillApiBattlePassesApi::ActivateBattlePassLevelRequest();

	activateBattlePassRequest.AppId = AppId;
	activateBattlePassRequest.LevelId = levelId;

	FGuid guid = FGuid::NewGuid();

	callbackMapResponseReceived.Add(guid, responseReceived);

	auto activateBattlePassRequestDelegate = ScillSDK::ScillApiBattlePassesApi::FActivateBattlePassLevelDelegate::CreateUObject(this, &UScillClient::ReceiveActivateBattlePassLevelResponse, guid);
	
	battlePassesApi.ActivateBattlePassLevel(activateBattlePassRequest, activateBattlePassRequestDelegate);
}

void UScillClient::ClaimBattlePassLevel(FString levelId, FHttpResponseReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::ClaimBattlePassLevelRewardRequest();

	request.AppId = AppId;
	request.LevelId = levelId;

	FGuid guid = FGuid::NewGuid();

	callbackMapResponseReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FClaimBattlePassLevelRewardDelegate::CreateUObject(this, &UScillClient::ReceiveClaimBattlePassLevelResponse, guid);

	battlePassesApi.ClaimBattlePassLevelReward(request, delegate);
}

void UScillClient::GetActiveBattlePasses(FBattlePassArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::GetActiveBattlePassesRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FGetActiveBattlePassesDelegate::CreateUObject(this, &UScillClient::ReceiveActiveBattlePassesResponse, guid);

	battlePassesApi.GetActiveBattlePasses(request, delegate);
}

void UScillClient::GetUnlockedPasses(FBattlePassArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::GetUnlockedBattlePassesRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FGetUnlockedBattlePassesDelegate::CreateUObject(this, &UScillClient::ReceiveUnlockedBattlePassesResponse, guid);

	battlePassesApi.GetUnlockedBattlePasses(request, delegate);
}

void UScillClient::GetAllPassLevels(FBattlePassLevelArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::GetAllBattlePassLevelsRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassLevelArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FGetAllBattlePassLevelsDelegate::CreateUObject(this, &UScillClient::ReceiveAllBattlePassLevelsResponse, guid);

	battlePassesApi.GetAllBattlePassLevels(request, delegate);
}

void UScillClient::GetBattlePass(FString battlePassId, FBattlePassReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::GetBattlePassRequest();

	request.AppId = AppId;
	request.BattlePassId = battlePassId;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FGetBattlePassDelegate::CreateUObject(this, &UScillClient::ReceiveBattlePassResponse, guid);

	battlePassesApi.GetBattlePass(request, delegate);
}

void UScillClient::GetBattlePassLevels(FString battlePassId, FBattlePassLevelArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::GetBattlePassLevelsRequest();

	request.AppId = AppId;
	request.BattlePassId = battlePassId;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassLevelArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FGetBattlePassLevelsDelegate::CreateUObject(this, &UScillClient::ReceiveBattlePassLevelsResponse, guid);

	battlePassesApi.GetBattlePassLevels(request, delegate);
}

void UScillClient::GetBattlePasses(FBattlePassArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::GetBattlePassesRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FGetBattlePassesDelegate::CreateUObject(this, &UScillClient::ReceiveBattlePassesResponse, guid);

	battlePassesApi.GetBattlePasses(request, delegate);
}

void UScillClient::UnlockBattlePass(FString battlePassId, float purchasePrice, FString purchaseCurrency, FBattlePassUnlockInfoReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::UnlockBattlePassRequest();

	request.AppId = AppId;
	request.BattlePassId = battlePassId;

	auto unlockPayload = ScillSDK::ScillApiBattlePassUnlockPayload();
	unlockPayload.PurchasePrice = purchasePrice;
	unlockPayload.PurchaseCurrency = purchaseCurrency;

	request.ScillApiBattlePassUnlockPayload = unlockPayload;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassUnlockInfoReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FUnlockBattlePassDelegate::CreateUObject(this, &UScillClient::ReceiveUnlockBattlePassResponse, guid);

	battlePassesApi.UnlockBattlePass(request, delegate);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Challenges
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ActivatePersonalChallenge(FString challengeId, FChallengeReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::ActivatePersonalChallengeRequest();

	request.AppId = AppId;
	request.ChallengeId = challengeId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FActivatePersonalChallengeDelegate::CreateUObject(this, &UScillClient::ReceiveActivatePersonalChallengeResponse, guid);

	challengesApi.ActivatePersonalChallenge(request, delegate);
}

void UScillClient::CancelPersonalChallenge(FString challengeId, FChallengeReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::CancelPersonalChallengeRequest();

	request.AppId = AppId;
	request.ChallengeId = challengeId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FCancelPersonalChallengeDelegate::CreateUObject(this, &UScillClient::ReceiveCancelPersonalChallengeResponse, guid);

	challengesApi.CancelPersonalChallenge(request, delegate);
}

void UScillClient::ClaimPersonalChallengeReward(FString challengeId, FChallengeReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::ClaimPersonalChallengeRewardRequest();

	request.AppId = AppId;
	request.ChallengeId = challengeId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FClaimPersonalChallengeRewardDelegate::CreateUObject(this, &UScillClient::ReceiveClaimPersonalChallengeRewardResponse, guid);

	challengesApi.ClaimPersonalChallengeReward(request, delegate);
}

void UScillClient::GetActivePersonalChallenges(FChallengeCategoryArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::GetActivePersonalChallengesRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeCategoryArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FGetActivePersonalChallengesDelegate::CreateUObject(this, &UScillClient::ReceiveGetActivePersonalChallengesResponse, guid);

	challengesApi.GetActivePersonalChallenges(request, delegate);
}

void UScillClient::GetAllPersonalChallenges(FChallengeCategoryArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::GetAllPersonalChallengesRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeCategoryArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FGetAllPersonalChallengesDelegate::CreateUObject(this, &UScillClient::ReceiveGetAllPersonalChallengesResponse, guid);

	challengesApi.GetAllPersonalChallenges(request, delegate);
}

void UScillClient::GetPersonalChallenges(FChallengeCategoryArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::GetPersonalChallengesRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeCategoryArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FGetPersonalChallengesDelegate::CreateUObject(this, &UScillClient::ReceiveGetPersonalChallengesResponse, guid);

	challengesApi.GetPersonalChallenges(request, delegate);
}

void UScillClient::GetUnresolvedPersonalChallenges(FChallengeCategoryArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::GetUnresolvedPersonalChallengesRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeCategoryArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FGetUnresolvedPersonalChallengesDelegate::CreateUObject(this, &UScillClient::ReceiveGetUnresolvedPersonalChallengesResponse, guid);

	challengesApi.GetUnresolvedPersonalChallenges(request, delegate);
}

void UScillClient::GetPersonalChallengeById(FString challengeId, FChallengeReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::GetPersonalChallengeByIdRequest();

	request.AppId = AppId;
	request.ChallengeId = challengeId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FGetPersonalChallengeByIdDelegate::CreateUObject(this, &UScillClient::ReceiveGetPersonalChallengeByIdResponse, guid);

	challengesApi.GetPersonalChallengeById(request, delegate);
}

void UScillClient::UnlockPersonalChallenge(FString challengeId, FChallengeReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::UnlockPersonalChallengeRequest();

	request.AppId = AppId;
	request.ChallengeId = challengeId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FUnlockPersonalChallengeDelegate::CreateUObject(this, &UScillClient::ReceiveUnlockPersonalChallengeResponse, guid);

	challengesApi.UnlockPersonalChallenge(request, delegate);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Events
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::SendEvent(FScillEventPayload payload, FHttpResponseReceived responseReceived)
{
	auto request = ScillSDK::ScillApiEventsApi::SendEventRequest();

	request.ScillApiEventPayload = FScillEventPayload::ToScillApiEventPayload(payload);

	FGuid guid = FGuid::NewGuid();

	callbackMapResponseReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiEventsApi::FSendEventDelegate::CreateUObject(this, &UScillClient::ReceiveSendEventResponse, guid);

	eventsApi.SendEvent(request, delegate);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Realtime Updates
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ReceiveBattlePassUpdates(FString battlePassId, FBattlePassChangeReceived responseReceived)
{
	auto request = ScillSDK::ScillApiAuthApi::GetUserBattlePassNotificationTopicRequest();

	request.BattlePassId = battlePassId;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassChangeReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiAuthApi::FGetUserBattlePassNotificationTopicDelegate::CreateUObject(this, &UScillClient::ReceiveBattlePassChangeTopic, guid);

	authApi.GetUserBattlePassNotificationTopic(request, delegate);
}


// ----------------------------------------------------------------------------------------------------------------------------
// UActor Event Implementations
// ----------------------------------------------------------------------------------------------------------------------------

// Called when the game starts
void UScillClient::BeginPlay()
{
	Super::BeginPlay();

	auto accessToken = FString();
	auto userId = FString();

	auto gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (gameInstance->Implements<UScillLevelPersistenceInterface>())
	{
		IScillLevelPersistenceInterface::Execute_GetAccessToken(gameInstance, accessToken);
		IScillLevelPersistenceInterface::Execute_GetUserId(gameInstance, userId);
	}

	// Set access token to value of level persistence
	if (!accessToken.IsEmpty())
		this->AccessToken = accessToken;

	if (!userId.IsEmpty())
		this->UserId = userId;

	SetAccessToken(this->AccessToken);
	SetUserId(this->UserId);

	this->battlePassesApi.AddHeaderParam("Authorization", "Bearer " + this->AccessToken);
	this->battlePassesApi.SetURL(TEXT("https://es.scillgame.com"));

	this->challengesApi.AddHeaderParam("Authorization", "Bearer " + this->AccessToken);
	this->challengesApi.SetURL(TEXT("https://pcs.scillgame.com"));

	this->eventsApi.AddHeaderParam("Authorization", "Bearer " + this->AccessToken);
	this->eventsApi.SetURL(TEXT("https://ep.scillgame.com"));

	this->authApi.AddHeaderParam("Authorization", "Bearer " + this->AccessToken);
	this->authApi.SetURL(TEXT("https://us.scillgame.com"));
	
}

// ----------------------------------------------------------------------------------------------------------------------------
// Battle Passes Handlers
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ReceiveActivateBattlePassLevelResponse(const ScillSDK::ScillApiBattlePassesApi::ActivateBattlePassLevelResponse& Response, FGuid guid) const
{
	auto callback = callbackMapResponseReceived.FindRef(guid);
	callback.ExecuteIfBound(Response.IsSuccessful());

	callbackMapResponseReceived.Remove(guid);
}

void UScillClient::ReceiveClaimBattlePassLevelResponse(const ScillSDK::ScillApiBattlePassesApi::ClaimBattlePassLevelRewardResponse& Response, FGuid guid) const
{
	auto callback = callbackMapResponseReceived.FindRef(guid);
	callback.ExecuteIfBound(Response.IsSuccessful());

	callbackMapResponseReceived.Remove(guid);
}

void UScillClient::ReceiveActiveBattlePassesResponse(const ScillSDK::ScillApiBattlePassesApi::GetActiveBattlePassesResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassArrayReceived.FindRef(guid);

	TArray<FBattlePass> battlePasses = TArray<FBattlePass>();

	for (auto bp : Response.Content)
	{
		battlePasses.Add(FBattlePass::FromScillApiBattlePass(bp));
	}

	callback.ExecuteIfBound(battlePasses,Response.IsSuccessful());

	callbackMapBattlePassArrayReceived.Remove(guid);
}

void UScillClient::ReceiveUnlockedBattlePassesResponse(const ScillSDK::ScillApiBattlePassesApi::GetUnlockedBattlePassesResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassArrayReceived.FindRef(guid);

	TArray<FBattlePass> battlePasses = TArray<FBattlePass>();

	for (auto bp : Response.Content)
	{
		battlePasses.Add(FBattlePass::FromScillApiBattlePass(bp));
	}

	callback.ExecuteIfBound(battlePasses, Response.IsSuccessful());

	callbackMapBattlePassArrayReceived.Remove(guid);
}

void UScillClient::ReceiveAllBattlePassLevelsResponse(const ScillSDK::ScillApiBattlePassesApi::GetAllBattlePassLevelsResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassLevelArrayReceived.FindRef(guid);

	TArray<FBattlePassLevel> battlePasses = TArray<FBattlePassLevel>();

	for (auto bp : Response.Content)
	{
		battlePasses.Add(FBattlePassLevel::FromScillApiBattlePassLevel(bp));
	}

	callback.ExecuteIfBound(battlePasses, Response.IsSuccessful());

	callbackMapBattlePassLevelArrayReceived.Remove(guid);
}

void UScillClient::ReceiveBattlePassResponse(const ScillSDK::ScillApiBattlePassesApi::GetBattlePassResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassReceived.FindRef(guid);

	callback.ExecuteIfBound(FBattlePass::FromScillApiBattlePass(Response.Content), Response.IsSuccessful());

	callbackMapBattlePassReceived.Remove(guid);
}

void UScillClient::ReceiveBattlePassLevelsResponse(const ScillSDK::ScillApiBattlePassesApi::GetBattlePassLevelsResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassLevelArrayReceived.FindRef(guid);

	TArray<FBattlePassLevel> battlePassLevels = TArray<FBattlePassLevel>();

	for (auto bp : Response.Content)
	{
		battlePassLevels.Add(FBattlePassLevel::FromScillApiBattlePassLevel(bp));
	}

	callback.ExecuteIfBound(battlePassLevels, Response.IsSuccessful());

	callbackMapBattlePassLevelArrayReceived.Remove(guid);
}

void UScillClient::ReceiveBattlePassesResponse(const ScillSDK::ScillApiBattlePassesApi::GetBattlePassesResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassArrayReceived.FindRef(guid);

	TArray<FBattlePass> battlePasses = TArray<FBattlePass>();

	for (auto bp : Response.Content)
	{
		battlePasses.Add(FBattlePass::FromScillApiBattlePass(bp));
	}

	callback.ExecuteIfBound(battlePasses, Response.IsSuccessful());

	callbackMapBattlePassArrayReceived.Remove(guid);
}

void UScillClient::ReceiveUnlockBattlePassResponse(const ScillSDK::ScillApiBattlePassesApi::UnlockBattlePassResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassUnlockInfoReceived.FindRef(guid);

	callback.ExecuteIfBound(FBattlePassUnlockInfo::FromScillApiBattlePassUnlockInfo(Response.Content), Response.IsSuccessful());

	callbackMapBattlePassUnlockInfoReceived.Remove(guid);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Challenges Handlers
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ReceiveActivatePersonalChallengeResponse(const ScillSDK::ScillApiChallengesApi::ActivatePersonalChallengeResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeReceived.FindRef(guid);

	callback.ExecuteIfBound(FChallenge::FromScillApiChallenge(Response.Content.Challenge.Get(ScillSDK::ScillApiChallenge())), Response.IsSuccessful());

	callbackMapChallengeReceived.Remove(guid);
}

void UScillClient::ReceiveCancelPersonalChallengeResponse(const ScillSDK::ScillApiChallengesApi::CancelPersonalChallengeResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeReceived.FindRef(guid);

	callback.ExecuteIfBound(FChallenge::FromScillApiChallenge(Response.Content.Challenge.Get(ScillSDK::ScillApiChallenge())), Response.IsSuccessful());

	callbackMapChallengeReceived.Remove(guid);
}

void UScillClient::ReceiveClaimPersonalChallengeRewardResponse(const ScillSDK::ScillApiChallengesApi::ClaimPersonalChallengeRewardResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeReceived.FindRef(guid);

	callback.ExecuteIfBound(FChallenge::FromScillApiChallenge(Response.Content.Challenge.Get(ScillSDK::ScillApiChallenge())), Response.IsSuccessful());

	callbackMapChallengeReceived.Remove(guid);
}

void UScillClient::ReceiveGetActivePersonalChallengesResponse(const ScillSDK::ScillApiChallengesApi::GetActivePersonalChallengesResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeCategoryArrayReceived.FindRef(guid);

	TArray<FChallengeCategory> challengeCategories = TArray<FChallengeCategory>();

	for (auto c : Response.Content)
	{
		challengeCategories.Add(FChallengeCategory::FromScillApiChallengeCategory(c));
	}

	callback.ExecuteIfBound(challengeCategories, Response.IsSuccessful());

	callbackMapChallengeCategoryArrayReceived.Remove(guid);
}

void UScillClient::ReceiveGetAllPersonalChallengesResponse(const ScillSDK::ScillApiChallengesApi::GetAllPersonalChallengesResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeCategoryArrayReceived.FindRef(guid);

	TArray<FChallengeCategory> challengeCategories = TArray<FChallengeCategory>();

	for (auto c : Response.Content)
	{
		challengeCategories.Add(FChallengeCategory::FromScillApiChallengeCategory(c));
	}

	callback.ExecuteIfBound(challengeCategories, Response.IsSuccessful());

	callbackMapChallengeCategoryArrayReceived.Remove(guid);
}

void UScillClient::ReceiveGetPersonalChallengesResponse(const ScillSDK::ScillApiChallengesApi::GetPersonalChallengesResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeCategoryArrayReceived.FindRef(guid);

	TArray<FChallengeCategory> challengeCategories = TArray<FChallengeCategory>();

	for (auto c : Response.Content)
	{
		challengeCategories.Add(FChallengeCategory::FromScillApiChallengeCategory(c));
	}

	callback.ExecuteIfBound(challengeCategories, Response.IsSuccessful());

	callbackMapChallengeCategoryArrayReceived.Remove(guid);
}

void UScillClient::ReceiveGetUnresolvedPersonalChallengesResponse(const ScillSDK::ScillApiChallengesApi::GetUnresolvedPersonalChallengesResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeCategoryArrayReceived.FindRef(guid);

	TArray<FChallengeCategory> challengeCategories = TArray<FChallengeCategory>();

	for (auto c : Response.Content)
	{
		challengeCategories.Add(FChallengeCategory::FromScillApiChallengeCategory(c));
	}

	callback.ExecuteIfBound(challengeCategories, Response.IsSuccessful());

	callbackMapChallengeCategoryArrayReceived.Remove(guid);
}

void UScillClient::ReceiveGetPersonalChallengeByIdResponse(const ScillSDK::ScillApiChallengesApi::GetPersonalChallengeByIdResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeReceived.FindRef(guid);

	callback.ExecuteIfBound(FChallenge::FromScillApiChallenge(Response.Content), Response.IsSuccessful());

	callbackMapChallengeReceived.Remove(guid);
}

void UScillClient::ReceiveUnlockPersonalChallengeResponse(const ScillSDK::ScillApiChallengesApi::UnlockPersonalChallengeResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeReceived.FindRef(guid);

	callback.ExecuteIfBound(FChallenge::FromScillApiChallenge(Response.Content.Challenge.Get(ScillSDK::ScillApiChallenge())), Response.IsSuccessful());

	callbackMapChallengeReceived.Remove(guid);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Events Handlers
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ReceiveSendEventResponse(const ScillSDK::ScillApiEventsApi::SendEventResponse& Response, FGuid guid) const
{
	auto callback = callbackMapResponseReceived.FindRef(guid);
	callback.ExecuteIfBound(Response.IsSuccessful());

	callbackMapResponseReceived.Remove(guid);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Realtime Updates Handlers
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ReceiveBattlePassChangeTopic(const ScillSDK::ScillApiAuthApi::GetUserBattlePassNotificationTopicResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassChangeReceived.FindRef(guid);

	mqtt->SubscribeToTopic(Response.Content.Topic);

	callbackMapResponseReceived.Remove(guid);
}

// Called every frame
void UScillClient::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

