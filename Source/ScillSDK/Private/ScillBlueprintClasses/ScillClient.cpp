// Fill out your copyright notice in the Description page of Project Settings.


#include "ScillBlueprintClasses/ScillClient.h"

#include "ScillApiWrapper/ScillApiAuthApiOperations.h"
#include "ScillApiWrapper/ScillApiEventsApiOperations.h"
#include "ScillApiWrapper/ScillApiLeaderboardsApiOperations.h"
#include "ScillApiWrapper/ScillApiLeaderboardsV2ApiOperations.h"
#include "ScillSDK.h"

// Sets default values for this component's properties
UScillClient::UScillClient()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UScillClient::SetAccessToken(FString newAccessToken)
{
	this->battlePassesApi.AddHeaderParam("Authorization", "Bearer " + newAccessToken);
	this->challengesApi.AddHeaderParam("Authorization", "Bearer " + newAccessToken);
	this->eventsApi.AddHeaderParam("Authorization", "Bearer " + newAccessToken);
	this->authApi.AddHeaderParam("Authorization", "Bearer " + newAccessToken);
	this->leaderboardsApi.AddHeaderParam("Authorization", "Bearer " + newAccessToken);
	this->leaderboardsApiV2.AddHeaderParam("Authorization", "Bearer " + newAccessToken);
	this->AccessToken = newAccessToken;
	
	auto gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (gameInstance->Implements<UScillLevelPersistenceInterface>())
	{
		IScillLevelPersistenceInterface::Execute_SetAccessToken(gameInstance, newAccessToken);
	}
}

FString UScillClient::GetAccessToken() const
{
	auto value = FString();

	value = this->AccessToken;

	auto gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (gameInstance->Implements<UScillLevelPersistenceInterface>())
	{
		auto instanceValue = FString();
		IScillLevelPersistenceInterface::Execute_GetAccessToken(gameInstance, instanceValue);
		if (!instanceValue.IsEmpty())
			value = instanceValue;
	}

	return value;
}

FString UScillClient::GetUserId() const
{
	auto value = FString();

	value = this->UserId;

	auto gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (gameInstance->Implements<UScillLevelPersistenceInterface>())
	{
		auto instanceValue = FString();
		IScillLevelPersistenceInterface::Execute_GetUserId(gameInstance, instanceValue);
		if (!instanceValue.IsEmpty())
			value = instanceValue;
	}

	return value;
}

void UScillClient::SetUserId(FString newUserId)
{
	this->UserId = newUserId;

	auto gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (gameInstance->Implements<UScillLevelPersistenceInterface>())
	{
		IScillLevelPersistenceInterface::Execute_SetUserId(gameInstance, newUserId);
	}
}

// ----------------------------------------------------------------------------------------------------------------------------
// Battle Passes
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ActivateBattlePassLevel(FString levelId, FHttpResponseReceived responseReceived)
{
	auto activateBattlePassRequest = ScillSDK::ScillApiBattlePassesApi::ActivateBattlePassLevelRequest();

	activateBattlePassRequest.AppId = AppId;
	activateBattlePassRequest.LevelId = levelId;

	FGuid guid = FGuid::NewGuid();

	callbackMapResponseReceived.Add(guid, responseReceived);

	auto activateBattlePassRequestDelegate = ScillSDK::ScillApiBattlePassesApi::FActivateBattlePassLevelDelegate::CreateUObject(this, &UScillClient::ReceiveActivateBattlePassLevelResponse, guid);
	
	battlePassesApi.ActivateBattlePassLevel(activateBattlePassRequest, activateBattlePassRequestDelegate);
}

void UScillClient::ClaimBattlePassLevel(FString levelId, FHttpResponseReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::ClaimBattlePassLevelRewardRequest();

	request.AppId = AppId;
	request.LevelId = levelId;

	FGuid guid = FGuid::NewGuid();

	callbackMapResponseReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FClaimBattlePassLevelRewardDelegate::CreateUObject(this, &UScillClient::ReceiveClaimBattlePassLevelResponse, guid);

	battlePassesApi.ClaimBattlePassLevelReward(request, delegate);
}

void UScillClient::GetActiveBattlePasses(FBattlePassArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::GetActiveBattlePassesRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FGetActiveBattlePassesDelegate::CreateUObject(this, &UScillClient::ReceiveActiveBattlePassesResponse, guid);

	battlePassesApi.GetActiveBattlePasses(request, delegate);
}

void UScillClient::GetUnlockedPasses(FBattlePassArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::GetUnlockedBattlePassesRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FGetUnlockedBattlePassesDelegate::CreateUObject(this, &UScillClient::ReceiveUnlockedBattlePassesResponse, guid);

	battlePassesApi.GetUnlockedBattlePasses(request, delegate);
}

void UScillClient::GetAllPassLevels(FBattlePassLevelArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::GetAllBattlePassLevelsRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassLevelArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FGetAllBattlePassLevelsDelegate::CreateUObject(this, &UScillClient::ReceiveAllBattlePassLevelsResponse, guid);

	battlePassesApi.GetAllBattlePassLevels(request, delegate);
}

void UScillClient::GetBattlePass(FString battlePassId, FBattlePassReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::GetBattlePassRequest();

	request.AppId = AppId;
	request.BattlePassId = battlePassId;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FGetBattlePassDelegate::CreateUObject(this, &UScillClient::ReceiveBattlePassResponse, guid);

	battlePassesApi.GetBattlePass(request, delegate);
}

void UScillClient::GetBattlePassLevels(FString battlePassId, FBattlePassLevelArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::GetBattlePassLevelsRequest();

	request.AppId = AppId;
	request.BattlePassId = battlePassId;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassLevelArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FGetBattlePassLevelsDelegate::CreateUObject(this, &UScillClient::ReceiveBattlePassLevelsResponse, guid);

	battlePassesApi.GetBattlePassLevels(request, delegate);
}

void UScillClient::GetBattlePasses(FBattlePassArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::GetBattlePassesRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FGetBattlePassesDelegate::CreateUObject(this, &UScillClient::ReceiveBattlePassesResponse, guid);

	battlePassesApi.GetBattlePasses(request, delegate);
}

void UScillClient::UnlockBattlePass(FString battlePassId, float purchasePrice, FString purchaseCurrency, FBattlePassUnlockInfoReceived responseReceived)
{
	auto request = ScillSDK::ScillApiBattlePassesApi::UnlockBattlePassRequest();

	request.AppId = AppId;
	request.BattlePassId = battlePassId;

	auto unlockPayload = ScillSDK::ScillApiBattlePassUnlockPayload();
	unlockPayload.PurchasePrice = purchasePrice;
	unlockPayload.PurchaseCurrency = purchaseCurrency;

	request.ScillApiBattlePassUnlockPayload = unlockPayload;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassUnlockInfoReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiBattlePassesApi::FUnlockBattlePassDelegate::CreateUObject(this, &UScillClient::ReceiveUnlockBattlePassResponse, guid);

	battlePassesApi.UnlockBattlePass(request, delegate);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Challenges
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ActivatePersonalChallenge(FString challengeId, FChallengeReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::ActivatePersonalChallengeRequest();

	request.AppId = AppId;
	request.ChallengeId = challengeId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FActivatePersonalChallengeDelegate::CreateUObject(this, &UScillClient::ReceiveActivatePersonalChallengeResponse, guid);

	challengesApi.ActivatePersonalChallenge(request, delegate);
}

void UScillClient::CancelPersonalChallenge(FString challengeId, FChallengeReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::CancelPersonalChallengeRequest();

	request.AppId = AppId;
	request.ChallengeId = challengeId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FCancelPersonalChallengeDelegate::CreateUObject(this, &UScillClient::ReceiveCancelPersonalChallengeResponse, guid);

	challengesApi.CancelPersonalChallenge(request, delegate);
}

void UScillClient::ClaimPersonalChallengeReward(FString challengeId, FChallengeReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::ClaimPersonalChallengeRewardRequest();

	request.AppId = AppId;
	request.ChallengeId = challengeId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FClaimPersonalChallengeRewardDelegate::CreateUObject(this, &UScillClient::ReceiveClaimPersonalChallengeRewardResponse, guid);

	challengesApi.ClaimPersonalChallengeReward(request, delegate);
}

void UScillClient::GetActivePersonalChallenges(FChallengeCategoryArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::GetActivePersonalChallengesRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeCategoryArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FGetActivePersonalChallengesDelegate::CreateUObject(this, &UScillClient::ReceiveGetActivePersonalChallengesResponse, guid);

	challengesApi.GetActivePersonalChallenges(request, delegate);
}

void UScillClient::GetAllPersonalChallenges(FChallengeCategoryArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::GetAllPersonalChallengesRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeCategoryArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FGetAllPersonalChallengesDelegate::CreateUObject(this, &UScillClient::ReceiveGetAllPersonalChallengesResponse, guid);

	challengesApi.GetAllPersonalChallenges(request, delegate);
}

void UScillClient::GetPersonalChallenges(FChallengeCategoryArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::GetPersonalChallengesRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeCategoryArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FGetPersonalChallengesDelegate::CreateUObject(this, &UScillClient::ReceiveGetPersonalChallengesResponse, guid);

	challengesApi.GetPersonalChallenges(request, delegate);
}

void UScillClient::GetUnresolvedPersonalChallenges(FChallengeCategoryArrayReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::GetUnresolvedPersonalChallengesRequest();

	request.AppId = AppId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeCategoryArrayReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FGetUnresolvedPersonalChallengesDelegate::CreateUObject(this, &UScillClient::ReceiveGetUnresolvedPersonalChallengesResponse, guid);

	challengesApi.GetUnresolvedPersonalChallenges(request, delegate);
}

void UScillClient::GetPersonalChallengeById(FString challengeId, FChallengeReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::GetPersonalChallengeByIdRequest();

	request.AppId = AppId;
	request.ChallengeId = challengeId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FGetPersonalChallengeByIdDelegate::CreateUObject(this, &UScillClient::ReceiveGetPersonalChallengeByIdResponse, guid);

	challengesApi.GetPersonalChallengeById(request, delegate);
}

void UScillClient::UnlockPersonalChallenge(FString challengeId, FChallengeReceived responseReceived)
{
	auto request = ScillSDK::ScillApiChallengesApi::UnlockPersonalChallengeRequest();

	request.AppId = AppId;
	request.ChallengeId = challengeId;

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiChallengesApi::FUnlockPersonalChallengeDelegate::CreateUObject(this, &UScillClient::ReceiveUnlockPersonalChallengeResponse, guid);

	challengesApi.UnlockPersonalChallenge(request, delegate);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Leaderboards (Deprecated)
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::GetLeaderboardV1(FString BoardId, int CurrentPage, int PageSize, FString Language, FLeaderboardReceived responseReceived)
{
	auto request = ScillSDK::ScillApiLeaderboardsApi::GetLeaderboardRequest();

	request.LeaderboardId = BoardId;
	request.CurrentPage = CurrentPage;
	if(PageSize != 0)
		request.PageSize = PageSize;
	if(!Language.IsEmpty())
		request.Language = Language;

	FGuid guid = FGuid::NewGuid();

	callbackMapLeaderboardReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiLeaderboardsApi::FGetLeaderboardDelegate::CreateUObject(this, &UScillClient::ReceiveGetLeaderboardResponse, guid);

	leaderboardsApi.GetLeaderboard(request, delegate);
}

void UScillClient::GetLeaderboardsV1(int CurrentPage, int PageSize, FString Language, FLeaderboardsReceived responseReceived)
{
	auto request = ScillSDK::ScillApiLeaderboardsApi::GetLeaderboardsRequest();

	request.CurrentPage = CurrentPage;
	if (PageSize != 0)
		request.PageSize = PageSize;
	if (!Language.IsEmpty())
		request.Language = Language;

	FGuid guid = FGuid::NewGuid();

	callbackMapLeaderboardsReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiLeaderboardsApi::FGetLeaderboardsDelegate::CreateUObject(this, &UScillClient::ReceiveGetLeaderboardsResponse, guid);

	leaderboardsApi.GetLeaderboards(request, delegate);
}

void UScillClient::GetLeaderboardRankingV1(FString MemberType, FString MemberId, FString LeaderboardId, FString Language, FLeaderboardRankingReceived responseReceived)
{
	auto request = ScillSDK::ScillApiLeaderboardsApi::GetLeaderboardRankingRequest();

	request.LeaderboardId = LeaderboardId;
	request.MemberType = MemberType;
	request.MemberId = MemberId;

	if (!Language.IsEmpty())
		request.Language = Language;

	FGuid guid = FGuid::NewGuid();

	callbackMapLeaderboardRankingReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiLeaderboardsApi::FGetLeaderboardRankingDelegate::CreateUObject(this, &UScillClient::ReceiveGetLeaderboardRankingResponse, guid);

	leaderboardsApi.GetLeaderboardRanking(request, delegate);
}

void UScillClient::GetLeaderboardRankingsV1(FString MemberType, FString MemberId, FString Language, FLeaderboardRankingsReceived responseReceived)
{
	auto request = ScillSDK::ScillApiLeaderboardsApi::GetLeaderboardRankingsRequest();

	request.MemberType = MemberType;
	request.MemberId = MemberId;

	if (!Language.IsEmpty())
		request.Language = Language;

	FGuid guid = FGuid::NewGuid();

	callbackMapLeaderboardRankingsReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiLeaderboardsApi::FGetLeaderboardRankingsDelegate::CreateUObject(this, &UScillClient::ReceiveGetLeaderboardRankingsResponse, guid);

	leaderboardsApi.GetLeaderboardRankings(request, delegate);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Leaderboards V2
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::GetLeaderboardV2(FString BoardId, FString StartDate, FString EndDate, FString Aggregate, int CurrentPage, int CurrentPosition, int PageSize, FString Language, FLeaderboardReceived responseReceived)
{
	auto request = ScillSDK::ScillApiLeaderboardsV2Api::GetLeaderboardV2Request();

	request.LeaderboardId = BoardId;
	request.CurrentPage = CurrentPage;
	if (PageSize != 0)
		request.PageSize = PageSize;
	if (!Language.IsEmpty())
		request.Language = Language;

	request.StartDate = StartDate;
	request.EndDate = EndDate;
	if (!Aggregate.IsEmpty())
	{
		request.Aggregate = "SUM";
	}
	else
	{
		request.Aggregate = Aggregate;
	}

	FGuid guid = FGuid::NewGuid();

	callbackMapLeaderboardReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiLeaderboardsV2Api::FGetLeaderboardV2Delegate::CreateUObject(this, &UScillClient::ReceiveGetLeaderboardResponseV2, guid);

	leaderboardsApiV2.GetLeaderboardV2(request, delegate);
}

void UScillClient::GetLeaderboardRankingV2(FString MemberType, FString MemberId, FString LeaderboardId, FString StartDate, FString EndDate, FString Aggregate, FString Language, FLeaderboardRankingReceived responseReceived)
{
	auto request = ScillSDK::ScillApiLeaderboardsV2Api::GetLeaderboardV2RankingRequest();

	request.MemberType = MemberType;
	request.MemberId = MemberId;
	request.LeaderboardId = LeaderboardId;

	request.StartDate = StartDate;
	request.EndDate = EndDate;
	if (!Aggregate.IsEmpty())
	{
		request.Aggregate = "SUM";
	}
	else
	{
		request.Aggregate = Aggregate;
	}


	if (!Language.IsEmpty())
		request.Language = Language;

	FGuid guid = FGuid::NewGuid();

	callbackMapLeaderboardRankingReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiLeaderboardsV2Api::FGetLeaderboardV2RankingDelegate::CreateUObject(this, &UScillClient::ReceiveGetLeaderboardRankingResponseV2, guid);

	leaderboardsApiV2.GetLeaderboardV2Ranking(request, delegate);
}

void UScillClient::GetLeaderboardRankingsV2(FString MemberType, FString MemberId, FString StartDate, FString EndDate, FString Aggregate, FString Language, FLeaderboardRankingsReceived responseReceived)
{
	auto request = ScillSDK::ScillApiLeaderboardsV2Api::GetLeaderboardV2RankingsRequest();

	request.MemberType = MemberType;
	request.MemberId = MemberId;

	request.StartDate = StartDate;
	request.EndDate = EndDate;
	if (!Aggregate.IsEmpty())
	{
		request.Aggregate = "SUM";
	}
	else
	{
		request.Aggregate = Aggregate;
	}


	if (!Language.IsEmpty())
		request.Language = Language;

	FGuid guid = FGuid::NewGuid();

	callbackMapLeaderboardRankingsReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiLeaderboardsV2Api::FGetLeaderboardV2RankingsDelegate::CreateUObject(this, &UScillClient::ReceiveGetLeaderboardRankingsResponseV2, guid);

	leaderboardsApiV2.GetLeaderboardV2Rankings(request, delegate);
}

void UScillClient::GetLeaderboardsV2(FString StartDate, FString EndDate, FString Aggregate, int CurrentPage, int CurrentPosition, int PageSize, FString Language, FLeaderboardsReceived responseReceived)
{
	auto request = ScillSDK::ScillApiLeaderboardsV2Api::GetLeaderboardsV2Request();

	request.CurrentPage = CurrentPage;
	if (PageSize != 0)
		request.PageSize = PageSize;
	if (!Language.IsEmpty())
		request.Language = Language;

	request.StartDate = StartDate;
	request.EndDate = EndDate;
	if (!Aggregate.IsEmpty())
	{
		request.Aggregate = "SUM";
	}
	else
	{
		request.Aggregate = Aggregate;
	}

	FGuid guid = FGuid::NewGuid();

	callbackMapLeaderboardsReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiLeaderboardsV2Api::FGetLeaderboardsV2Delegate::CreateUObject(this, &UScillClient::ReceiveGetLeaderboardsResponseV2, guid);

	leaderboardsApiV2.GetLeaderboardsV2(request, delegate);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Leaderboards Version Agnostic
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::GetLeaderboard(FString BoardId, FString StartDate, FString EndDate, FString Aggregate, int CurrentPage, int CurrentPosition, int PageSize, FString Language, FLeaderboardReceived responseReceived)
{
	if (this->LeaderboardVersionNumber == 1)
	{
		this->GetLeaderboardV1(BoardId, CurrentPage, PageSize, Language, responseReceived);
	}
	else
	{
		this->GetLeaderboardV2(BoardId, StartDate, EndDate, Aggregate, CurrentPage, CurrentPosition, PageSize, Language, responseReceived);
	}
}

void UScillClient::GetLeaderboardRanking(FString MemberType, FString MemberId, FString LeaderboardId, FString StartDate, FString EndDate, FString Aggregate, FString Language, FLeaderboardRankingReceived responseReceived)
{
	if (this->LeaderboardVersionNumber == 1)
	{
		this->GetLeaderboardRankingV1(MemberType, MemberId, LeaderboardId, Language, responseReceived);
	}
	else
	{
		this->GetLeaderboardRankingV2(MemberType, MemberId, LeaderboardId, StartDate, EndDate, Aggregate, Language, responseReceived);
	}
}

void UScillClient::GetLeaderboardRankings(FString MemberType, FString MemberId, FString StartDate, FString EndDate, FString Aggregate, FString Language, FLeaderboardRankingsReceived responseReceived)
{
	if (this->LeaderboardVersionNumber == 1)
	{
		this->GetLeaderboardRankingsV1(MemberType, MemberId, Language, responseReceived);
	}
	else
	{
		this->GetLeaderboardRankingsV2(MemberType, MemberId, StartDate, EndDate, Aggregate, Language, responseReceived);
	}
}

void UScillClient::GetLeaderboards(FString StartDate, FString EndDate, FString Aggregate, int CurrentPage, int CurrentPosition, int PageSize, FString Language, FLeaderboardsReceived responseReceived)
{
	if (this->LeaderboardVersionNumber == 1)
	{
		this->GetLeaderboardsV1(CurrentPage, PageSize, Language, responseReceived);
	}
	else
	{
		this->GetLeaderboardsV2(StartDate, EndDate, Aggregate, CurrentPage, CurrentPosition, PageSize, Language, responseReceived);
	}
}

void UScillClient::SetUserData(FUserInfo UserInfo, FUserInfoReceived responseReceived)
{
	auto request = ScillSDK::ScillApiAuthApi::SetUserInfoRequest();

	request.ScillApiUserInfo = FUserInfo::ToScillApiUserInfo(UserInfo);

	FGuid guid = FGuid::NewGuid();

	callbackMapUserInfoReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiAuthApi::FSetUserInfoDelegate::CreateUObject(this, &UScillClient::ReceiveSetUserInfoResponse, guid);

	authApi.SetUserInfo(request, delegate);
}

void UScillClient::GetUserData(FUserInfoReceived responseReceived)
{
	auto request = ScillSDK::ScillApiAuthApi::GetUserInfoRequest();

	FGuid guid = FGuid::NewGuid();

	callbackMapUserInfoReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiAuthApi::FGetUserInfoDelegate::CreateUObject(this, &UScillClient::ReceiveGetUserInfoResponse, guid);

	authApi.GetUserInfo(request, delegate);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Events
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::SendEvent(FScillEventPayload payload, FHttpResponseReceived responseReceived)
{
	auto request = ScillSDK::ScillApiEventsApi::SendEventRequest();

	request.ScillApiEventPayload = FScillEventPayload::ToScillApiEventPayload(payload);

	FGuid guid = FGuid::NewGuid();

	callbackMapResponseReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiEventsApi::FSendEventDelegate::CreateUObject(this, &UScillClient::ReceiveSendEventResponse, guid);

	eventsApi.SendEvent(request, delegate);
}

void UScillClient::SendScillEvent(UEventMetaDataBase* payload, FHttpResponseReceived responseReceived)
{
	if (!payload)
	{
		UE_LOG(LogScillSDK, Error, TEXT("Payload must be set! Use the Construct Object From Class Node to create an event payload."));
		return;
	}

	this->SendEvent(FScillEventPayload::FromScillEventPayloadBase(payload), responseReceived);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Realtime Updates
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ReceiveChallengeUpdates(FChallengeChangeReceived responseReceived)
{
	auto request = ScillSDK::ScillApiAuthApi::GetUserChallengesNotificationTopicRequest();

	FGuid guid = FGuid::NewGuid();

	callbackMapChallengeChangeReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiAuthApi::FGetUserChallengesNotificationTopicDelegate::CreateUObject(this, &UScillClient::ReceiveChallengeChangeTopic, guid);

	authApi.GetUserChallengesNotificationTopic(request, delegate);
}

void UScillClient::ReceiveBattlePassUpdates(FString battlePassId, FBattlePassChangeReceived responseReceived)
{
	auto request = ScillSDK::ScillApiAuthApi::GetUserBattlePassNotificationTopicRequest();

	request.BattlePassId = battlePassId;

	FGuid guid = FGuid::NewGuid();

	callbackMapBattlePassChangeReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiAuthApi::FGetUserBattlePassNotificationTopicDelegate::CreateUObject(this, &UScillClient::ReceiveBattlePassChangeTopic, guid);

	authApi.GetUserBattlePassNotificationTopic(request, delegate);
}

void UScillClient::ReceiveLeaderboardUpdates(FString LeaderboardId, FLeaderboardChangeReceived responseReceived)
{
	auto request = ScillSDK::ScillApiAuthApi::GetLeaderboardNotificationTopicRequest();

	request.LeaderboardId = LeaderboardId;

	FGuid guid = FGuid::NewGuid();

	callbackMapLeaderboardChangeReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiAuthApi::FGetLeaderboardNotificationTopicDelegate::CreateUObject(this, &UScillClient::ReceiveLeaderboardChangeTopic, guid);

	authApi.GetLeaderboardNotificationTopic(request, delegate);
}


// ----------------------------------------------------------------------------------------------------------------------------
// UActor Event Implementations
// ----------------------------------------------------------------------------------------------------------------------------

// Called when the game starts
void UScillClient::BeginPlay()
{
	Super::BeginPlay();
	
	mqtt = NewObject<UScillMqtt>();
	mqtt->leaderboardVersion = this->LeaderboardVersionNumber;

	auto accessToken = FString();
	auto userId = FString();

	auto gameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (gameInstance->Implements<UScillLevelPersistenceInterface>())
	{
		IScillLevelPersistenceInterface::Execute_GetAccessToken(gameInstance, accessToken);
		IScillLevelPersistenceInterface::Execute_GetUserId(gameInstance, userId);
	}

	// Set access token to value of level persistence
	if (!accessToken.IsEmpty())
		this->AccessToken = accessToken;

	if (!userId.IsEmpty())
		this->UserId = userId;

	SetAccessToken(this->AccessToken);
	SetUserId(this->UserId);

	this->battlePassesApi.AddHeaderParam("Authorization", "Bearer " + this->AccessToken);
	this->battlePassesApi.SetURL(TEXT("https://es.scill.4players.io"));

	this->challengesApi.AddHeaderParam("Authorization", "Bearer " + this->AccessToken);
	this->challengesApi.SetURL(TEXT("https://pcs.scill.4players.io"));

	this->eventsApi.AddHeaderParam("Authorization", "Bearer " + this->AccessToken);
	this->eventsApi.SetURL(TEXT("https://ep.scill.4players.io"));

	this->authApi.AddHeaderParam("Authorization", "Bearer " + this->AccessToken);
	this->authApi.SetURL(TEXT("https://us.scill.4players.io"));

	this->leaderboardsApi.AddHeaderParam("Authorization", "Bearer " + this->AccessToken);
	this->leaderboardsApi.SetURL(TEXT("https://ls.scill.4players.io"));

	this->leaderboardsApiV2.AddHeaderParam("Authorization", "Bearer " + this->AccessToken);
	this->leaderboardsApiV2.SetURL(TEXT("https://ls.scill.4players.io"));

	GetWorld()->GetTimerManager().SetTimer(PingTimer, this, &UScillClient::MqttPing, 250, true);
}

void UScillClient::OnRealtimeConnectionOpen(FRealtimeConnectionEstablished onConnectionEstablished)
{
	FGuid guid = FGuid::NewGuid();
	callbackMqttConnectionEstablished.Add(guid, onConnectionEstablished);
	mqtt->MqttConnectionEstablishedDelegate.AddUObject(this, &UScillClient::MqttConnectionOpen, guid);
}

void UScillClient::MqttConnectionOpen(FGuid guid) const
{
	auto callback = callbackMqttConnectionEstablished.FindRef(guid);
	callback.ExecuteIfBound();
	callbackMqttConnectionEstablished.Remove(guid);
}

void UScillClient::RetrieveUserInfoOrSetToDefault()
{
	FUserInfoReceived Delegate;
	Delegate.BindDynamic(this, &UScillClient::UserInfoRetrieved);
	this->GetUserData(Delegate);
}

void UScillClient::UserInfoRetrieved(const FUserInfo& UserInfo, bool Success)
{
	if (!Success || UserInfo.Username.IsEmpty())
	{
		//Send default User Info because there is none yet for this user.
		FUserInfoReceived Delegate;

		auto ui = FUserInfo();
		ui.Username = TEXT("John Doe");
		ui.AvatarImage = TEXT("0");

		this->SetUserData(ui, Delegate);
	}
	else
	{
		this->CurrentUserInfo = UserInfo;
	}
}

void UScillClient::MqttPing()
{
	if(mqtt && mqtt->MqttConnected)
		mqtt->Ping();
}

void UScillClient::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
	if (GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(PingTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(PingTimer);
	}
	if (mqtt && !(mqtt->Destroyed))
	{
		mqtt->Destroy();
	}
}

// ----------------------------------------------------------------------------------------------------------------------------
// Battle Passes Handlers
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ReceiveActivateBattlePassLevelResponse(const ScillSDK::ScillApiBattlePassesApi::ActivateBattlePassLevelResponse& Response, FGuid guid) const
{
	auto callback = callbackMapResponseReceived.FindRef(guid);
	callback.ExecuteIfBound(Response.IsSuccessful());

	callbackMapResponseReceived.Remove(guid);
}

void UScillClient::ReceiveClaimBattlePassLevelResponse(const ScillSDK::ScillApiBattlePassesApi::ClaimBattlePassLevelRewardResponse& Response, FGuid guid) const
{
	auto callback = callbackMapResponseReceived.FindRef(guid);
	callback.ExecuteIfBound(Response.IsSuccessful());

	callbackMapResponseReceived.Remove(guid);
}

void UScillClient::ReceiveActiveBattlePassesResponse(const ScillSDK::ScillApiBattlePassesApi::GetActiveBattlePassesResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassArrayReceived.FindRef(guid);

	TArray<FBattlePass> battlePasses = TArray<FBattlePass>();

	for (auto bp : Response.Content)
	{
		battlePasses.Add(FBattlePass::FromScillApiBattlePass(bp));
	}

	callback.ExecuteIfBound(battlePasses,Response.IsSuccessful());

	callbackMapBattlePassArrayReceived.Remove(guid);
}

void UScillClient::ReceiveUnlockedBattlePassesResponse(const ScillSDK::ScillApiBattlePassesApi::GetUnlockedBattlePassesResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassArrayReceived.FindRef(guid);

	TArray<FBattlePass> battlePasses = TArray<FBattlePass>();

	for (auto bp : Response.Content)
	{
		battlePasses.Add(FBattlePass::FromScillApiBattlePass(bp));
	}

	callback.ExecuteIfBound(battlePasses, Response.IsSuccessful());

	callbackMapBattlePassArrayReceived.Remove(guid);
}

void UScillClient::ReceiveAllBattlePassLevelsResponse(const ScillSDK::ScillApiBattlePassesApi::GetAllBattlePassLevelsResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassLevelArrayReceived.FindRef(guid);

	TArray<FBattlePassLevel> battlePasses = TArray<FBattlePassLevel>();

	for (auto bp : Response.Content)
	{
		battlePasses.Add(FBattlePassLevel::FromScillApiBattlePassLevel(bp));
	}

	callback.ExecuteIfBound(battlePasses, Response.IsSuccessful());

	callbackMapBattlePassLevelArrayReceived.Remove(guid);
}

void UScillClient::ReceiveBattlePassResponse(const ScillSDK::ScillApiBattlePassesApi::GetBattlePassResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassReceived.FindRef(guid);

	callback.ExecuteIfBound(FBattlePass::FromScillApiBattlePass(Response.Content), Response.IsSuccessful());

	callbackMapBattlePassReceived.Remove(guid);
}

void UScillClient::ReceiveBattlePassLevelsResponse(const ScillSDK::ScillApiBattlePassesApi::GetBattlePassLevelsResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassLevelArrayReceived.FindRef(guid);

	TArray<FBattlePassLevel> battlePassLevels = TArray<FBattlePassLevel>();

	for (auto bp : Response.Content)
	{
		battlePassLevels.Add(FBattlePassLevel::FromScillApiBattlePassLevel(bp));
	}

	callback.ExecuteIfBound(battlePassLevels, Response.IsSuccessful());

	callbackMapBattlePassLevelArrayReceived.Remove(guid);
}

void UScillClient::ReceiveBattlePassesResponse(const ScillSDK::ScillApiBattlePassesApi::GetBattlePassesResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassArrayReceived.FindRef(guid);

	TArray<FBattlePass> battlePasses = TArray<FBattlePass>();

	for (auto bp : Response.Content)
	{
		battlePasses.Add(FBattlePass::FromScillApiBattlePass(bp));
	}

	callback.ExecuteIfBound(battlePasses, Response.IsSuccessful());

	callbackMapBattlePassArrayReceived.Remove(guid);
}

void UScillClient::ReceiveUnlockBattlePassResponse(const ScillSDK::ScillApiBattlePassesApi::UnlockBattlePassResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassUnlockInfoReceived.FindRef(guid);

	callback.ExecuteIfBound(FBattlePassUnlockInfo::FromScillApiBattlePassUnlockInfo(Response.Content), Response.IsSuccessful());

	callbackMapBattlePassUnlockInfoReceived.Remove(guid);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Challenges Handlers
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ReceiveActivatePersonalChallengeResponse(const ScillSDK::ScillApiChallengesApi::ActivatePersonalChallengeResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeReceived.FindRef(guid);

	callback.ExecuteIfBound(FChallenge::FromScillApiChallenge(Response.Content.Challenge.Get(ScillSDK::ScillApiChallenge())), Response.IsSuccessful());

	callbackMapChallengeReceived.Remove(guid);
}

void UScillClient::ReceiveCancelPersonalChallengeResponse(const ScillSDK::ScillApiChallengesApi::CancelPersonalChallengeResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeReceived.FindRef(guid);

	callback.ExecuteIfBound(FChallenge::FromScillApiChallenge(Response.Content.Challenge.Get(ScillSDK::ScillApiChallenge())), Response.IsSuccessful());

	callbackMapChallengeReceived.Remove(guid);
}

void UScillClient::ReceiveClaimPersonalChallengeRewardResponse(const ScillSDK::ScillApiChallengesApi::ClaimPersonalChallengeRewardResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeReceived.FindRef(guid);

	callback.ExecuteIfBound(FChallenge::FromScillApiChallenge(Response.Content.Challenge.Get(ScillSDK::ScillApiChallenge())), Response.IsSuccessful());

	callbackMapChallengeReceived.Remove(guid);
}

void UScillClient::ReceiveGetActivePersonalChallengesResponse(const ScillSDK::ScillApiChallengesApi::GetActivePersonalChallengesResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeCategoryArrayReceived.FindRef(guid);

	TArray<FChallengeCategory> challengeCategories = TArray<FChallengeCategory>();

	for (auto c : Response.Content)
	{
		challengeCategories.Add(FChallengeCategory::FromScillApiChallengeCategory(c));
	}

	callback.ExecuteIfBound(challengeCategories, Response.IsSuccessful());

	callbackMapChallengeCategoryArrayReceived.Remove(guid);
}

void UScillClient::ReceiveGetAllPersonalChallengesResponse(const ScillSDK::ScillApiChallengesApi::GetAllPersonalChallengesResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeCategoryArrayReceived.FindRef(guid);

	TArray<FChallengeCategory> challengeCategories = TArray<FChallengeCategory>();

	for (auto c : Response.Content)
	{
		challengeCategories.Add(FChallengeCategory::FromScillApiChallengeCategory(c));
	}

	callback.ExecuteIfBound(challengeCategories, Response.IsSuccessful());

	callbackMapChallengeCategoryArrayReceived.Remove(guid);
}

void UScillClient::ReceiveGetPersonalChallengesResponse(const ScillSDK::ScillApiChallengesApi::GetPersonalChallengesResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeCategoryArrayReceived.FindRef(guid);

	TArray<FChallengeCategory> challengeCategories = TArray<FChallengeCategory>();

	for (auto c : Response.Content)
	{
		challengeCategories.Add(FChallengeCategory::FromScillApiChallengeCategory(c));
	}

	callback.ExecuteIfBound(challengeCategories, Response.IsSuccessful());

	callbackMapChallengeCategoryArrayReceived.Remove(guid);
}

void UScillClient::ReceiveGetUnresolvedPersonalChallengesResponse(const ScillSDK::ScillApiChallengesApi::GetUnresolvedPersonalChallengesResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeCategoryArrayReceived.FindRef(guid);

	TArray<FChallengeCategory> challengeCategories = TArray<FChallengeCategory>();

	for (auto c : Response.Content)
	{
		challengeCategories.Add(FChallengeCategory::FromScillApiChallengeCategory(c));
	}

	callback.ExecuteIfBound(challengeCategories, Response.IsSuccessful());

	callbackMapChallengeCategoryArrayReceived.Remove(guid);
}

void UScillClient::ReceiveGetPersonalChallengeByIdResponse(const ScillSDK::ScillApiChallengesApi::GetPersonalChallengeByIdResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeReceived.FindRef(guid);

	callback.ExecuteIfBound(FChallenge::FromScillApiChallenge(Response.Content), Response.IsSuccessful());

	callbackMapChallengeReceived.Remove(guid);
}

void UScillClient::ReceiveUnlockPersonalChallengeResponse(const ScillSDK::ScillApiChallengesApi::UnlockPersonalChallengeResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeReceived.FindRef(guid);

	callback.ExecuteIfBound(FChallenge::FromScillApiChallenge(Response.Content.Challenge.Get(ScillSDK::ScillApiChallenge())), Response.IsSuccessful());

	callbackMapChallengeReceived.Remove(guid);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Leaderboards Handlers
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ReceiveGetLeaderboardResponse(const ScillSDK::ScillApiLeaderboardsApi::GetLeaderboardResponse& Response, FGuid guid) const
{
	auto callback = callbackMapLeaderboardReceived.FindRef(guid);
	callback.ExecuteIfBound(FLeaderboardV2Results::FromScillApiLeaderboard(Response.Content), Response.IsSuccessful());

	callbackMapLeaderboardReceived.Remove(guid);
}

void UScillClient::ReceiveGetLeaderboardRankingResponse(const ScillSDK::ScillApiLeaderboardsApi::GetLeaderboardRankingResponse& Response, FGuid guid) const
{
	auto callback = callbackMapLeaderboardRankingReceived.FindRef(guid);
	callback.ExecuteIfBound(FLeaderboardV2MemberRanking::FromScillApiLeaderboardMemberRanking(Response.Content), Response.IsSuccessful());

	callbackMapLeaderboardRankingReceived.Remove(guid);
}

void UScillClient::ReceiveGetLeaderboardRankingsResponse(const ScillSDK::ScillApiLeaderboardsApi::GetLeaderboardRankingsResponse& Response, FGuid guid) const
{
	auto callback = callbackMapLeaderboardRankingsReceived.FindRef(guid);

	auto Result = TArray<FLeaderboardV2MemberRanking>();
	if (Response.IsSuccessful())
	{
		for(ScillSDK::ScillApiLeaderboardMemberRanking r : Response.Content)
		{
			Result.Add(FLeaderboardV2MemberRanking::FromScillApiLeaderboardMemberRanking(r));
		}
	}

	callback.ExecuteIfBound(Result, Response.IsSuccessful());

	callbackMapLeaderboardRankingsReceived.Remove(guid);
}

void UScillClient::ReceiveGetLeaderboardsResponse(const ScillSDK::ScillApiLeaderboardsApi::GetLeaderboardsResponse& Response, FGuid guid) const
{
	auto callback = callbackMapLeaderboardsReceived.FindRef(guid);

	auto Result = TArray<FLeaderboardV2Results>();
	if (Response.IsSuccessful())
	{
		for (ScillSDK::ScillApiLeaderboard r : Response.Content)
		{
			Result.Add(FLeaderboardV2Results::FromScillApiLeaderboard(r));
		}
	}

	callback.ExecuteIfBound(Result, Response.IsSuccessful());

	callbackMapLeaderboardsReceived.Remove(guid);
}

void UScillClient::ReceiveSetUserInfoResponse(const ScillSDK::ScillApiAuthApi::SetUserInfoResponse& Response, FGuid guid) const
{
	auto callback = callbackMapUserInfoReceived.FindRef(guid);
	callback.ExecuteIfBound(FUserInfo::FromScillApiUserInfo(Response.Content), Response.IsSuccessful());

	callbackMapUserInfoReceived.Remove(guid);
}

void UScillClient::ReceiveGetUserInfoResponse(const ScillSDK::ScillApiAuthApi::GetUserInfoResponse& Response, FGuid guid) const
{
	auto callback = callbackMapUserInfoReceived.FindRef(guid);
	callback.ExecuteIfBound(FUserInfo::FromScillApiUserInfo(Response.Content), Response.IsSuccessful());

	callbackMapUserInfoReceived.Remove(guid);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Leaderboards V2 Handlers
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ReceiveGetLeaderboardResponseV2(const ScillSDK::ScillApiLeaderboardsV2Api::GetLeaderboardV2Response& Response, FGuid guid) const
{
	auto callback = callbackMapLeaderboardReceived.FindRef(guid);
	callback.ExecuteIfBound(FLeaderboardV2Results::FromScillApiLeaderboardV2Results(Response.Content), Response.IsSuccessful());

	callbackMapLeaderboardReceived.Remove(guid);
}

void UScillClient::ReceiveGetLeaderboardRankingResponseV2(const ScillSDK::ScillApiLeaderboardsV2Api::GetLeaderboardV2RankingResponse& Response, FGuid guid) const
{
	auto callback = callbackMapLeaderboardRankingReceived.FindRef(guid);
	callback.ExecuteIfBound(FLeaderboardV2MemberRanking::FromScillApiLeaderboardV2MemberRanking(Response.Content), Response.IsSuccessful());

	callbackMapLeaderboardRankingReceived.Remove(guid);
}

void UScillClient::ReceiveGetLeaderboardRankingsResponseV2(const ScillSDK::ScillApiLeaderboardsV2Api::GetLeaderboardV2RankingsResponse& Response, FGuid guid) const
{
	auto callback = callbackMapLeaderboardRankingsReceived.FindRef(guid);

	auto Result = TArray<FLeaderboardV2MemberRanking>();
	if (Response.IsSuccessful())
	{
		for (ScillSDK::ScillApiLeaderboardV2MemberRanking r : Response.Content)
		{
			Result.Add(FLeaderboardV2MemberRanking::FromScillApiLeaderboardV2MemberRanking(r));
		}
	}

	callback.ExecuteIfBound(Result, Response.IsSuccessful());

	callbackMapLeaderboardRankingsReceived.Remove(guid);
}

void UScillClient::ReceiveGetLeaderboardsResponseV2(const ScillSDK::ScillApiLeaderboardsV2Api::GetLeaderboardsV2Response& Response, FGuid guid) const
{
	auto callback = callbackMapLeaderboardsReceived.FindRef(guid);

	auto Result = TArray<FLeaderboardV2Results>();
	if (Response.IsSuccessful())
	{
		for (ScillSDK::ScillApiLeaderboardV2Results r : Response.Content)
		{
			Result.Add(FLeaderboardV2Results::FromScillApiLeaderboardV2Results(r));
		}
	}

	callback.ExecuteIfBound(Result, Response.IsSuccessful());

	callbackMapLeaderboardRankingsReceived.Remove(guid);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Events Handlers
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ReceiveSendEventResponse(const ScillSDK::ScillApiEventsApi::SendEventResponse& Response, FGuid guid) const
{
	auto callback = callbackMapResponseReceived.FindRef(guid);
	callback.ExecuteIfBound(Response.IsSuccessful());

	callbackMapResponseReceived.Remove(guid);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Realtime Updates Handlers
// ----------------------------------------------------------------------------------------------------------------------------

void UScillClient::ReceiveBattlePassChangeTopic(const ScillSDK::ScillApiAuthApi::GetUserBattlePassNotificationTopicResponse& Response, FGuid guid) const
{
	auto callback = callbackMapBattlePassChangeReceived.FindRef(guid);

	mqtt->SubscribeToTopicBP(Response.Content.Topic, callback);

	callbackMapResponseReceived.Remove(guid);
}

void UScillClient::ReceiveChallengeChangeTopic(const ScillSDK::ScillApiAuthApi::GetUserChallengesNotificationTopicResponse& Response, FGuid guid) const
{
	auto callback = callbackMapChallengeChangeReceived.FindRef(guid);

	mqtt->SubscribeToTopicC(Response.Content.Topic, callback);

	callbackMapResponseReceived.Remove(guid);
}

void UScillClient::ReceiveLeaderboardChangeTopic(const ScillSDK::ScillApiAuthApi::GetLeaderboardNotificationTopicResponse& Response, FGuid guid) const
{
	auto callback = callbackMapLeaderboardChangeReceived.FindRef(guid);

	mqtt->SubscribeToTopicL(Response.Content.Topic, callback);

	callbackMapResponseReceived.Remove(guid);
}

// Called every frame
void UScillClient::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

