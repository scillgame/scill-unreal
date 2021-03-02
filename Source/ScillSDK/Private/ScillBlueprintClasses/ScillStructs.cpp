// Fill out your copyright notice in the Description page of Project Settings.


#include "ScillBlueprintClasses/ScillStructs.h"

FBattlePass FBattlePass::FromScillApiBattlePass(ScillSDK::ScillApiBattlePass battlePass)
{
	auto bp = FBattlePass();

	bp.AppId = battlePass.AppId.Get("");
	bp.BattlePassDescription = battlePass.BattlePassDescription.Get("");
	bp.BattlePassDisclaimer = battlePass.BattlePassDisclaimer.Get("");

	// TODO:
	// Finish writing this function

	return bp;
}
