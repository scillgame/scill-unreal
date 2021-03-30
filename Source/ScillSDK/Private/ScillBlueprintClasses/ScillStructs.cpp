// Fill out your copyright notice in the Description page of Project Settings.


#include "ScillBlueprintClasses/ScillStructs.h"

ScillSDK::ScillApiEventPayload FScillEventPayload::ToScillApiEventPayload(const FScillEventPayload o)
{
	auto n = ScillSDK::ScillApiEventPayload();

	n.UserId = o.UserId;
	n.SessionId = o.SessionId;
	n.EventName = o.EventName;
	n.EventType = o.EventType;
	n.MetaData = FEventMetaData::ToScillApiEventMetaData(o.MetaData);

	return n;
}

ScillSDK::ScillApiEventMetaData FEventMetaData::ToScillApiEventMetaData(const FEventMetaData o)
{
	auto n = ScillSDK::ScillApiEventMetaData();

	if (!o.ActionObject.IsEmpty()) n.ActionObject = o.ActionObject;
	if (!o.ActionSubject.IsEmpty()) n.ActionSubject = o.ActionSubject;
	if (!o.ActionType.IsEmpty()) n.ActionType = o.ActionType;
	if (!o.AnimalName.IsEmpty()) n.AnimalName = o.AnimalName;
	if (!o.AwayTeamId.IsEmpty()) n.AwayTeamId = o.AwayTeamId;
	if (!o.BountyName.IsEmpty()) n.BountyName = o.BountyName;
	if (!o.BuildingId.IsEmpty()) n.BuildingId = o.BuildingId;
	if (!o.CardType.IsEmpty()) n.CardType = o.CardType;
	if (!o.CharacterName.IsEmpty()) n.CharacterName = o.CharacterName;
	if (!o.CheckpointId.IsEmpty()) n.CheckpointId = o.CheckpointId;
	if (!o.CrewName.IsEmpty()) n.CrewName = o.CrewName;
	if (!o.EffectId.IsEmpty()) n.EffectId = o.EffectId;
	if (!o.EnemyCharacter.IsEmpty()) n.EnemyCharacter = o.EnemyCharacter;
	if (!o.EnemyType.IsEmpty()) n.EnemyType = o.EnemyType;
	if (!o.EventType.IsEmpty()) n.EventType = o.EventType;
	if (!o.HitType.IsEmpty()) n.HitType = o.HitType;
	if (!o.HomeTeamId.IsEmpty()) n.HomeTeamId = o.HomeTeamId;
	if (!o.ItemId.IsEmpty()) n.ItemId = o.ItemId;
	if (!o.ItemName.IsEmpty()) n.ItemName = o.ItemName;
	if (!o.ItemType.IsEmpty()) n.ItemType = o.ItemType;
	if (!o.KillType.IsEmpty()) n.KillType = o.KillType;
	if (!o.LevelId.IsEmpty()) n.LevelId = o.LevelId;
	if (!o.MapName.IsEmpty()) n.MapName = o.MapName;
	if (!o.MapSectionName.IsEmpty()) n.MapSectionName = o.MapSectionName;
	if (!o.MissionId.IsEmpty()) n.MissionId = o.MissionId;
	if (!o.PlayerCharacter.IsEmpty()) n.PlayerCharacter = o.PlayerCharacter;
	if (!o.Realm.IsEmpty()) n.Realm = o.Realm;
	if (!o.ResourceGained.IsEmpty()) n.ResourceGained = o.ResourceGained;
	if (!o.ResourceGiven.IsEmpty()) n.ResourceGiven = o.ResourceGiven;
	if (!o.ResourceName.IsEmpty()) n.ResourceName = o.ResourceName;
	if (!o.RoundType.IsEmpty()) n.RoundType = o.RoundType;
	if (!o.StatType.IsEmpty()) n.StatType = o.StatType;
	if (!o.TimeCondition.IsEmpty()) n.TimeCondition = o.TimeCondition;
	if (!o.TransportId.IsEmpty()) n.TransportId = o.TransportId;
	if (!o.Type.IsEmpty()) n.Type = o.Type;
	if (!o.UnitType.IsEmpty()) n.UnitType = o.UnitType;
	if (!o.UpgradeType.IsEmpty()) n.UpgradeType = o.UpgradeType;
	if (!o.WeaponAction.IsEmpty()) n.WeaponAction = o.WeaponAction;
	if (!o.WeaponId.IsEmpty()) n.WeaponId = o.WeaponId;
	if (!o.WeaponType.IsEmpty()) n.WeaponType = o.WeaponType;
	if (!o.WeaponUsed.IsEmpty()) n.WeaponUsed = o.WeaponUsed;
	if (!o.ZoneName.IsEmpty()) n.ZoneName = o.ZoneName;

	if (o.SendAmmoUsed) n.AmmoUsed = o.AmmoUsed;
	if (o.SendAmount) n.Amount = o.Amount;
	if (o.SendAmountGained) n.AmountGained = o.AmountGained;
	if (o.SendAmountGiven) n.AmountGiven = o.AmountGiven;
	if (o.SendArmor) n.Armor = o.Armor;
	if (o.SendAwayScore) n.AwayScore = o.AwayScore;
	if (o.SendBattleStatus) n.BattleStatus = o.BattleStatus;
	if (o.SendBuildingLevel) n.BuildingLevel = o.BuildingLevel;
	if (o.SendCoordinateX) n.CoordinateX = o.CoordinateX;
	if (o.SendCoordinateY) n.CoordinateY = o.CoordinateY;
	if (o.SendDamageAmount) n.DamageAmount = o.DamageAmount;
	if (o.SendDistance) n.Distance = o.Distance;
	if (o.SendDuration) n.Duration = o.Duration;
	if (o.SendFuelConsumed) n.FuelConsumed = o.FuelConsumed;
	if (o.SendHealth) n.Health = o.Health;
	if (o.SendHomeScore) n.HomeScore = o.HomeScore;
	if (o.SendLapPosition) n.LapPosition = o.LapPosition;
	if (o.SendPuzzleId) n.PuzzleId = o.PuzzleId;
	if (o.SendRacePosition) n.RacePosition = o.RacePosition;
	if (o.SendRequiredTime) n.RequiredTime = o.RequiredTime;
	if (o.SendRoundId) n.RoundId = o.RoundId;
	if (o.SendScore) n.Score = o.Score;

	return n;
}

FChallengeCategory FChallengeCategory::FromScillApiChallengeCategory(const ScillSDK::ScillApiChallengeCategory o)
{
	auto n = FChallengeCategory();

	n.IsDailyCategory = o.IsDailyCategory.Get(false);
	n.CategoryPosition = o.CategoryPosition.Get(0);
	n.CategorySlug = o.CategorySlug.Get("");
	n.CategoryName = o.CategoryName.Get("");
	n.CategoryId = o.CategoryId.Get("");

	TArray<FChallenge> challenges = TArray<FChallenge>();

	if(o.Challenges.IsSet())
		for (auto & c : o.Challenges.GetValue())
		{
			challenges.Add(FChallenge::FromScillApiChallenge(c));
		}

	n.Challenges = challenges;

	n.IsDailyCategory = o.IsDailyCategory.Get(false);

	return n;
}

FChallenge FChallenge::FromScillApiChallenge(const ScillSDK::ScillApiChallenge o)
{
	auto n = FChallenge();

	n.ChallengeId = o.ChallengeId.Get("");
	n.ChallengeName = o.ChallengeName.Get("");
	n.LiveDate = o.LiveDate.Get("");
	n.ChallengeIcon = o.ChallengeIcon.Get("");
	n.ChallengeIconHd = o.ChallengeIconHd.Get("");
	n.ChallengeReward = o.ChallengeReward.Get("");
	n.ChallengeRewardType = o.ChallengeRewardType.Get("");
	n.Type = o.Type.Get("");
	n.UserChallengeUnlockedAt = o.UserChallengeUnlockedAt.Get("");
	n.UserChallengeActivatedAt = o.UserChallengeActivatedAt.Get("");

	n.ChallengeDurationTime = o.ChallengeDurationTime.Get(0);
	n.ChallengeGoal = o.ChallengeGoal.Get(0);
	n.UserChallengeCurrentScore = o.UserChallengeCurrentScore.Get(0);
	n.ChallengePrice = o.ChallengePrice.Get(0);
	n.ChallengeGoalCondition = o.ChallengeGoalCondition.Get(0);
	n.ChallengeXp = o.ChallengeXp.Get(0);
	n.UserChallengeStatus = o.UserChallengeStatus.Get(0);

	n.Repeatable = o.Repeatable.Get(false);
	n.IsClaimed = o.IsClaimed.Get(false);
	n.UserChallengeIsClaimed = o.UserChallengeIsClaimed.Get(false);

	return n;
}

FBattlePassUnlockInfo FBattlePassUnlockInfo::FromScillApiBattlePassUnlockInfo(const ScillSDK::ScillApiBattlePassUnlockInfo o)
{
	auto n = FBattlePassUnlockInfo();

	n.PurchaseId = o.PurchaseId.Get("");
	n.BattlePassId = o.BattlePassId.Get("");
	n.PurchasePrice = o.PurchasePrice.Get(0);
	n.UserId = o.UserId.Get("");
	n.PurchaseCurrency = o.PurchaseCurrency.Get("");
	n.PurchasedAt = o.PurchasedAt.Get("");
	n.BattlePassCompleted = o.BattlePassCompleted.Get(false);

	return n;
}

FBattlePassLevelChallenge FBattlePassLevelChallenge::FromScillApiBattlePassLevelChallenge(const ScillSDK::ScillApiBattlePassLevelChallenge o)
{
	auto n = FBattlePassLevelChallenge();

	n.ChallengeId = o.ChallengeId.Get("");
	n.ChallengeName = o.ChallengeName.Get("");
	n.ChallengeGoal = o.ChallengeGoal.Get(0);
	n.ChallengeGoalCondition = o.ChallengeGoalCondition.Get(0);
	n.UserChallengeCurrentScore = o.UserChallengeCurrentScore.Get(0);
	n.ChallengeIcon = o.ChallengeIcon.Get("");
	n.ChallengeIconHd = o.ChallengeIconHd.Get("");
	n.Type = o.Type.Get("");

	return n;
}

FBattlePassLevel FBattlePassLevel::FromScillApiBattlePassLevel(const ScillSDK::ScillApiBattlePassLevel o)
{
	auto n = FBattlePassLevel();

	n.LevelId = o.LevelId.Get("");
	n.AppId = o.AppId.Get("");
	n.BattlePassId = o.BattlePassId.Get("");
	n.RewardAmount = o.RewardAmount.Get("");
	n.RewardTypeName = o.RewardTypeName.Get("");
	n.LevelRewardType = o.LevelRewardType.Get("");
	n.LevelCompleted = o.LevelCompleted.Get(false);
	n.LevelPriority = o.LevelPriority.Get(0);
	n.RewardClaimed = o.RewardClaimed.Get(false);
	n.ActivatedAt = o.ActivatedAt.Get("");
	
	// TODO:
	// Retrieve Battle Pass Level Challenges

	TArray<FBattlePassLevelChallenge> challenges = TArray<FBattlePassLevelChallenge>();
	if(o.Challenges.IsSet())
		for (auto& c : o.Challenges.GetValue())
		{
			challenges.Add(FBattlePassLevelChallenge::FromScillApiBattlePassLevelChallenge(c));
		}


	return n;
}

FBattlePass FBattlePass::FromScillApiBattlePass(const ScillSDK::ScillApiBattlePass battlePass)
{
	auto bp = FBattlePass();

	bp.AppId = battlePass.AppId.Get("");
	bp.BattlePassDescription = battlePass.BattlePassDescription.Get("");
	bp.BattlePassDisclaimer = battlePass.BattlePassDisclaimer.Get("");
	bp.BattlePassId = battlePass.BattlePassId.Get("");
	bp.BattlePassName = battlePass.BattlePassName.Get("");
	bp.BattlePassPriority = battlePass.BattlePassPriority.Get(0);
	bp.BattlePassShortDescription = battlePass.BattlePassDescription.Get("");
	bp.CanPurchaseWithCoins = battlePass.CanPurchaseWithCoins.Get(false);
	bp.CanPurchaseWithMoney = battlePass.CanPurchaseWithMoney.Get(false);
	bp.EndDate = battlePass.EndDate.Get("");
	bp.ImageL = battlePass.ImageL.Get("");
	bp.ImageM = battlePass.ImageM.Get("");
	bp.ImageS = battlePass.ImageS.Get("");
	bp.ImageXl = battlePass.ImageXl.Get("");
	bp.ImageXs = battlePass.ImageXs.Get("");
	bp.IsActive = battlePass.IsActive.Get(false);
	bp.IsUnlockedIncrementally = battlePass.IsUnlockedIncrementally.Get(false);
	bp.PackageSkuAndroid = battlePass.PackageSkuAndroid.Get("");
	bp.PackageSkuIos = battlePass.PackageSkuIos.Get("");
	bp.ReadMoreLink = battlePass.ReadMoreLink.Get("");
	bp.StartDate = battlePass.StartDate.Get("");
	bp.UnlockedAt = battlePass.UnlockedAt.Get("");

	return bp;
}

FBattlePassChallengeState FBattlePassChallengeState::FromScillApiBattlePassChallengeState(const ScillSDK::ScillApiBattlePassChallengeState o)
{
	auto n = FBattlePassChallengeState();

	n.AppId = o.AppId.Get("");
	n.BattlePassId = o.BattlePassId.Get("");
	n.LevelId = o.LevelId.Get("");
	n.UserId = o.UserId.Get("");
	n.LevelPositionIndex = o.LevelPositionIndex.Get(0);
	n.ChallengeId = o.ChallengeId.Get("");
	n.ChallengePositionIndex = o.ChallengePositionIndex.Get(0);
	n.ChallengeGoal = o.ChallengeGoal.Get(0);
	n.UserChallengeCurrentScore = o.UserChallengeCurrentScore.Get(0);
	n.Type = o.Type.Get("");

	return n;
}

FBattlePassChanged FBattlePassChanged::FromScillApiBattlePassChallengeChangedPayload(const ScillSDK::ScillApiBattlePassChallengeChangedPayload o)
{
	auto n = FBattlePassChanged();

	n.WebhookType = o.WebhookType.Get("");
	n.OldBattlePassChallenge = FBattlePassChallengeState::FromScillApiBattlePassChallengeState(o.OldBattlePassChallenge.Get(ScillSDK::ScillApiBattlePassChallengeState()));
	n.NewBattlePassChallenge = FBattlePassChallengeState::FromScillApiBattlePassChallengeState(o.NewBattlePassChallenge.Get(ScillSDK::ScillApiBattlePassChallengeState()));

	return n;
}

FChallengeChanged FChallengeChanged::FromScillApiChallengeWebhookPayload(const ScillSDK::ScillApiChallengeWebhookPayload o)
{
	auto n = FChallengeChanged();

	n.WebhookType = o.WebhookType.Get("");
	n.CategoryPosition = o.CategoryPosition.Get(0.0);
	n.UserToken = o.UserToken.Get("");

	n.OldChallenge = FChallenge::FromScillApiChallenge(o.OldChallenge.Get(ScillSDK::ScillApiChallenge()));
	n.NewChallenge = FChallenge::FromScillApiChallenge(o.NewChallenge.Get(ScillSDK::ScillApiChallenge()));

	return n;
}

FBattlePassState FBattlePassState::FromScillApiBattlePassState(const ScillSDK::ScillApiBattlePassState o)
{
	auto n = FBattlePassState();

	n.BattlePassId = o.BattlePassId.Get("");
	n.BattlePassPriority = o.BattlePassPriority.Get(0);
	n.AppId = o.AppId.Get("");
	n.StartDate = o.StartDate.Get("");
	n.EndDate = o.EndDate.Get("");
	n.IsActive = o.IsActive.Get(false);

	return n;
}

FBattlePassExpired FBattlePassExpired::FromScillApiBattlePassExpiredPayload(const ScillSDK::ScillApiBattlePassExpiredPayload o)
{
	auto n = FBattlePassExpired();

	n.WebhookType = o.WebhookType.Get("");

	n.OldBattlePass = FBattlePassState::FromScillApiBattlePassState(o.OldBattlePass.Get(ScillSDK::ScillApiBattlePassState()));
	n.NewBattlePass = FBattlePassState::FromScillApiBattlePassState(o.NewBattlePass.Get(ScillSDK::ScillApiBattlePassState()));

	return n;
}

FBattlePassLevelReward FBattlePassLevelReward::FromScillApiBattlePassLevelReward(const ScillSDK::ScillApiBattlePassLevelReward o)
{
	auto n = FBattlePassLevelReward();

	n.BattlePassId = o.BattlePassId.Get("");
	n.LevelPositionIndex = o.LevelPositionIndex.Get(0);
	n.AppId = o.AppId.Get("");
	n.LevelId = o.LevelId.Get("");
	n.UserId = o.UserId.Get("");
	n.RewardAmount = o.RewardAmount.Get("");
	n.RewardTypeName = o.RewardTypeName.Get("");

	return n;
}

FBattlePassLevelClaimed FBattlePassLevelClaimed::FromScillApiBattlePassLevelClaimedPayload(const ScillSDK::ScillApiBattlePassLevelClaimedPayload o)
{
	auto n = FBattlePassLevelClaimed();

	n.WebhookType = o.WebhookType.Get("");

	n.BattlePassLevelRewardClaimed = FBattlePassLevelReward::FromScillApiBattlePassLevelReward(o.BattlePassLevelRewardClaimed.Get(ScillSDK::ScillApiBattlePassLevelReward()));

	return n;
}