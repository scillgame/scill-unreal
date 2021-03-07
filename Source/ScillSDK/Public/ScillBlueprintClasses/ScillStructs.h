// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScillApiWrapper/ScillApiBattlePass.h"
#include "ScillStructs.generated.h"




/*
* Represents a Battle Pass Object.
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FBattlePass
{
	GENERATED_USTRUCT_BODY();

	/* The unique id of this battle pass. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BattlePassId;
	/* The unique id of the app */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AppId;
	/* The name of the battle bass. You can set that in the Admin Panel. The language is set with the query parameter language. See documentation for more info on that. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BattlePassName;
	/* The description of the battle bass. You can set that in the Admin Panel and it can also be HTML. The language is set with the query parameter language. See documentation for more info on that. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BattlePassDescription;
	/* A short description of the battle bass. You can set that in the Admin Panel and it can also be HTML. The language is set with the query parameter language. See documentation for more info on that. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BattlePassShortDescription;
	/* Use this to provide some terms and conditions following along this battle passes purchase. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BattlePassDisclaimer;
	/* The priority of the battle pass. I.e. if multiple are available you can use this field to sort them. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BattlePassPriority;
	/* If you want to sell Battle Passes you can use this field to trigger in-app purchase products within your mobile app. You can set this value in the Admin Panel. This one is for iOS. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PackageSkuIos;
	/* If you want to sell Battle Passes you can use this field to trigger in-app purchase products within your mobile app. You can set this value in the Admin Panel. Use this to set the package string for Android. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PackageSkuAndroid;
	/* The xs sized image name or url. You can determine the best size distribution yourself and depends on your application or UI */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ImageXs;
	/* The s sized image name or url. You can determine the best size distribution yourself and depends on your application or UI */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ImageS;
	/* The m sized image name or url. You can determine the best size distribution yourself and depends on your application or UI */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ImageM;
	/* The l sized image name or url. You can determine the best size distribution yourself and depends on your application or UI */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ImageL;
	/* The xl sized image name or url. You can determine the best size distribution yourself and depends on your application or UI */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ImageXl;
	/* The date (in iso format) when the Battle Pass starts. Tracking begins once this date is passed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString StartDate;
	/* The date (in iso format) when the Battle Pass ends. Tracking stops once the end is reached and users will not be able to progress further than what they have achieved up to that point. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString EndDate;
	/* If the Battle Pass costs “money” you may want to route the user to a web site/page, where they can learn more about this battle pass. You can also use this field to route the user inside your application by providing a path or whatever works for you. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ReadMoreLink;
	/* Indicates if one level after the other must be activated or if users can activate whichever level they want. Typically battle passes are unlocked level by level, but if battle passes are used for other applications (like user referal programs) it can be useful to set this to false. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsUnlockedIncrementally;
	/* Indicated if this battle pass is active. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsActive;
	/* The date in iso format when the user unlocked this Battle Pass. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString UnlockedAt;
	/* Indicates that this Battle Pass can be purchased via in-app purchase. This can be set in the Admin Panel. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CanPurchaseWithMoney;
	/* Indicates that this Battle Pass can be purchased with SCILL Coins. This can be set in the Admin Panel. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CanPurchaseWithCoins;

	static FBattlePass FromScillApiBattlePass(const ScillSDK::ScillApiBattlePass battlePass);
};
