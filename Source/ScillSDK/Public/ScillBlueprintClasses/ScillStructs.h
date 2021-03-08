// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScillApiWrapper/ScillApiBattlePass.h"
#include "ScillApiWrapper/ScillApiBattlePassLevel.h"
#include "ScillApiWrapper/ScillApiBattlePassUnlockInfo.h"
#include "ScillStructs.generated.h"

/*
*  Gives information about an unlocking process on a battle pass.
*/

USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FBattlePassUnlockInfo
{
	GENERATED_USTRUCT_BODY();

	static FBattlePassUnlockInfo FromScillApiBattlePassUnlockInfo(const ScillSDK::ScillApiBattlePassUnlockInfo o);

	/* The id of this battle pass purchase */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PurchaseId;
	/* The battle pass id */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString BattlePassId;
	/* The user id of this battle pass purchase */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString UserId;
	/* The price paid for this battle pass */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PurchasePrice;
	/* The currency used to purchase this battle pass */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PurchaseCurrency;
	/* The date this battle pass has been purchased */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PurchasedAt;
	/* Indicates if this battle pass has been completed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool BattlePassCompleted;
};

/*
* Represents the Translation of a Battle Pass.
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FBattlePassTranslation
{
	GENERATED_USTRUCT_BODY();

	/* The id of the language */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LanguageId;
	/* The name of the Battle Pass in the local language set in the request (see Setting Language). In the admin panel you can either create HTML content or plain text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	/* The description of the Battle Pass in the local language set in the request (see Setting Language). In the admin panel you can either create HTML content or plain text. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description;
	/* A short description in the local language you can use to teaser battle passes or implement “expand for more” functionality. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ShortDescription;
	/* Use this to provide some terms and conditions following along this battle passes purchase. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Disclaimer;
};

/*
*  Represents a Battle Pass State
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FBattlePassState
{
	GENERATED_USTRUCT_BODY();

	/* The unique id of this battle pass. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString BattlePassId;
	/* The unique id of the app */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString AppId;
	/* The priority of the battle pass. I.e. if multiple are available you can use this field to sort them. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 BattlePassPriority;
	/* The date (in iso format) when the Battle Pass starts. Tracking begins once this date is passed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString StartDate;
	/* The date (in iso format) when the Battle Pass ends. Tracking stops once the end is reached and users will not be able to progress further than what they have achieved up to that point. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString EndDate;
	/* Indicated if this battle pass is active. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsActive;
};

/*
*  Represents a Battle Pass Level Reward.
*/

USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FBattlePassLevelReward
{
	GENERATED_USTRUCT_BODY();

	/* The unique id of the app */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString AppId;
	/* The unique id of this battle pass. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString BattlePassId;
	/* Unique id of this BattlePassLevel object. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LevelId;
	/* This is your user id. You can set this to whatever you like, either your real user id or an obfuscated user id. However you need to be consistent here. Events linked to this user id only track if challenges or battle passes are unlocked with the same user id. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString UserId;
	/* Typical usage pattern is to load battle pass levels with getBattlePassLevels operation and store them for rendering. Using this value you can quickly identify the index of the level that changed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 LevelPositionIndex;
	/* In the Admin Panel you can set different types of rewards. You can also set an identifier of an in-game-item or anything you like. Use this to include the reward into your own business logic. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString RewardAmount;
	/* There are different types of rewards available. Possible values are Coins, Voucher, Money and Experience. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString RewardTypeName;
};

/*
*  Represents Battle Pass Level Challenge. This is usually nested inside a Battle Pass Level.
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FBattlePassLevelChallenge
{
	GENERATED_USTRUCT_BODY();

	static FBattlePassLevelChallenge FromScillApiBattlePassLevelChallenge(const ScillSDK::ScillApiBattlePassLevelChallenge o);

	/* The unique id of this challenge. Every challenge is linked to a product. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ChallengeId;
	/* The name of the challenge in the language set by the language parameter. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ChallengeName;
	/* Indicates how many “tasks” must be completed or done to complete this challenge. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ChallengeGoal;
	/* With this you can set the way how the SCILL system approaches the challenges state. 0 means, that the counter of the challenge must be brought above the goal. If this is 1, then the counter must be kept below the goal. This is often useful for challenges that include times, like: Manage the level in under 50 seconds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ChallengeGoalCondition;
	/* Indicates how many tasks the user already has completed. Use this in combination with challenge_goal to render a nice progress bar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 UserChallengeCurrentScore;
	/* In the admin panel you can set a string representing an image. This can be a URL, but it can also be an image or texture that you have in your games asset database. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ChallengeIcon;
	/* This is the HD variant of the challenge icon image. If you have a game, that runs on multiple platforms that could come in handy. Otherwise just leave blank. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ChallengeIconHd;
	/* Indicates the status of the challenge. This can be one of the following unlock: Challenge does not track anything. in-progress: Challenge is active and tracking. overtime: User did not manage to finish the challenge in time. unclaimed: The challenge has been completed but the reward has not yet been claimed. finished: The challenge has been successfully be completed and the reward has been claimed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Type;
};

/*
*  Represents a Battle Pass Level.
*/

USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FBattlePassLevel
{
	GENERATED_USTRUCT_BODY();

	static FBattlePassLevel FromScillApiBattlePassLevel(const ScillSDK::ScillApiBattlePassLevel o);

	/* Unique id of this BattlePassLevel object. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LevelId;
	/* The app id */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString AppId;
	/* The id of the battle pass this level belongs to */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString BattlePassId;
	/* In the Admin Panel you can set different types of rewards. You can also set an identifier of an in-game-item or anything you like. Use this to include the reward into your own business logic. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString RewardAmount;
	/* There are different types of rewards available. Possible values are Coins, Voucher, Money and Experience. This is deprecated in favor of level_reward_type which uses a slug instead of a human readable expression */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString RewardTypeName;
	/* The reward type in a machine readable slug. Available values are nothing, coin, experience, item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LevelRewardType;
	/* Indicates if this level is completed, i.e. all challenges have been completed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool LevelCompleted;
	/* Indicates the position of the level. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LevelPriority;
	/* Indicates if this level has already be claimed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool RewardClaimed;
	/* The date when this level has been activated or null if it's not activated. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ActivatedAt;
	/* An array of BattlePassLevelChallenge objects. Please note, not all values are available from the challenge object, as battle passes handle the lifecycle of challenges. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBattlePassLevelChallenge> Challenges;
};


/*
*  Represents a Battle Pass Challenge State object.
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FBattlePassChallengeState
{
	GENERATED_USTRUCT_BODY();

	/* The unique id of the app */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString AppId;
	/* The unique id of this battle pass. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString BattlePassId;
	/* Unique id of this BattlePassLevel object. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LevelId;
	/* This is your user id. You can set this to whatever you like, either your real user id or an obfuscated user id. However you need to be consistent here. Events linked to this user id only track if challenges or battle passes are unlocked with the same user id. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString UserId;
	/* Typical usage pattern is to load battle pass levels with getBattlePassLevels operation and store them for rendering. Using this value you can quickly identify the index of the level that changed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 LevelPositionIndex;
	/* The unique id of this challenge. Every challenge is linked to a product. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ChallengeId;
	/* Same as level_position_index. Use this index to identify the challenge that changed within the levels challenges array. Typical usage pattern is to update the previously stored score and type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ChallengePositionIndex;
	/* Indicates how many “tasks” must be completed or done to complete this challenge. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ChallengeGoal;
	/* Indicates how many tasks the user already has completed. Use this in combination with challenge_goal to render a nice progress bar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 UserChallengeCurrentScore;
	/* Indicates the status of the challenge. This can be one of the following unlock: Challenge does not track anything. in-progress: Challenge is active and tracking. overtime: User did not manage to finish the challenge in time. unclaimed: The challenge has been completed but the reward has not yet been claimed. finished: The challenge has been successfully be completed and the reward has been claimed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Type;
};

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
