// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScillApiWrapper/ScillApiBattlePassesApi.h"
#include "ScillApiWrapper/ScillApiBattlePassesApiOperations.h"
#include "ScillBlueprintClasses/ScillStructs.h"
#include "ScillBlueprintClasses/ScillLevelPersistenceInterface.h"
#include "Kismet/GameplayStatics.h"
#include "ScillClient.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FHttpResponseReceived, bool, Success);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FBattlePassArrayReceived, const TArray<FBattlePass>&, BattlePasses, bool, Success);


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

	/* You can set a user id for testing purposes here. If set during runtime use the SetUserId function. */
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

	UFUNCTION(BlueprintCallable)
		void ActivateBattlePassLevel(FString levelId, FHttpResponseReceived responseReceived);

	UFUNCTION(BlueprintCallable)
		void ClaimBattlePassLevel(FString levelId, FHttpResponseReceived responseReceived);

	UFUNCTION(BlueprintCallable)
		void GetActiveBattlePasses(FBattlePassArrayReceived responseReceived);

	UFUNCTION(BlueprintCallable)
		void GetUnlockedPasses(FBattlePassArrayReceived responseReceived);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	ScillSDK::ScillApiBattlePassesApi battlePassesApi;

	void ReceiveActivateBattlePassLevelResponse(const ScillSDK::ScillApiBattlePassesApi::ActivateBattlePassLevelResponse& Response, FGuid guid) const;
	void ReceiveClaimBattlePassLevelResponse(const ScillSDK::ScillApiBattlePassesApi::ClaimBattlePassLevelRewardResponse& Response, FGuid guid) const;
	void ReceiveActiveBattlePassesResponse(const ScillSDK::ScillApiBattlePassesApi::GetActiveBattlePassesResponse& Response, FGuid guid) const;
	void ReceiveUnlockedBattlePassesResponse(const ScillSDK::ScillApiBattlePassesApi::GetUnlockedBattlePassesResponse& Response, FGuid guid) const;

	// ----------------------------------------------------------------------------------
	// Battle Passes Helpers

	mutable TMap<FGuid, FHttpResponseReceived> callbackMapResponseReceived;
	mutable TMap<FGuid, FBattlePassArrayReceived> callbackMapBattlePassArrayReceived;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
