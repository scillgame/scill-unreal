// Fill out your copyright notice in the Description page of Project Settings.


#include "ScillBlueprintClasses/ScillClient.h"

// Sets default values for this component's properties
UScillClient::UScillClient()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UScillClient::SetAccessToken(FString newAccessToken)
{
	this->battlePassesApi.AddHeaderParam("Authorization", "Bearer " + newAccessToken);
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

	// ...
	
}

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

	callbackMapResponseReceived.Remove(guid);
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

	callbackMapResponseReceived.Remove(guid);
}


// Called every frame
void UScillClient::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

