// Fill out your copyright notice in the Description page of Project Settings.


#include "ScillBlueprintClasses/ScillStructs.h"

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
