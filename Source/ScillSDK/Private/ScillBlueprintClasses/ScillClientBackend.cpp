#include "ScillBlueprintClasses/ScillClientBackend.h"

void UScillClientBackend::SetApiKey(FString apiKey)
{
	this->authApi.AddHeaderParam("Authorization", "Bearer " + apiKey);
	this->ApiKey = apiKey;
	//UE_LOG(LogScillSDK, Log, TEXT("API Key Created: %s"), *apiKey);
}

void UScillClientBackend::GenerateAccessToken(FString userId, const FReceiveAccessToken& OnAccessTokenGenerated)
{
	auto accessTokenRequest = ScillSDK::ScillApiAuthApi::GenerateAccessTokenRequest();

	accessTokenRequest.ScillApiForeignUserIdentifier = ScillSDK::ScillApiForeignUserIdentifier();
	accessTokenRequest.ScillApiForeignUserIdentifier.UserId = userId;

	FGuid guid = FGuid::NewGuid();

	callbackMapReceiveAccessToken.Add(guid, OnAccessTokenGenerated);

	auto generateAccessTokenDelegate = ScillSDK::ScillApiAuthApi::FGenerateAccessTokenDelegate::CreateUObject(this, &UScillClientBackend::ReceiveAccessTokenResponse, guid);

	authApi.GenerateAccessToken(accessTokenRequest, generateAccessTokenDelegate);
}

void UScillClientBackend::StartMonitorBattlePassUpdates(FString accessToken, const FReceiveBattlePassUpdate& battlePassIFReceiveBattlePassUpdate callback)
{
}

void UScillClientBackend::BeginPlay()
{
	Super::BeginPlay();

	this->authApi.AddHeaderParam("Authorization", "Bearer " + this->ApiKey);
	//UE_LOG(LogScillSDK, Log, TEXT("API Key Created: %s"), *this->ApiKey);
}

void UScillClientBackend::ReceiveAccessTokenResponse(const ScillSDK::ScillApiAuthApi::GenerateAccessTokenResponse& Response, FGuid guid) const
{
	bool isSuccessful = Response.IsSuccessful();
	FString token = isSuccessful ? Response.Content.Token.GetValue() : "";

	auto callback = callbackMapReceiveAccessToken.FindRef(guid);
	callback.ExecuteIfBound(token, isSuccessful);
}
