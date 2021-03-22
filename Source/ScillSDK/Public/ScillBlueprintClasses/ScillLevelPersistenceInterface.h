// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScilllevelpersistenceInterface.generated.h"

/**
 * Implement this interface on your game instance class. This is used to uniformly retrieve and store the client's access token and user id.
 * If the GetAccessToken or GetUserId functions return anything but an empty string on startup of the game it will overwrite the settings in the ScillClient Component.
 */
UINTERFACE(Blueprintable)
class UScillLevelPersistenceInterface : public UInterface
{
	GENERATED_BODY()
};

class SCILLSDK_API IScillLevelPersistenceInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ScillSDK")
		void SetAccessToken(const FString& token);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ScillSDK")
		void GetAccessToken(FString& token) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ScillSDK")
		void SetUserId(const FString& userId);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ScillSDK")
		void GetUserId(FString& userId) const;
};
