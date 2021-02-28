#include "ScillBlueprintClasses/ScillClientBackend.h"

void UScillClientBackend::SetApiKey(FString apiKey)
{
	this->authApi.AddHeaderParam("Authorization", "Bearer " + apiKey);
	this->ApiKey = apiKey;
	UE_LOG(LogScillSDK, Log, TEXT("API Key Created: %s"), *apiKey);
}

void UScillClientBackend::GenerateAccessToken(FString userId)
{
	auto accessTokenRequest = ScillSDK::ScillApiAuthApi::GenerateAccessTokenRequest();

	accessTokenRequest.ScillApiForeignUserIdentifier = ScillSDK::ScillApiForeignUserIdentifier();
	accessTokenRequest.ScillApiForeignUserIdentifier.UserId = userId;

	auto generateAccessTokenDelegate = ScillSDK::ScillApiAuthApi::FGenerateAccessTokenDelegate::CreateUObject(this, &UScillClientBackend::ReceiveAccessTokenResponse);

	authApi.GenerateAccessToken(accessTokenRequest, generateAccessTokenDelegate);
}

void UScillClientBackend::BeginPlay()
{
	Super::BeginPlay();

	this->authApi.AddHeaderParam("Authorization", "Bearer " + this->ApiKey);
	UE_LOG(LogScillSDK, Log, TEXT("API Key Created: %s"), *this->ApiKey);
}

void UScillClientBackend::ReceiveAccessTokenResponse(const ScillSDK::ScillApiAuthApi::GenerateAccessTokenResponse& Response)
{
	bool isSuccessful = Response.IsSuccessful();
	FString token = isSuccessful ? Response.Content.Token.GetValue() : "";

	AccessTokenGenerated.Broadcast(token, isSuccessful);
}
