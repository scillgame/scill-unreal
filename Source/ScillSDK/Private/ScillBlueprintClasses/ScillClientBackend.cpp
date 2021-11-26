#include "ScillBlueprintClasses/ScillClientBackend.h"
#include "JsonObjectConverter.h"

UScillClientBackend::UScillClientBackend()
	: RealtimeUpdatesWebsocketURL(TEXT("wss://mqtt.scillgame.com:8083/mqtt"))
{
	mqtt = NewObject<UScillMqtt>();
}

void UScillClientBackend::SetApiKey(FString apiKey)
{
	this->authApi.AddHeaderParam("Authorization", "Bearer " + apiKey);
	this->ApiKey = apiKey;
	this->eventsApi.AddHeaderParam("Authorization", "Bearer " + this->ApiKey);
	this->leaderboardsApi.AddHeaderParam("Authorization", "Bearer " + this->ApiKey);
	//UE_LOG(LogScillSDK, Log, TEXT("API Key Created: %s"), *apiKey);
}

void UScillClientBackend::GenerateAccessToken(FString userId, const FReceiveAccessToken& OnAccessTokenGenerated)
{
	auto accessTokenRequest = ScillSDK::ScillApiAuthApi::GenerateAccessTokenRequest();

	accessTokenRequest.ScillApiForeignUserIdentifier = ScillSDK::ScillApiForeignUserIdentifier();
	accessTokenRequest.ScillApiForeignUserIdentifier.UserId = userId;

	FGuid guid = FGuid::NewGuid();

	callbackMapReceiveAccessToken.Add(guid, OnAccessTokenGenerated);

	auto generateAccessTokenDelegate = ScillSDK::ScillApiAuthApi::FGenerateAccessTokenDelegate::CreateUObject(this, &UScillClientBackend::ReceiveAccessTokenResponse, guid);

	authApi.GenerateAccessToken(accessTokenRequest, generateAccessTokenDelegate);
}

//void UScillClientBackend::StartMonitorBattlePassUpdates(FString accessToken, FString battlePassId, const FReceiveBattlePassUpdate& callback)
//{
//	auto getBattlePassUpdatesTopicRequest = ScillSDK::ScillApiAuthApi::GetUserBattlePassNotificationTopicRequest();
//
//	getBattlePassUpdatesTopicRequest.BattlePassId = battlePassId;
//
//	FGuid guid = FGuid::NewGuid();
//
//	callbackMapReceiveBattlepassTopic.Add(guid, callback);
//	
//	auto getBattlePassUpdatesTopicDelegate = ScillSDK::ScillApiAuthApi::FGetUserBattlePassNotificationTopicDelegate::CreateUObject(this, &UScillClientBackend::ReceiveBattlepassTopic, guid);
//	
//	auto tempAuthApi = ScillSDK::ScillApiAuthApi();
//	tempAuthApi.AddHeaderParam("Authorization", "Bearer " + accessToken);
//
//	tempAuthApi.GetUserBattlePassNotificationTopic(getBattlePassUpdatesTopicRequest, getBattlePassUpdatesTopicDelegate);
//}

void UScillClientBackend::BeginPlay()
{
	Super::BeginPlay();

	this->authApi.AddHeaderParam("Authorization", "Bearer " + this->ApiKey);
	this->authApi.SetURL(TEXT("https://us.scillgame.com"));

	this->eventsApi.AddHeaderParam("Authorization", "Bearer " + this->ApiKey);
	this->eventsApi.SetURL(TEXT("https://ep.scillgame.com"));

	//UE_LOG(LogScillSDK, Log, TEXT("API Key Created: %s"), *this->ApiKey);
}

void UScillClientBackend::ReceiveAccessTokenResponse(const ScillSDK::ScillApiAuthApi::GenerateAccessTokenResponse& Response, FGuid guid) const
{
	bool isSuccessful = Response.IsSuccessful();
	FString token = isSuccessful ? Response.Content.Token.GetValue() : "";

	auto callback = callbackMapReceiveAccessToken.FindRef(guid);
	callback.ExecuteIfBound(token, isSuccessful);

	callbackMapReceiveAccessToken.Remove(guid);
}

void UScillClientBackend::ReceiveBattlepassTopic(const ScillSDK::ScillApiAuthApi::GetUserBattlePassNotificationTopicResponse& Response, FGuid guid) const
{
	if (Response.IsSuccessful())
	{
		FString topic = Response.Content.Topic;

		const FString ServerProtocol = TEXT("ws");

		auto websocket = FWebSocketsModule::Get().CreateWebSocket(RealtimeUpdatesWebsocketURL, ServerProtocol);

		websocket->OnConnected().AddLambda([]() -> void {
			
			});

		websocket->OnMessage().AddUObject(this, &UScillClientBackend::ReceiveStringMessageFromBattlepassTopic, guid);

		websocket->Connect();
	}
}

void UScillClientBackend::ReceiveStringMessageFromBattlepassTopic(const FString& Message, FGuid guid) const
{
	//auto battlePass = ScillSDK::ScillApiBattlePass().FromJson();
	auto JsonReader = TJsonReaderFactory<TCHAR>::Create(Message);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		auto callback = callbackMapReceiveBattlepassTopic.FindRef(guid);

		TSharedPtr<FJsonValueObject> ValueObject = MakeShareable(new FJsonValueObject(JsonObject));

		auto battlePass = ScillSDK::ScillApiBattlePass();
		battlePass.FromJson(ValueObject);

		callback.ExecuteIfBound(FBattlePass::FromScillApiBattlePass(battlePass));
	}
}

void UScillClientBackend::SendEvent(FScillEventPayload payload, FResponseReceived responseReceived)
{
	auto request = ScillSDK::ScillApiEventsApi::SendEventRequest();

	request.ScillApiEventPayload = FScillEventPayload::ToScillApiEventPayload(payload);

	FGuid guid = FGuid::NewGuid();

	callbackMapResponseReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiEventsApi::FSendEventDelegate::CreateUObject(this, &UScillClientBackend::ReceiveSendEventResponse, guid);

	eventsApi.SendEvent(request, delegate);
}

void UScillClientBackend::ReceiveSendEventResponse(const ScillSDK::ScillApiEventsApi::SendEventResponse& Response, FGuid guid) const
{
	auto callback = callbackMapResponseReceived.FindRef(guid);
	callback.ExecuteIfBound(Response.IsSuccessful());

	callbackMapResponseReceived.Remove(guid);
}

void UScillClientBackend::ResetLeaderboardRankingsV2(FString ApplicationId, FString LeaderboardId, FResponseReceived responseReceived)
{
	auto request = ScillSDK::ScillApiLeaderboardsV2Api::ResetLeaderboardV2RankingsRequest();

	request.AppId = ApplicationId;
	request.LeaderboardId = LeaderboardId;

	FGuid guid = FGuid::NewGuid();

	callbackMapResponseReceived.Add(guid, responseReceived);

	auto delegate = ScillSDK::ScillApiLeaderboardsV2Api::FResetLeaderboardV2RankingsDelegate::CreateUObject(this, &UScillClientBackend::ReceiveResetLeaderboardRankingsResponseV2, guid);

	leaderboardsApi.ResetLeaderboardV2Rankings(request, delegate);
}

void UScillClientBackend::ReceiveResetLeaderboardRankingsResponseV2(const ScillSDK::ScillApiLeaderboardsV2Api::ResetLeaderboardV2RankingsResponse& Response, FGuid guid) const
{
	auto callback = callbackMapResponseReceived.FindRef(guid);

	callback.ExecuteIfBound(Response.IsSuccessful());

	callbackMapResponseReceived.Remove(guid);
}
