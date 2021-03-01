#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "ScillSDK.h"
#include "ScillApiWrapper/ScillApiAuthApi.h"
#include "ScillApiWrapper/ScillApiAuthApiOperations.h"
#include "Misc/Guid.h"
#include "ScillClientBackend.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FReceiveAccessToken, FString, Token, bool, Success);

/* This is the entry component for your game's server logic in regards of the SCILL API. This component uses the API Key of your App and should not be created on the client - so best place it on your GameMode class. */
UCLASS(meta = (BlueprintSpawnableComponent))
class SCILLSDK_API UScillClientBackend : public UActorComponent
{

	GENERATED_BODY()
public:

	// SETUP

	/* This changes the set API Key for your app. A good practice is to read the API Key from a configuration file that is not accessible to your Client. */
	UFUNCTION(BlueprintCallable)
		void SetApiKey(FString apiKey);

	/* This is best set by reading it from a configuration file unaccessible to your Clients. So normally you should not set it from Editor. Only use this property for testing purposes. */
	UPROPERTY(EditDefaultsOnly)
		FString ApiKey;

	virtual void BeginPlay() override;

	// Generate Access Token

	/* Requests an access token that you can then pass to your client. The client can the authenticate itself to your SCILL APP as the user with the passed user id. */
	UFUNCTION(BlueprintCallable)
		void GenerateAccessToken(FString userId, const FReceiveAccessToken& OnAccessTokenGenerated);

	// Start Monitor Battlepass Updates

	/* Starts to monitor Battlepass updates. */
	/*UFUNCTION(BlueprintCallable)
		void StartMonitorBattlePassUpdates(FString accessToken);*/

private:
	ScillSDK::ScillApiAuthApi authApi;

	TMap<FGuid, FReceiveAccessToken> callbackMapReceiveAccessToken;

	void ReceiveAccessTokenResponse(const ScillSDK::ScillApiAuthApi::GenerateAccessTokenResponse& Response, FGuid guid) const;
};

