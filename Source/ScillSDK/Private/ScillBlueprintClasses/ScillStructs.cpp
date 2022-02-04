// Fill out your copyright notice in the Description page of Project Settings.


#include "ScillBlueprintClasses/ScillStructs.h"
#include "ObjectEditorUtils.h"

FScillEventPayload FScillEventPayload::FromScillEventPayloadBase(const UEventMetaDataBase* meta)
{
	auto n = FScillEventPayload();

	n.UserId = meta->UserId;
	n.SessionId = meta->SessionId;
	n.EventName = meta->EventName();
	n.EventType = meta->BaseEventType;

	n.MetaData = FEventMetaData();

	if (auto o = Cast<UAchieveScoreMetaData>(meta))
	{
		n.MetaData.Score = o->Score;
		n.MetaData.SendScore = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UBuildRoadMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.MapName = o->MapName;
		n.MetaData.Realm = o->Realm;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UCaptureFlagMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
	}
	if (auto o = Cast<UCatchAnimalMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.AnimalName = o->AnimalName;
	}
	if (auto o = Cast<UCharacterFlyMetaData>(meta))
	{
		n.MetaData.Distance = o->Distance;
		n.MetaData.SendDistance = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
		n.MetaData.Realm = o->Realm;
	}
	if (auto o = Cast<UCharacterRespawnMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
		n.MetaData.Realm = o->Realm;
	}

	if (auto o = Cast<UCharacterRunMetaData>(meta))
	{
		n.MetaData.Distance = o->Distance;
		n.MetaData.SendDistance = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
		n.MetaData.Realm = o->Realm;
	}

	if (auto o = Cast<UCharacterSpawnedMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
	}

	if (auto o = Cast<UCharacterSurviveMetaData>(meta))
	{
		n.MetaData.Duration = o->Duration;
		n.MetaData.SendDuration = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
		n.MetaData.Realm = o->Realm;
	}

	if (auto o = Cast<UCharacterWalkMetaData>(meta))
	{
		n.MetaData.Distance = o->Distance;
		n.MetaData.SendDistance = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
		n.MetaData.Realm = o->Realm;
	}

	if (auto o = Cast<UCollectItemMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.ItemType = o->ItemType;
	}

	if (auto o = Cast<UConsumeContentMetaData>(meta))
	{
		n.MetaData.ContentType = o->ContentType;
		n.MetaData.ItemId = o->ItemId;
		n.MetaData.ItemType = o->ItemType;
	}

	if (auto o = Cast<UCraftItemMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.ItemType = o->ItemType;
	}

	if (auto o = Cast<UDealDamageMetaData>(meta))
	{
		n.MetaData.DamageAmount = o->DamageAmount;
		n.MetaData.SendDamageAmount = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
		n.MetaData.WeaponUsed = o->WeaponUsed;
	}

	if (auto o = Cast<UDefeatBossMetaData>(meta))
	{
		n.MetaData.EnemyCharacter = o->EnemyCharacter;
		n.MetaData.SendHealth = o->SendHealth;
		n.MetaData.Health = o->Health;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.HitType = o->HitType;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
	}

	if (auto o = Cast<UDestroyItemMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.ItemId = o->ItemId;
	}

	if (auto o = Cast<UEarnExperienceMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.Type = o->Type;
	}

	if (auto o = Cast<UEarnPointsMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.Type = o->Type;
	}

	if (auto o = Cast<UEventCompletedMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.ActionType = o->ActionType;
		n.MetaData.ActionObject = o->ActionObject;
		n.MetaData.ActionSubject = o->ActionSubject;
	}

	if (auto o = Cast<UFinishBuildingMetaData>(meta))
	{
		n.MetaData.BuildingId = o->BuildingId;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.SendBuildingLevel = o->SendBuildingLevel;
		n.MetaData.BuildingLevel = o->BuildingLevel;
	}

	if (auto o = Cast<UFinishFightMetaData>(meta))
	{
		n.MetaData.SendBattleStatus = o->SendBattleStatus;
		n.MetaData.BattleStatus = o->BattleStatus;
		n.MetaData.EnemyCharacter = o->EnemyCharacter;
		n.MetaData.SendHealth = o->SendHealth;
		n.MetaData.Health = o->Health;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.HitType = o->HitType;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
	}

	if (auto o = Cast<UFinishLapsMetaData>(meta))
	{
		n.MetaData.LapPosition = o->LapPosition;
		n.MetaData.SendLapPosition = true;
		n.MetaData.SendRequiredTime = true;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}

	if (auto o = Cast<UFinishRoundMetaData>(meta))
	{
		n.MetaData.RoundId = o->RoundId;
		n.MetaData.SendBattleStatus = o->SendBattleStatus;
		n.MetaData.BattleStatus = o->BattleStatus;
		n.MetaData.SendHealth = o->SendHealth;
		n.MetaData.Health = o->Health;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.RoundType = o->RoundType;
		n.MetaData.TimeCondition = o->TimeCondition;
	}

	if (auto o = Cast<UFinishTransportMetaData>(meta))
	{
		n.MetaData.TransportId = o->TransportId;
		n.MetaData.SendDistance = o->SendDistance;
		n.MetaData.Distance = o->Distance;
		n.MetaData.SendFuelConsumed = o->SendFuelConsumed;
		n.MetaData.FuelConsumed = o->FuelConsumed;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}

	if (auto o = Cast<UFireRateMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}

	if (auto o = Cast<UGainResourceMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.ResourceName = o->ResourceName;
	}

	if (auto o = Cast<UHealUnitMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.UnitType = o->UnitType;
	}

	if (auto o = Cast<UHireCrewMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.CrewName = o->CrewName;
	}

	if (auto o = Cast<UInstantDeathMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.CharacterName = o->CharacterName;
	}

	if (auto o = Cast<UInstantKillMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.CharacterName = o->CharacterName;
	}

	if (auto o = Cast<UKillAmmoMetaData>(meta))
	{
		n.MetaData.AmmoUsed = o->AmmoUsed;
		n.MetaData.SendAmmoUsed = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.EnemyType = o->EnemyType;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
		n.MetaData.WeaponUsed = o->WeaponUsed;
	}

	if (auto o = Cast<UKillEnemyMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.EnemyType = o->EnemyType;
		n.MetaData.KillType = o->KillType;
		n.MetaData.MapName = o->MapName;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
		n.MetaData.Realm = o->Realm;
		n.MetaData.WeaponUsed = o->WeaponUsed;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
	}

	if (auto o = Cast<ULapPositionMetaData>(meta))
	{
		n.MetaData.LapPosition = o->LapPosition;
		n.MetaData.SendLapPosition = true;
		n.MetaData.SendRequiredTime = true;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}

	if (auto o = Cast<UMatchStartMetaData>(meta))
	{
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UMatchFinishMetaData>(meta))
	{
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UObtainItemMetaData>(meta))
	{
		n.MetaData.ItemId = o->ItemId;
		n.MetaData.SendArmor = o->SendArmor;
		n.MetaData.Armor = o->Armor;
		n.MetaData.SendHealth = o->SendHealth;
		n.MetaData.Health = o->Health;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UPassLevelMetaData>(meta))
	{
		n.MetaData.LevelId = o->LevelId;
		n.MetaData.SendArmor = o->SendArmor;
		n.MetaData.Armor = o->Armor;
		n.MetaData.SendHealth = o->SendHealth;
		n.MetaData.Health = o->Health;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UPassMissionMetaData>(meta))
	{
		n.MetaData.MissionId = o->MissionId;
		n.MetaData.SendArmor = o->SendArmor;
		n.MetaData.Armor = o->Armor;
		n.MetaData.SendHealth = o->SendHealth;
		n.MetaData.Health = o->Health;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UPerformJumpMetaData>(meta))
	{
		n.MetaData.Distance = o->Distance;
		n.MetaData.SendDistance = true;
		n.MetaData.SendScore = o->SendScore;
		n.MetaData.Score = o->Score;
		n.MetaData.SendHealth = o->SendHealth;
		n.MetaData.Health = o->Health;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UPlayCardMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.CardType = o->CardType;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UPlayEffectMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.EffectType = o->EffectType;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<URacePositionMetaData>(meta))
	{
		n.MetaData.LapPosition = o->LapPosition;
		n.MetaData.SendLapPosition = true;
		n.MetaData.SendHealth = o->SendHealth;
		n.MetaData.Health = o->Health;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UReachCheckpointMetaData>(meta))
	{
		n.MetaData.CheckpointId = o->CheckpointId;
		n.MetaData.SendArmor = o->SendArmor;
		n.MetaData.Armor = o->Armor;
		n.MetaData.SendHealth = o->SendHealth;
		n.MetaData.Health = o->Health;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UReachCoordinatesMetaData>(meta))
	{
		n.MetaData.CoordinateX = o->CoordinateX;
		n.MetaData.SendCoordinateX = true;
		n.MetaData.CoordinateY = o->CoordinateY;
		n.MetaData.SendCoordinateY = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UReachDistanceMetaData>(meta))
	{
		n.MetaData.Distance = o->Distance;
		n.MetaData.SendDistance = true;
		n.MetaData.SendHealth = o->SendHealth;
		n.MetaData.Health = o->Health;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UReachHeighteMetaData>(meta))
	{
		n.MetaData.Distance = o->Distance;
		n.MetaData.SendDistance = true;
		n.MetaData.SendHealth = o->SendHealth;
		n.MetaData.Health = o->Health;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UReachMapSectionMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.MapSectionName = o->MapSectionName;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UReachProgressMetaData>(meta))
	{
		n.MetaData.LevelId = o->LevelId;
		n.MetaData.SendArmor = o->SendArmor;
		n.MetaData.Armor = o->Armor;
		n.MetaData.SendHealth = o->SendHealth;
		n.MetaData.Health = o->Health;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UReachSpeedMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.SendHealth = o->SendHealth;
		n.MetaData.Health = o->Health;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UReceiveDamageMetaData>(meta))
	{
		n.MetaData.DamageAmount = o->DamageAmount;
		n.MetaData.SendDamageAmount = true;
		n.MetaData.EnemyCharacter = o->EnemyCharacter;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
		n.MetaData.WeaponUsed = o->WeaponUsed;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UReplenishStatMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.StatType = o->StatType;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<USecureZoneMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.MapName = o->MapName;
		n.MetaData.ZoneName = o->ZoneName;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<USolvePuzzleMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.PuzzleId = o->PuzzleId;
		n.MetaData.SendPuzzleId = true;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<USpawnItemMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.ItemType = o->ItemType;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
	}
	if (auto o = Cast<USprayGraffitiMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
		n.MetaData.MapName = o->MapName;
		n.MetaData.Realm = o->Realm;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UTradeResourceMetaData>(meta))
	{
		n.MetaData.AmountGained = o->AmountGained;
		n.MetaData.SendAmountGained = true;
		n.MetaData.AmountGiven = o->AmountGiven;
		n.MetaData.SendAmountGiven = true;
		n.MetaData.ResourceGained = o->ResourceGained;
		n.MetaData.ResourceGiven = o->ResourceGiven;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UTriggerEventMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.EventType = o->EventType;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
	}
	if (auto o = Cast<UUpgradeItemMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.ItemName = o->ItemName;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UUpgradeWeaponMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.WeaponId = o->WeaponId;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
		n.MetaData.UpgradeType = o->UpgradeType;
		n.MetaData.WeaponUsed = o->WeaponUsed;
	}
	if (auto o = Cast<UUseItemMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.ItemName = o->ItemName;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UUserInviteMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
	}
	if (auto o = Cast<UWeaponActionMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.WeaponId = o->WeaponId;
		n.MetaData.WeaponUsed = o->WeaponUsed;
		n.MetaData.PlayerCharacter = o->PlayerCharacter;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UWeaponActivatedMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.WeaponType = o->WeaponType;
		n.MetaData.SendDuration = o->SendDuration;
		n.MetaData.Duration = o->Duration;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UWinBountyMetaData>(meta))
	{
		n.MetaData.Amount = o->Amount;
		n.MetaData.SendAmount = true;
		n.MetaData.BountyName = o->BountyName;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UWinMatchMetaData>(meta))
	{
		n.MetaData.AwayScore = o->AwayScore;
		n.MetaData.SendAwayScore = true;
		n.MetaData.AwayTeamId = o->AwayTeamId;
		n.MetaData.HomeScore = o->HomeScore;
		n.MetaData.SendHomeScore = true;
		n.MetaData.HomeTeamId = o->HomeTeamId;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}
	if (auto o = Cast<UWinRoundMetaData>(meta))
	{
		n.MetaData.MapName = o->MapName;
		n.MetaData.RoundId = o->RoundId;
		n.MetaData.RoundType = o->RoundType;
		n.MetaData.SendRequiredTime = o->SendRequiredTime;
		n.MetaData.RequiredTime = o->RequiredTime;
		n.MetaData.TimeCondition = o->TimeCondition;
	}

	return n;
}

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
	n.Challenges = challenges;

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

FUserInfo FUserInfo::FromScillApiUserInfo(const ScillSDK::ScillApiUserInfo o)
{
	auto n = FUserInfo();
	n.Username = o.Username.Get("");
	n.AvatarImage = o.AvatarImage.Get("");

	return n;
}

ScillSDK::ScillApiUserInfo FUserInfo::ToScillApiUserInfo(const FUserInfo o)
{
	auto n = ScillSDK::ScillApiUserInfo();

	n.Username = o.Username;
	n.AvatarImage = o.AvatarImage;

	return n;
}

FLeaderboardRanking FLeaderboardRanking::FromScillApiLeaderboardRanking(const ScillSDK::ScillApiLeaderboardRanking o)
{
	auto n = FLeaderboardRanking();

	n.MemberId = o.MemberId.Get("");
	n.MemberType = o.MemberType.Get("");
	n.Score = o.Score.Get(0);
	n.Rank = o.Rank.Get(0);

	n.AdditionalInfo = FUserInfo::FromScillApiUserInfo(o.AdditionalInfo.Get(ScillSDK::ScillApiUserInfo()));

	return n;
}

FLeaderboardMemberRanking FLeaderboardMemberRanking::FromScillApiLeaderboardMemberRanking(const ScillSDK::ScillApiLeaderboardMemberRanking o)
{
	auto n = FLeaderboardMemberRanking();

	n.LeaderboardId = o.LeaderboardId.Get("");
	n.Name = o.Name.Get("");

	n.Member = FLeaderboardRanking::FromScillApiLeaderboardRanking(o.Member.Get(ScillSDK::ScillApiLeaderboardRanking()));

	return n;
}

FLeaderboard FLeaderboard::FromScillApiLeaderboard(const ScillSDK::ScillApiLeaderboard o)
{
	auto n = FLeaderboard();

	n.LeaderboardId = o.LeaderboardId.Get("");
	n.Name = o.Name.Get("");

	TArray<FLeaderboardRanking> groupedByUsers = TArray<FLeaderboardRanking>();
	if (o.GroupedByUsers.IsSet())
		for (auto& c : o.GroupedByUsers.GetValue())
		{
			groupedByUsers.Add(FLeaderboardRanking::FromScillApiLeaderboardRanking(c));
		}
	n.GroupedByUsers = groupedByUsers;

	TArray<FLeaderboardRanking> groupedByTeams = TArray<FLeaderboardRanking>();
	if (o.GroupedByTeams.IsSet())
		for (auto& c : o.GroupedByTeams.GetValue())
		{
			groupedByTeams.Add(FLeaderboardRanking::FromScillApiLeaderboardRanking(c));
		}
	n.GroupedByTeams = groupedByTeams;

	return n;
}

FLeaderboardScore FLeaderboardScore::FromScillApiLeaderboardScore(const ScillSDK::ScillApiLeaderboardScore o)
{
	auto n = FLeaderboardScore();

	n.Score = o.Score.Get(0);
	n.Rank = o.Rank.Get(0);

	return n;
}

FLeaderboardInfo FLeaderboardInfo::FromScillApiLeaderboardInfo(const ScillSDK::ScillApiLeaderboardInfo o)
{
	auto n = FLeaderboardInfo();

	n.AppId = o.AppId.Get("");
	n.LeaderboardId = o.LeaderboardId.Get("");
	n.Name = o.Name.Get("");
	n.EventType = o.EventType.Get("");
	n.SortOrderAscending = o.SortOrderAscending.Get(false);

	return n;
}

FLeaderboardUpdatePayload FLeaderboardUpdatePayload::FromScillApiLeaderboardUpdatePayload(const ScillSDK::ScillApiLeaderboardUpdatePayload o)
{
	auto n = FLeaderboardUpdatePayload();

	n.WebhookType = o.WebhookType.Get("");
	n.LeaderboardData = FLeaderboardInfo::FromScillApiLeaderboardInfo(o.LeaderboardData.Get(ScillSDK::ScillApiLeaderboardInfo()));
	n.MemberData = FLeaderboardRanking::FromScillApiLeaderboardRanking(o.MemberData.Get(ScillSDK::ScillApiLeaderboardRanking()));
	n.OldLeaderboardRanking = FLeaderboardScore::FromScillApiLeaderboardScore(o.OldLeaderboardRanking.Get(ScillSDK::ScillApiLeaderboardScore()));
	n.NewLeaderboardRanking = FLeaderboardScore::FromScillApiLeaderboardScore(o.NewLeaderboardRanking.Get(ScillSDK::ScillApiLeaderboardScore()));

	return n;
}

FLeaderboardV2MemberMetadata FLeaderboardV2MemberMetadata::FromScillApiLeaderboardV2MemberMetadata(const ScillSDK::ScillApiLeaderboardV2MemberMetadata o)
{
	auto n = FLeaderboardV2MemberMetadata();

	n.Key = o.Key.Get("");
	n.Ranked = o.Ranked.Get(false);
	n.Score = o.Score.Get(0);
	n.Rank = o.Rank.Get(0);

	return n;
}

FLeaderboardV2Member FLeaderboardV2Member::FromScillApiLeaderboardV2Member(const ScillSDK::ScillApiLeaderboardV2Member o)
{
	auto n = FLeaderboardV2Member();

	n.MemberId = o.MemberId.Get("");
	n.MemberType = o.MemberType.Get("");
	n.Score = o.Score.Get(0);
	n.Rank = o.Rank.Get(0);
	n.AdditionalInfo = FUserInfo::FromScillApiUserInfo(o.AdditionalInfo.Get(ScillSDK::ScillApiUserInfo()));

	TArray<FLeaderboardV2MemberMetadata> meta = TArray<FLeaderboardV2MemberMetadata>();
	if (o.MetadataResults.IsSet())
		for (auto& c : o.MetadataResults.GetValue())
		{
			meta.Add(FLeaderboardV2MemberMetadata::FromScillApiLeaderboardV2MemberMetadata(c));
		}
	n.MetadataResults = meta;

	return n;
}

FLeaderboardV2MemberTypeRanking FLeaderboardV2MemberTypeRanking::FromScillApiLeaderboardV2MemberTypeRanking(const ScillSDK::ScillApiLeaderboardV2MemberTypeRanking o)
{
	auto n = FLeaderboardV2MemberTypeRanking();

	n.Count = o.Count.Get(0);

	TArray<FLeaderboardV2Member> members = TArray<FLeaderboardV2Member>();
	if (o.Members.IsSet())
		for (auto& c : o.Members.GetValue())
		{
			members.Add(FLeaderboardV2Member::FromScillApiLeaderboardV2Member(c));
		}
	n.Members = members;

	return n;
}

FLeaderboardV2MemberRanking FLeaderboardV2MemberRanking::FromScillApiLeaderboardV2MemberRanking(const ScillSDK::ScillApiLeaderboardV2MemberRanking o)
{
	auto n = FLeaderboardV2MemberRanking();

	n.LeaderboardId = o.LeaderboardId.Get("");
	n.LeaderboardName = o.LeaderboardName.Get("");
	n.LeaderboardSortOrderAscending = o.LeaderboardSortOrderAscending.Get(false);

	/*TArray<FLeaderboardV2Member> members = TArray<FLeaderboardV2Member>();
	if (o.LeaderboardMember.IsSet())
		for (auto& c : o.LeaderboardMember.GetValue())
		{
			members.Add(FLeaderboardV2Member::FromScillApiLeaderboardV2Member(c));
		}*/
	n.LeaderboardMember = FLeaderboardV2Member::FromScillApiLeaderboardV2Member(o.LeaderboardMember.Get(ScillSDK::ScillApiLeaderboardV2Member()));

	return n;
}

FLeaderboardV2ResultsLeaderboardResultsByMemberType FLeaderboardV2ResultsLeaderboardResultsByMemberType::FromScillApiLeaderboardV2ResultsLeaderboardResultsByMemberType(const ScillSDK::ScillApiLeaderboardV2ResultsLeaderboardResultsByMemberType o)
{
	auto n = FLeaderboardV2ResultsLeaderboardResultsByMemberType();

	n.Team = FLeaderboardV2MemberTypeRanking::FromScillApiLeaderboardV2MemberTypeRanking(o.Team.Get(ScillSDK::ScillApiLeaderboardV2MemberTypeRanking()));
	n.User = FLeaderboardV2MemberTypeRanking::FromScillApiLeaderboardV2MemberTypeRanking(o.User.Get(ScillSDK::ScillApiLeaderboardV2MemberTypeRanking()));

	return n;
}



FLeaderboardV2Results FLeaderboardV2Results::FromScillApiLeaderboardV2Results(const ScillSDK::ScillApiLeaderboardV2Results o)
{
	auto n = FLeaderboardV2Results();

	n.LeaderboardId = o.LeaderboardId.Get("");
	n.LeaderboardName = o.LeaderboardName.Get("");
	n.LeaderboardResultsByMemberType = FLeaderboardV2ResultsLeaderboardResultsByMemberType::FromScillApiLeaderboardV2ResultsLeaderboardResultsByMemberType(o.LeaderboardResultsByMemberType.Get(ScillSDK::ScillApiLeaderboardV2ResultsLeaderboardResultsByMemberType()));

	return n;
}

FLeaderboardV2Info FLeaderboardV2Info::FromScillApiLeaderboardV2Info(const ScillSDK::ScillApiLeaderboardV2Info o)
{
	auto n = FLeaderboardV2Info();

	n.AppId = o.AppId.Get("");
	n.LeaderboardId = o.LeaderboardId.Get("");
	n.LeaderboardName = o.LeaderboardName.Get("");
	n.EventType = o.EventType.Get("");
	n.SortOrderAscending = o.SortOrderAscending.Get(false);
	
	return n;
}

FLeaderboardV2Changed FLeaderboardV2Changed::FromScillApiLeaderboardV2Changed(const ScillSDK::ScillApiLeaderboardV2Changed o)
{
	auto n = FLeaderboardV2Changed();

	n.WebhookType = o.WebhookType.Get("");
	n.OldLeaderboard = FLeaderboardV2Info::FromScillApiLeaderboardV2Info(o.OldLeaderboard.Get(ScillSDK::ScillApiLeaderboardV2Info()));
	n.NewLeaderboard = FLeaderboardV2Info::FromScillApiLeaderboardV2Info(o.NewLeaderboard.Get(ScillSDK::ScillApiLeaderboardV2Info()));

	return n;
}

FLeaderboardV2UpdatePayload FLeaderboardV2UpdatePayload::FromScillApiLeaderboardV2UpdatePayload(const ScillSDK::ScillApiLeaderboardV2UpdatePayload o)
{
	auto n = FLeaderboardV2UpdatePayload();

	n.WebhookType = o.WebhookType.Get("");
	n.LeaderboardData = FLeaderboardV2Info::FromScillApiLeaderboardV2Info(o.LeaderboardData.Get(ScillSDK::ScillApiLeaderboardV2Info()));
	n.MemberData = FLeaderboardV2Member::FromScillApiLeaderboardV2Member(o.MemberData.Get(ScillSDK::ScillApiLeaderboardV2Member()));
	n.OldLeaderboardRanking = FLeaderboardScore::FromScillApiLeaderboardScore(o.OldLeaderboardRanking.Get(ScillSDK::ScillApiLeaderboardScore()));
	n.NewLeaderboardRanking = FLeaderboardScore::FromScillApiLeaderboardScore(o.NewLeaderboardRanking.Get(ScillSDK::ScillApiLeaderboardScore()));

	return n;
}

// ------------------------------------------------
// Map Leaderboard V1 to Leaderboard V2
// ------------------------------------------------

FLeaderboardV2Results FLeaderboardV2Results::FromScillApiLeaderboard(const ScillSDK::ScillApiLeaderboard o)
{
	auto n = FLeaderboardV2Results();

	n.LeaderboardId = o.LeaderboardId.Get("");
	n.LeaderboardName = o.Name.Get("");
	n.LeaderboardResultsByMemberType = FLeaderboardV2ResultsLeaderboardResultsByMemberType();

	n.LeaderboardResultsByMemberType.User = FLeaderboardV2MemberTypeRanking();
	auto members = TArray< FLeaderboardV2Member>();
	if (o.GroupedByUsers.IsSet())
	{
		n.LeaderboardResultsByMemberType.User.Count = o.GroupedByUsers.GetValue().Num();

		for (auto& c : o.GroupedByUsers.GetValue())
		{
			members.Add(FLeaderboardV2Member::FromScillApiLeaderboardRanking(c));
		}
	}
	n.LeaderboardResultsByMemberType.User.Members = members;

	n.LeaderboardResultsByMemberType.Team = FLeaderboardV2MemberTypeRanking();
	auto members2 = TArray< FLeaderboardV2Member>();
	if (o.GroupedByTeams.IsSet())
	{
		n.LeaderboardResultsByMemberType.Team.Count = o.GroupedByTeams.GetValue().Num();

		for (auto& c : o.GroupedByTeams.GetValue())
		{
			members2.Add(FLeaderboardV2Member::FromScillApiLeaderboardRanking(c));
		}
	}
	n.LeaderboardResultsByMemberType.Team.Members = members2;

	return n;
}

FLeaderboardV2Member FLeaderboardV2Member::FromScillApiLeaderboardRanking(const ScillSDK::ScillApiLeaderboardRanking o)
{
	auto n = FLeaderboardV2Member();

	n.MemberId = o.MemberId.Get("");
	n.MemberType = o.MemberType.Get("");
	n.Score = o.Score.Get(0);
	n.Rank = o.Rank.Get(0);
	n.MetadataResults = TArray<FLeaderboardV2MemberMetadata>();
	n.AdditionalInfo = FUserInfo::FromScillApiUserInfo(o.AdditionalInfo.Get(ScillSDK::ScillApiUserInfo()));

	return n;
}

FLeaderboardV2MemberRanking FLeaderboardV2MemberRanking::FromScillApiLeaderboardMemberRanking(const ScillSDK::ScillApiLeaderboardMemberRanking o)
{
	auto n = FLeaderboardV2MemberRanking();
	
	n.LeaderboardId = o.LeaderboardId.Get("");
	n.LeaderboardName = o.Name.Get("");

	n.LeaderboardMember = FLeaderboardV2Member::FromScillApiLeaderboardRanking(o.Member.Get(ScillSDK::ScillApiLeaderboardRanking()));

	return n;
}

FLeaderboardV2UpdatePayload FLeaderboardV2UpdatePayload::FromScillApiLeaderboardUpdatePayload(const ScillSDK::ScillApiLeaderboardUpdatePayload o)
{
	auto n = FLeaderboardV2UpdatePayload();

	n.WebhookType = o.WebhookType.Get("");
	n.LeaderboardData = FLeaderboardV2Info::FromScillApiLeaderboardInfo(o.LeaderboardData.Get(ScillSDK::ScillApiLeaderboardInfo()));
	n.MemberData = FLeaderboardV2Member::FromScillApiLeaderboardRanking(o.MemberData.Get(ScillSDK::ScillApiLeaderboardRanking()));
	n.OldLeaderboardRanking = FLeaderboardScore::FromScillApiLeaderboardScore(o.OldLeaderboardRanking.Get(ScillSDK::ScillApiLeaderboardScore()));
	n.NewLeaderboardRanking = FLeaderboardScore::FromScillApiLeaderboardScore(o.NewLeaderboardRanking.Get(ScillSDK::ScillApiLeaderboardScore()));

	return n;
}

FLeaderboardV2Info FLeaderboardV2Info::FromScillApiLeaderboardInfo(const ScillSDK::ScillApiLeaderboardInfo o)
{
	auto n = FLeaderboardV2Info();

	n = FLeaderboardV2Info();
	n.AppId = o.AppId.Get("");
	n.LeaderboardId = o.LeaderboardId.Get("");
	n.LeaderboardName = o.Name.Get("");
	n.EventType = o.EventType.Get("");
	n.SortOrderAscending = o.SortOrderAscending.Get(false);

	return n;
}