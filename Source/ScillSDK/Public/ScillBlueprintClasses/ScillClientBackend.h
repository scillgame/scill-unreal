#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ScillSDK.h"
#include "ScillApiWrapper/ScillApiAuthApi.h"
#include "ScillApiWrapper/ScillApiAuthApiOperations.h"
#include "ScillClientBackend.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAccessTokenGenerated, FString, Token, bool, Success);

/* This is the entry component for your game's server logic in regards of the SCILL API. This component uses the API Key of your App and should not be created on the client - so best place it on your GameMode class. */

UCLASS(meta = (BlueprintSpawnableComponent))
class SCILLSDK_API UScillClientBackend : public UActorComponent
{
	GENERATED_BODY()
public:
	/* This changes the set API Key for your app. A good practice is to read the API Key from a configuration file that is not accessible to your Client. */
	UFUNCTION(BlueprintCallable)
		void SetApiKey(FString apiKey);

	/* This is best set by reading it from a configuration file unaccessible to your Clients. So normally you should not set it from Editor. Only use this property for testing purposes. */
	UPROPERTY(EditDefaultsOnly)
		FString ApiKey;

	/* Requests an access token that you can then pass to your client. The client can the authenticate itself to your SCILL APP as the user with the passed user id. */
	UFUNCTION(BlueprintCallable)
		void GenerateAccessToken(FString userId);

	/* Delegate that is called once the Access Token was generated. Assign an Event or Function to it to pass the access token to the respective Client. */
	UPROPERTY(BlueprintAssignable)
		FAccessTokenGenerated AccessTokenGenerated;

	virtual void BeginPlay() override;

private:
	ScillSDK::ScillApiAuthApi authApi;

	void ReceiveAccessTokenResponse(const ScillSDK::ScillApiAuthApi::GenerateAccessTokenResponse& Response);
};

