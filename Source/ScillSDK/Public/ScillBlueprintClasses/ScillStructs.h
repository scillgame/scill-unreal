// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScillApiWrapper/ScillApiBattlePass.h"
#include "ScillApiWrapper/ScillApiBattlePassLevel.h"
#include "ScillApiWrapper/ScillApiBattlePassUnlockInfo.h"
#include "ScillApiWrapper/ScillApiChallenge.h"
#include "ScillApiWrapper/ScillApiChallengeCategory.h"
#include "ScillApiWrapper/ScillApiBattlePassChallengeChangedPayload.h"
#include "ScillApiWrapper/ScillApiChallengeWebhookPayload.h"
#include "ScillApiWrapper/ScillApiBattlePassState.h"
#include "ScillApiWrapper/ScillApiBattlePassExpiredPayload.h"
#include "ScillApiWrapper/ScillApiBattlePassLevelClaimedPayload.h"
#include "ScillApiWrapper/ScillApiBattlePassLevelReward.h"
#include "ScillApiWrapper/ScillApiEventMetaData.h"
#include "ScillApiWrapper/ScillApiEventPayload.h"
#include "ScillApiWrapper/ScillApiUserInfo.h"
#include "ScillApiWrapper/ScillApiLeaderboardRanking.h"
#include "ScillApiWrapper/ScillApiLeaderboardMemberRanking.h"
#include "ScillApiWrapper/ScillApiLeaderboard.h"
#include "ScillApiWrapper/ScillApiLeaderboardInfo.h"
#include "ScillApiWrapper/ScillApiLeaderboardScore.h"
#include "ScillApiWrapper/ScillApiLeaderboardUpdatePayload.h"
#include "ScillApiWrapper/ScillApiLeaderboardV2Changed.h"
#include "ScillApiWrapper/ScillApiLeaderboardV2Info.h"
#include "ScillApiWrapper/ScillApiLeaderboardV2Member.h"
#include "ScillApiWrapper/ScillApiLeaderboardV2MemberMetadata.h"
#include "ScillApiWrapper/ScillApiLeaderboardV2MemberRanking.h"
#include "ScillApiWrapper/ScillApiLeaderboardV2MemberTypeRanking.h"
#include "ScillApiWrapper/ScillApiLeaderboardV2Results.h"
#include "ScillApiWrapper/ScillApiLeaderboardV2ResultsLeaderboardResultsByMemberType.h"
#include "ScillApiWrapper/ScillApiLeaderboardV2UpdatePayload.h"
#include "ScillStructs.generated.h"

/*
*  This is the metadata of an event. Make sure to send the correct metadata for the correct event name.
*/

USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FEventMetaData
{
	GENERATED_USTRUCT_BODY();

	static ScillSDK::ScillApiEventMetaData ToScillApiEventMetaData(const FEventMetaData o);

	/* The object that is the source of the action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ActionObject;
	/* The object that is the target of the action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ActionSubject;
	/* The name of the action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ActionType;
	/* Number of ammonition used */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendAmmoUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 AmmoUsed;
	/* A general indicator for number of items (i.e. number of kills in kill-enemy event) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Amount;
	/* The number of ammonition gained */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendAmountGained;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 AmountGained;
	/* The number of amminition given */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendAmountGiven;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 AmountGiven;
	/* The name of an animal */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString AnimalName;
	/* The \"health\" state of the armor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendArmor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Armor;
	/* The id of the opponent team */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString AwayTeamId;
	/* The score of the opponent team */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendAwayScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 AwayScore;
	/* An integer value indicating the battle status (map it to an enum for example in your code) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendBattleStatus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 BattleStatus;
	/* The name of the bounty */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString BountyName;
	/* The id or name of a building */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString BuildingId;
	/* The level of the building */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendBuildingLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 BuildingLevel;
	/* The name of the card */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CardType;
	/* The name of a character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CharacterName;
	/* The id/name of a checkpint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CheckpointId;
	/* The x coordinate in your coordinate system, used for example to store position on a map */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendCoordinateX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CoordinateX;
	/* The y coordinate in your coordinate system, used for example to store position on a map */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendCoordinateY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CoordinateY;
	/* The name of a crew */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CrewName;
	/* The amount of damage */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendDamageAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 DamageAmount;
	/* The distance measured in any coordinate system of your choice. Please note: This is an integer field. If you need more precision multiple your floating point value with 1000 or so to keep the precision but storing it as an integer value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Distance;
	/* The duration in any unit you like */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Duration;
	/* The effect id or name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString EffectId;
	/* The character type or name of an enemy */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString EnemyCharacter;
	/* The type of an enemy */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString EnemyType;
	/* The event type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString EventType;
	/* The number of fuel consumed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendFuelConsumed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 FuelConsumed;
	/* The health */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Health;
	/* The type of a hit (i.e. head, torso, leg) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString HitType;
	/* The id or name of your or the home team */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString HomeTeamId;
	/* The score of your or the home team */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendHomeScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 HomeScore;
	/* The id of an item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemId;
	/* The name of an item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemName;
	/* The type of an item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemType;
	/* The type of a kill */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString KillType;
	/* The position in a lap */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendLapPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 LapPosition;
	/* The id of the level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LevelId;
	/* The name of a map */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MapName;
	/* The name of a section of a map */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MapSectionName;
	/* The mission id */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MissionId;
	/* The name of the player character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PlayerCharacter;
	/* The id of a puzzle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendPuzzleId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 PuzzleId;
	/* The position within a race */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendRacePosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 RacePosition;
	/* The realm */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Realm;
	/* The time required involed in this event. I.e. in a reach-checkpoint event this could be the time in seconds required to reach that checkpoint from the last checkpoint. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendRequiredTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 RequiredTime;
	/* The name/id of the resource gained */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ResourceGained;
	/* The name/id of the resource given (to someone else) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ResourceGiven;
	/* The name of the resource */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ResourceName;
	/* The id of the round */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendRoundId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 RoundId;
	/* The type of the round */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString RoundType;
	/* The score */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SendScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Score;
	/* The type of the stats item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString StatType;
	/* The timing condition */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString TimeCondition;
	/* The id of the transport */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString TransportId;
	/* The name/id of a type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Type;
	/* The name/id of a unit type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString UnitType;
	/* The name of the upgrade */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString UpgradeType;
	/* The action taken on a weapon (i.e. infrared-activated) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString WeaponAction;
	/* The id of the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString WeaponId;
	/* The type of the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString WeaponType;
	/* The name/id of a weapon used in a kill or similar event */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString WeaponUsed;
	/* The name of the zone */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ZoneName;
};

/*
*  This represents the payload that you can send with a "Send Event" request. Make sure to send the correct metadata with it. 
*/

USTRUCT(BlueprintType, Category = "ScillSDK")
	struct SCILLSDK_API FScillEventPayload
{
	GENERATED_USTRUCT_BODY();

	static ScillSDK::ScillApiEventPayload ToScillApiEventPayload(FScillEventPayload o);

	/* This is your user id. You can set this to whatever you like, either your real user id or an obfuscated user id. However you need to be consistent here. Events linked to this user id only track if challenges or battle passes are unlocked with the same user id. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString UserId;
	/* This is required if event_type is single and identifies a session. This can be anything used to group events together. For example this can be a level or a match id. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SessionId;
	/* This is the event type as a string. These have predefined event names for many games and applications. It’s wise to use those as this allows us to analyse data and help you balancing your application or game. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString EventName;
	/* This is either single or group. You can send multiple events in one request (group) or send events in sequence. Please note, that depending on your tier you might run into rate limits. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString EventType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FEventMetaData MetaData;
};

/*
*  Represents a Personal Challenge (non-battlepass challenge).
*/

USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FChallenge
{
	GENERATED_USTRUCT_BODY();

	static FChallenge FromScillApiChallenge(const ScillSDK::ScillApiChallenge o);

	/* The unique id of this challenge. Every challenge is linked to a product. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ChallengeId;
	/* The name of the challenge in the language set by the language parameter. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ChallengeName;
	/* The duration of the challenge in seconds. Challenges auto lock after time-out and need to be unlocked again. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ChallengeDurationTime;
	/* The date this challenge should start. Use that field to create challenges that start in the future. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LiveDate;
	/* Indicates how many “tasks” must be completed or done to complete this challenge. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ChallengeGoal;
	/* Indicates how many tasks the user already has completed. Use this in combination with challenge_goal to render a nice progress bar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 UserChallengeCurrentScore;
	/* In the admin panel you can set a string representing an image. This can be a URL, but it can also be an image or texture that you have in your games asset database. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ChallengeIcon;
	/* This is the HD variant of the challenge icon image. If you have a game, that runs on multiple platforms that could come in handy. Otherwise just leave blank. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ChallengeIconHd;
	/* If you purchase the challenge, you can set a price. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ChallengePrice;
	/* Set a reward for this challenge. This is a string value that you can map to anything in your code. Use in combination with challenge_reward_type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ChallengeReward;
	/* The reward type can be set to various different settings. Use it to implement different reward types on your side and use challenge_reward to set the value or amount of this reward. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ChallengeRewardType;
	/* With this you can set the way how the SCILL system approaches the challenges state. 0 means, that the counter of the challenge must be brought above the goal. If this is 1, then the counter must be kept below the goal. This is often useful for challenges that include times, like: Manage the level in under 50 seconds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ChallengeGoalCondition;
	/* If you have experience, player rankings whatever, you can use this field to set the gain in that when this challenge is rewarded. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ChallengeXp;
	/* If this challenge can be only activated once per user this will be false. Otherwise this challenge will always be added to list of available challenges (see personal or alliance challenges). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Repeatable;
	/* Indicates the status of the challenge. This can be one of the following unlock: Challenge does not track anything. in-progress: Challenge is active and tracking. overtime: User did not manage to finish the challenge in time. unclaimed: The challenge has been completed but the reward has not yet been claimed. finished: The challenge has been successfully be completed and the reward has been claimed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Type;
	/* If the challenge reward has been claimed this is true otherwise its false. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsClaimed;
	/* This is the timestamp the challenge has been unlocked. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString UserChallengeUnlockedAt;
	/* This is the timestamp the challenge has been activated. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString UserChallengeActivatedAt;
	/* Indicates if this challenge has been claimed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool UserChallengeIsClaimed;
	/* Gives indication in what state the challenge is. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 UserChallengeStatus;

};

/*
*  Represents a Personal Challenge Request. This is usually the result of any Challenge Request.
*/

USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FChallengeCategory
{
	GENERATED_USTRUCT_BODY();

	static FChallengeCategory FromScillApiChallengeCategory(const ScillSDK::ScillApiChallengeCategory o);

	/* Indicates if this is the daily category, bringing up new challenges every day for the user to tackle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsDailyCategory;
	/* In the admin panel you set the order of the categories. This is the position index and indicates the position within the categories array. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CategoryPosition;
	/* A short name without special chars to make it easier to refer to a specific category (in code) that is language and id agnostic. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CategorySlug;
	/* The name of the category in the local language set as the query parameter. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CategoryName;
	/* Indicates how many “tasks” must be completed or done to complete this challenge. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CategoryId;
	/* An array of Challenge objects. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FChallenge> Challenges;

};

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

	static FBattlePassState FromScillApiBattlePassState(const ScillSDK::ScillApiBattlePassState o);
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

	static FBattlePassLevelReward FromScillApiBattlePassLevelReward(const ScillSDK::ScillApiBattlePassLevelReward o);
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

	static FBattlePassChallengeState FromScillApiBattlePassChallengeState(const ScillSDK::ScillApiBattlePassChallengeState o);
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

/*
* Represents any update of a battle pass challenge.
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FBattlePassChanged
{
	GENERATED_USTRUCT_BODY()
public:
	/* The type of the notification. If you receive this payload, it's most likely battlepass-challenge-changed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WebhookType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBattlePassChallengeState OldBattlePassChallenge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBattlePassChallengeState NewBattlePassChallenge;

	static FBattlePassChanged FromScillApiBattlePassChallengeChangedPayload(const ScillSDK::ScillApiBattlePassChallengeChangedPayload o);
};

/*
* Is returned if a monitored battle pass has expired.
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FBattlePassExpired
{
	GENERATED_USTRUCT_BODY()
public:
	/* The type of the notification. If you receive this payload, it's most likely battlepass-expired */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString WebhookType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBattlePassState OldBattlePass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBattlePassState NewBattlePass;

	static FBattlePassExpired FromScillApiBattlePassExpiredPayload(const ScillSDK::ScillApiBattlePassExpiredPayload o);
};

/*
* Is returned if a Battle Pass Level's reward was claimed.
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FBattlePassLevelClaimed
{
	GENERATED_USTRUCT_BODY()
public:
	/* The type of the notification. If you receive this payload, it's most likely battlepass-expired */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString WebhookType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBattlePassLevelReward BattlePassLevelRewardClaimed;

	static FBattlePassLevelClaimed FromScillApiBattlePassLevelClaimedPayload(const ScillSDK::ScillApiBattlePassLevelClaimedPayload o);
};

/*
* Represents an update of a user challenge.
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FChallengeChanged
{
	GENERATED_USTRUCT_BODY()
public:
	/* The type of the notification. If you receive this payload, it's most likely battlepass-challenge-changed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString WebhookType;

	/* The index of the category this challenge is linked to. When you request personal challenges, you get an array of categories which contain an array of challenges in their challenges property. This value indicates in which category this challenge can be found. Speeds up updating UI as you don't need to iterate through all catagories and challenges to find the challenge. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CategoryPosition;

	/* The access token for the user of that challenge. You can use that user_token to directly send another event and therefore to chain different SCILL pieces together. For example you can send another event driving another challenge or battle pass whenever a user has completed a challenge. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString UserToken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FChallenge NewChallenge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FChallenge OldChallenge;

	static FChallengeChanged FromScillApiChallengeWebhookPayload(const ScillSDK::ScillApiChallengeWebhookPayload o);
};

/*Can be any object that is attached to the user. You can set these values in the user service. For example you can provide a user name and an avatar image url.
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FUserInfo
{
	GENERATED_USTRUCT_BODY()
public:
	/* The user name of the user */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Username;

	/* The name or URL of an avatar image for a user. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString AvatarImage;

	static FUserInfo FromScillApiUserInfo(const ScillSDK::ScillApiUserInfo o);
	static ScillSDK::ScillApiUserInfo ToScillApiUserInfo(const FUserInfo o);
};

/*The ranking for the user or team in the leaderboard
*/
USTRUCT(BlueprintType, Category = "ScillSDK", meta = (DeprecatedNode, DeprecationMessage = "The Leaderboard V1 endpoints have been deprecated. Please use the new Leaderboard functions."))
struct SCILLSDK_API FLeaderboardRanking
{
	GENERATED_USTRUCT_BODY()
public:
	/* The id of the user - its the same user id you used to create the access token and the same user id you used to send the events */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MemberId;

	/* Indicates what type this entry is, it's either user or team */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MemberType;

	/* The score achieved as an integer value. If you want to store floats, for example laptimes you need to convert them into an int before (i.e. multiply by 100 to get hundreds of seconds and format back to float in UI) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Score;

	/* The position within the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Rank;

	/* Info about the user */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FUserInfo AdditionalInfo;

	static FLeaderboardRanking FromScillApiLeaderboardRanking(const ScillSDK::ScillApiLeaderboardRanking o);
};

/*You get these object if you query the leaderboard ranking for a specific user. Only the requested user will be returned.
*/
USTRUCT(BlueprintType, Category = "ScillSDK", meta = (DeprecatedNode, DeprecationMessage = "The Leaderboard V1 endpoints have been deprecated. Please use the new Leaderboard functions."))
struct SCILLSDK_API FLeaderboardMemberRanking
{
	GENERATED_USTRUCT_BODY()
public:
	/* The id of the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LeaderboardId;

	/* The name of the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	/* Info about the user */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLeaderboardRanking Member;

	static FLeaderboardMemberRanking FromScillApiLeaderboardMemberRanking(const ScillSDK::ScillApiLeaderboardMemberRanking o);
};

/*The Leaderboard object contains information about the leaderboard itself like the name and the id, but also contains actual rankings for users and teams.
*/
USTRUCT(BlueprintType, Category = "ScillSDK", meta = (DeprecatedNode, DeprecationMessage = "The Leaderboard V1 endpoints have been deprecated. Please use the new Leaderboard functions."))
struct SCILLSDK_API FLeaderboard
{
	GENERATED_USTRUCT_BODY()
public:
	/* The id of the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LeaderboardId;

	/* The name of the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	/* An array of LeaderboardRanking Items for individual users */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FLeaderboardRanking> GroupedByUsers;

	/* An array of LeaderboardRanking Items for teams. Provide a team_id in the event payload to also create leaderboards for teams */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FLeaderboardRanking> GroupedByTeams;

	static FLeaderboard FromScillApiLeaderboard(const ScillSDK::ScillApiLeaderboard o);
};

/* Contains info about rank and score
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FLeaderboardScore
{
	GENERATED_USTRUCT_BODY()
public:
	/* The score achieved as an integer value. If you want to store floats, for example laptimes you need to convert them into an int before (i.e. multiply by 100 to get hundreds of seconds and format back to float in UI) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Score;

	/* The position within the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Rank;

	static FLeaderboardScore FromScillApiLeaderboardScore(const ScillSDK::ScillApiLeaderboardScore o);
};

/* The Leaderboard object contains information about the leaderboard itself like the name and the id
*/
USTRUCT(BlueprintType, Category = "ScillSDK", meta = (DeprecatedNode, DeprecationMessage = "The Leaderboard V1 endpoints have been deprecated. Please use the new Leaderboard functions."))
struct SCILLSDK_API FLeaderboardInfo
{
	GENERATED_USTRUCT_BODY()
public:
	/* The id of the app */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AppId;
	/* The id of the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LeaderboardId;
	/* The name of the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	/* The event type that triggers this leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString EventType;
	/* True if this leaderboard sorts the score ascending or false if the ranking is defined by a descending score. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SortOrderAscending;

	static FLeaderboardInfo FromScillApiLeaderboardInfo(const ScillSDK::ScillApiLeaderboardInfo o);
};

/* The payload used for realtime updates and webhooks if a leaderboard is updated.
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FLeaderboardUpdatePayload
{
	GENERATED_USTRUCT_BODY()
public:
	/* The type of the webhook, in this case it is leaderboard-ranking-changed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WebhookType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLeaderboardInfo LeaderboardData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLeaderboardRanking MemberData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLeaderboardScore OldLeaderboardRanking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLeaderboardScore NewLeaderboardRanking;

	static FLeaderboardUpdatePayload FromScillApiLeaderboardUpdatePayload(const ScillSDK::ScillApiLeaderboardUpdatePayload o);
};

/* The object containing secondary metadata ranking information, useful for tied scores on the main tracking parameter
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FLeaderboardV2MemberMetadata
{
	GENERATED_USTRUCT_BODY()
public:
	/* The event type key used for ranking */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Key;

	/* Determines if the user is ranked for that event type key. If false, no score and rank will be provided */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Ranked;

	/* The score achieved as an integer value. If you want to store floats, for example laptimes you need to convert them into an int before (i.e. multiply by 100 to get hundreds of seconds and format back to float in UI) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Score;

	/* The position within the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Rank;

	static FLeaderboardV2MemberMetadata FromScillApiLeaderboardV2MemberMetadata(const ScillSDK::ScillApiLeaderboardV2MemberMetadata o);
};

/* The ranking for the user or team in the leaderboard
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FLeaderboardV2Member
{
	GENERATED_USTRUCT_BODY()
public:
	/* The id of the user - its the same user id you used to create the access token and the same user id you used to send the events */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MemberId;

	/* Indicates what type this entry is, it's either user or team */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MemberType;

	/* The score achieved as an integer value. If you want to store floats, for example laptimes you need to convert them into an int before (i.e. multiply by 100 to get hundreds of seconds and format back to float in UI) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Score;

	/* The position within the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Rank;

	/* Returns an array of the LeaderboardMemberMetadata objects containing user ranking metadata information */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FLeaderboardV2MemberMetadata> MetadataResults;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FUserInfo AdditionalInfo;

	static FLeaderboardV2Member FromScillApiLeaderboardV2Member(const ScillSDK::ScillApiLeaderboardV2Member o);
};

/* The payload used for realtime updates and webhooks if a leaderboard is updated.
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FLeaderboardV2MemberTypeRanking
{
	GENERATED_USTRUCT_BODY()
public:

	/* The total number of members included in the results */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Count;

	/* An array of LeaderboardMember objects */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FLeaderboardV2Member> Members;

	static FLeaderboardV2MemberTypeRanking FromScillApiLeaderboardV2MemberTypeRanking(const ScillSDK::ScillApiLeaderboardV2MemberTypeRanking o);
};

/* The payload used for realtime updates and webhooks if a leaderboard is updated.
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FLeaderboardV2MemberRanking
{
	GENERATED_USTRUCT_BODY()
public:
	/* The id of the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LeaderboardId;

	/* The name of the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LeaderboardName;

	/* Determines the results sort order. If true, the order is ascending, otherwise, it's descending. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool LeaderboardSortOrderAscending;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLeaderboardV2Member LeaderboardMember;

	static FLeaderboardV2MemberRanking FromScillApiLeaderboardV2MemberRanking(const ScillSDK::ScillApiLeaderboardV2MemberRanking o);
};

/* This object uses two keys - "user" and "team", both of which contain ranking info
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FLeaderboardV2ResultsLeaderboardResultsByMemberType
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLeaderboardV2MemberTypeRanking Team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLeaderboardV2MemberTypeRanking User;

	static FLeaderboardV2ResultsLeaderboardResultsByMemberType FromScillApiLeaderboardV2ResultsLeaderboardResultsByMemberType(const ScillSDK::ScillApiLeaderboardV2ResultsLeaderboardResultsByMemberType o);
};

/* The Leaderboard object contains information about the leaderboard itself like the name and the id, but also contains actual rankings for users and teams.
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FLeaderboardV2Results
{
	GENERATED_USTRUCT_BODY()
public:

	/* The id of the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LeaderboardId;

	/* The name of the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LeaderboardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLeaderboardV2ResultsLeaderboardResultsByMemberType LeaderboardResultsByMemberType;

	/* Determines the results sort order. If true, the order is ascending, otherwise, it's descending. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool LeaderboardSortOrderAscending;

	static FLeaderboardV2Results FromScillApiLeaderboardV2Results(const ScillSDK::ScillApiLeaderboardV2Results o);
};

/* The Leaderboard object contains information about the leaderboard itself like the name and the id
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FLeaderboardV2Info
{
	GENERATED_USTRUCT_BODY()
public:

	/* The id of the app */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString AppId;

	/* The id of the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LeaderboardId;

	/* The name of the leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LeaderboardName;

	/* The event type that triggers this leaderboard */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString EventType;

	/* True if this leaderboard sorts the score ascending or false if the ranking is defined by a descending score. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SortOrderAscending;

	static FLeaderboardV2Info FromScillApiLeaderboardV2Info(const ScillSDK::ScillApiLeaderboardV2Info o);
};

/* This object is sent via Webhook or notifications of type leaderboard-changed.
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FLeaderboardV2Changed
{
	GENERATED_USTRUCT_BODY()
public:

	/* The type of the notification. If you receive this payload, it's most likely leaderboard-changed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString WebhookType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLeaderboardV2Info OldLeaderboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLeaderboardV2Info NewLeaderboard;

	static FLeaderboardV2Changed FromScillApiLeaderboardV2Changed(const ScillSDK::ScillApiLeaderboardV2Changed o);
};

/* The payload used for realtime updates and webhooks if a leaderboard is updated.
*/
USTRUCT(BlueprintType, Category = "ScillSDK")
struct SCILLSDK_API FLeaderboardV2UpdatePayload
{
	GENERATED_USTRUCT_BODY()
public:

	/* The type of the webhook, in this case it is leaderboard-ranking-changed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString WebhookType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLeaderboardV2Info LeaderboardData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLeaderboardV2Member MemberData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLeaderboardScore OldLeaderboardRanking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLeaderboardScore NewLeaderboardRanking;

	static FLeaderboardV2UpdatePayload FromScillApiLeaderboardV2UpdatePayload(const ScillSDK::ScillApiLeaderboardV2UpdatePayload o);
};