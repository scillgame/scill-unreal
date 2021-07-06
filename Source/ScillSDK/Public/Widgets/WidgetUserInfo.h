// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"
#include "WidgetUserInfo.generated.h"

/**
 * 
 */
UCLASS()
class SCILLSDK_API UWidgetUserInfo : public UUserWidget
{
	GENERATED_BODY()
public:

	UWidgetUserInfo(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UScillClient* ScillClient;

	UPROPERTY(meta = (BindWidgetOptional))
		UButton* SetUserData;

	UPROPERTY(meta = (BindWidgetOptional))
		UEditableText* UserName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString AvatarImage;
private:
	UFUNCTION()
		void SetUserDataClicked();

	void QueryUserInfo();

	UFUNCTION()
	void ReceiveUserInfo(const FUserInfo& UserInfo, bool Success);
};
