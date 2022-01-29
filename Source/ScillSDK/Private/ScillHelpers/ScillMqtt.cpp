// Fill out your copyright notice in the Description page of Project Settings.


#include "ScillHelpers/ScillMqtt.h"

UScillMqtt::UScillMqtt()
{
	callbacksBattlePassChanges.Empty();

	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}

	mqttWs = FWebSocketsModule::Get().CreateWebSocket(TEXT("wss://mqtt.scillgame.com:8083/mqtt"), TEXT("mqtt"));

	mqttWs->OnConnected().AddUObject(this, &UScillMqtt::OnConnect);
	mqttWs->OnConnectionError().AddUObject(this, &UScillMqtt::OnConnectionError);

	mqttWs->OnRawMessage().AddUObject(this, &UScillMqtt::OnRawMessage);

	mqttWs->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean) -> void {
		UE_LOG(LogTemp, Error, TEXT("MQTT Connection was closed. Status Code %d: %s"), StatusCode, *Reason);
		});

	mqttWs->Connect();
}

void UScillMqtt::Destroy()
{
	Destroyed = true;
	if (mqttWs && mqttWs->IsConnected())
	{
		if (MqttConnected)
		{
			this->Disconnect();
		}
		mqttWs->Close();
	}
}

void UScillMqtt::OnRawMessage(const void* data, SIZE_T Size, SIZE_T BytesRemaining)
{
	uint8* buffer = (uint8*)data;
	TArray<uint8> receivedMessage;
	receivedMessage.AddDefaulted(Size);

	for (int i = 0; i < Size; i++)
	{
		receivedMessage[i] = buffer[i];
	}

	UScillMqttPacketBase* packet = UScillMqttPacketBase::FromBuffer(receivedMessage);

	if (packet->PacketType == ScillMqttPacketType::CONNACK)
	{
		this->MqttConnected = true;
		this->MqttConnectionEstablishedDelegate.Broadcast();
	}
	if (packet->PacketType == ScillMqttPacketType::PUBLISH)
	{

		UScillMqttPacketPublish* pubPacket = Cast<UScillMqttPacketPublish>(packet);

		auto JsonReader = TJsonReaderFactory<TCHAR>::Create(pubPacket->Payload);

		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
		{
			TSharedPtr<FJsonValueObject> ValueObject = MakeShareable(new FJsonValueObject(JsonObject));

			if (callbacksBattlePassChanges.Contains(pubPacket->TopicName))
			{
				FString webhookType = JsonObject->GetStringField("webhook_type");

				auto callback = this->callbacksBattlePassChanges.FindRef(pubPacket->TopicName);

				// Battle Pass Challenge Changed
				if (webhookType == TEXT("battlepass-challenge-changed"))
				{
					auto battlePass = ScillSDK::ScillApiBattlePassChallengeChangedPayload();
					battlePass.FromJson(ValueObject);

					callback.ExecuteIfBound(BattlePassPayloadType::ChallengeChanged, FBattlePassChanged::FromScillApiBattlePassChallengeChangedPayload(battlePass), FBattlePassLevelClaimed(), FBattlePassExpired());
				}
				// Battle Pass Reward Claimed
				if (webhookType == TEXT("battlepass-level-reward-claimed"))
				{
					auto battlePassRewardClaimed = ScillSDK::ScillApiBattlePassLevelClaimedPayload();
					battlePassRewardClaimed.FromJson(ValueObject);

					callback.ExecuteIfBound(BattlePassPayloadType::RewardClaimed, FBattlePassChanged(), FBattlePassLevelClaimed::FromScillApiBattlePassLevelClaimedPayload(battlePassRewardClaimed), FBattlePassExpired());
				}
				// Battle Pass Expired
				if (webhookType == TEXT("battlepass-expired"))
				{
					auto battlePassExpired = ScillSDK::ScillApiBattlePassExpiredPayload();
					battlePassExpired.FromJson(ValueObject);

					callback.ExecuteIfBound(BattlePassPayloadType::Expired, FBattlePassChanged(), FBattlePassLevelClaimed(), FBattlePassExpired::FromScillApiBattlePassExpiredPayload(battlePassExpired));
				}
			}
			if (callbacksChallengeChanges.Contains(pubPacket->TopicName))
			{
				auto callback = this->callbacksChallengeChanges.FindRef(pubPacket->TopicName);

				auto challenge = ScillSDK::ScillApiChallengeWebhookPayload();
				challenge.FromJson(ValueObject);

				callback.ExecuteIfBound(FChallengeChanged::FromScillApiChallengeWebhookPayload(challenge));
			}
			if (callbacksLeaderboardChanges.Contains(pubPacket->TopicName))
			{
				FString webhookType = JsonObject->GetStringField("webhook_type");

				auto callback = this->callbacksLeaderboardChanges.FindRef(pubPacket->TopicName);
				if (webhookType == TEXT("leaderboard-ranking-changed"))
				{
					if (leaderboardVersion == 2)
					{
						auto leaderboardUpdate = ScillSDK::ScillApiLeaderboardV2UpdatePayload();
						leaderboardUpdate.FromJson(ValueObject);

						callback.ExecuteIfBound(FLeaderboardV2UpdatePayload::FromScillApiLeaderboardV2UpdatePayload(leaderboardUpdate), FLeaderboardV2Changed());
					}
					else
					{
						auto leaderboardUpdate = ScillSDK::ScillApiLeaderboardUpdatePayload();
						leaderboardUpdate.FromJson(ValueObject);

						callback.ExecuteIfBound(FLeaderboardV2UpdatePayload::FromScillApiLeaderboardUpdatePayload(leaderboardUpdate), FLeaderboardV2Changed());
					}
				}
				if (webhookType == TEXT("leaderboard-changed"))
				{
					auto leaderboardUpdate = ScillSDK::ScillApiLeaderboardV2Changed();
					leaderboardUpdate.FromJson(ValueObject);

					callback.ExecuteIfBound(FLeaderboardV2UpdatePayload(), FLeaderboardV2Changed::FromScillApiLeaderboardV2Changed(leaderboardUpdate));
				}
			}
		}
	}

	return;
}

void UScillMqtt::SubscribeToTopic(FString Topic)
{
	UScillMqttPacketSubscribe* pk = NewObject<UScillMqttPacketSubscribe>();

	pk->PacketIdentifier = ++(this->CurrentPacketIdentifier);

	pk->TopicFilter.Add(Topic);
	pk->RequestedQoS.Add(0);


	pk->Buffer = pk->ToBuffer();
	uint8* pkBuffer = new uint8[pk->Buffer.Num()];

	for (int i = 0; i < pk->Buffer.Num(); i++)
	{
		pkBuffer[i] = pk->Buffer[i];
	}

	mqttWs->Send(pkBuffer, pk->Length, true);

	delete[] pkBuffer;
}

void UScillMqtt::SubscribeToTopicBP(FString Topic, FBattlePassChangeReceived callback)
{
	callbacksBattlePassChanges.Add(Topic, callback);

	this->SubscribeToTopic(Topic);
}

void UScillMqtt::SubscribeToTopicC(FString Topic, FChallengeChangeReceived callback)
{
	callbacksChallengeChanges.Add(Topic, callback);

	this->SubscribeToTopic(Topic);
}

void UScillMqtt::SubscribeToTopicL(FString Topic, FLeaderboardChangeReceived callback)
{
	callbacksLeaderboardChanges.Add(Topic, callback);

	this->SubscribeToTopic(Topic);
}

void UScillMqtt::OnConnectionError(const FString& Error)
{
	UE_LOG(LogTemp, Error, TEXT("Could not establish connection to MQTT Server: %s"), *Error);
	return;
}

void UScillMqtt::OnConnect()
{
	UScillMqttPacketConnect* pk = NewObject<UScillMqttPacketConnect>();

	pk->KeepAlive = 300;
	pk->WillRetain = false;
	pk->WillQoS = 0;
	pk->CleanSession = 1;

	pk->Buffer = pk->ToBuffer();
	uint8* buffer = new uint8[pk->Buffer.Num()];
	for (int i = 0; i < pk->Buffer.Num(); i++)
	{
		buffer[i] = pk->Buffer[i];
	}

	mqttWs->Send(buffer, pk->Length, true);

	delete buffer;
}

void UScillMqtt::Ping()
{
	UScillMqttPacketPing* pk = NewObject<UScillMqttPacketPing>();
	pk->Buffer = pk->ToBuffer();
	uint8* buffer = new uint8[pk->Buffer.Num()];
	for (int i = 0; i < pk->Buffer.Num(); i++)
	{
		buffer[i] = pk->Buffer[i];
	}

	this->mqttWs->Send(buffer, pk->Length, true);

	delete[] buffer;
}

void UScillMqtt::Disconnect()
{
	UScillMqttPacketDisconnect* pk = NewObject<UScillMqttPacketDisconnect>();
	pk->Buffer = pk->ToBuffer();
	uint8* buffer = new uint8[pk->Buffer.Num()];
	for (int i = 0; i < pk->Buffer.Num(); i++)
	{
		buffer[i] = pk->Buffer[i];
	}

	this->mqttWs->Send(buffer, pk->Length, true);

	delete[] buffer;
}

TArray<uint8> UScillMqttPacketConnect::ToBuffer()
{
	//calculate length of packet
	uint64 length, varlength;

	// fixed header without RemainingLength
	length = 1;
	// protocol name length specs + protocol level + connect flags + keep alive - basically everything after remaining length
	varlength = 2 + 1 + 1 + 2;

	// connect payload
	varlength += this->ProtocolName.Len();
	varlength += ClientId.Len() + 2;
	varlength += this->WillTopic.IsSet() ? this->WillTopic.GetValue().Len() + 2 : 0;
	varlength += this->WillMessage.IsSet() ? this->WillMessage.GetValue().Len() + 2 : 0;
	varlength += this->UserName.IsSet() ? this->UserName.GetValue().Len() + 2 : 0;
	varlength += this->Password.IsSet() ? this->Password.GetValue().Len() + 2 : 0;

	if (varlength > 268435455) return TArray<uint8>();

	// add bytes for remaining length
	length += varlength < 128 ? 1 : varlength < 16384 ? 2 : varlength < 2097152 ? 3 : 4;

	// allocate array
	this->Length = length + varlength;
	this->RemainLength = varlength;
	TArray<uint8> buffer;
	buffer.AddDefaulted(this->Length);

	// write to buffer
	uint64 pointer = 0;

	// Packet Type and Flags
	buffer[pointer++] = ScillMqttPacketType::CONNECT << 4;
	this->PacketType = ScillMqttPacketType::CONNECT;

	// Remaining Length
	uint64 x = varlength;
	do {
		buffer[pointer] = x % 128;
		x = x / 128;
		if (x > 0)
			buffer[pointer] += 128;
		pointer++;
	} while (x > 0);

	// Connect Variable Header

	// Protocol Name
	buffer[pointer++] = this->ProtocolName.Len() / 256; //MSB
	buffer[pointer++] = this->ProtocolName.Len() % 256; //LSB

	int32 pnLen = StringHelper::StringToTArray(this->ProtocolName, buffer, this->ProtocolName.Len(), pointer);
	pointer += pnLen;

	// Protocol Level, version 3.1.1
	buffer[pointer++] = 4;

	// Connect Flags
	this->SetConnectFlags();
	buffer[pointer++] = this->ConnectFlags;

	// Keep Alive
	buffer[pointer++] = this->KeepAlive / 256; //MSB
	buffer[pointer++] = this->KeepAlive % 256; //LSB

	// Payload

	// Client Identifier
	buffer[pointer++] = this->ClientId.Len() / 256; //MSB
	buffer[pointer++] = this->ClientId.Len() % 256; //LSB
	int32 cIdLen = StringHelper::StringToTArray(this->ClientId, buffer, this->ClientId.Len(), pointer);
	pointer += cIdLen;

	// Will Topic
	if (this->ConnectFlags & ScillMqttConnectFlags::WILL)
	{
		buffer[pointer++] = this->WillTopic.Get("").Len() / 256; //MSB
		buffer[pointer++] = this->WillTopic.Get("").Len() % 256; //LSB

		int32 wtLen = StringHelper::StringToTArray(this->WillTopic.Get(""), buffer, this->WillTopic.Get("").Len(), pointer);
		pointer += wtLen;
	}

	// Will Message
	if (this->ConnectFlags & ScillMqttConnectFlags::WILL)
	{
		buffer[pointer++] = this->WillMessage.Get("").Len() / 256; //MSB
		buffer[pointer++] = this->WillMessage.Get("").Len() % 256; //LSB

		int32 wmLen = StringHelper::StringToTArray(this->WillMessage.Get(""), buffer, this->WillMessage.Get("").Len(), pointer);
		pointer += wmLen;
	}

	// User Name
	if (this->ConnectFlags & ScillMqttConnectFlags::USER_NAME)
	{
		buffer[pointer++] = this->UserName.Get("").Len() / 256; //MSB
		buffer[pointer++] = this->UserName.Get("").Len() % 256; //LSB

		int32 unLen = StringHelper::StringToTArray(this->UserName.Get(""), buffer, this->UserName.Get("").Len(), pointer);
		pointer += unLen;
	}

	// Password
	if (this->ConnectFlags & ScillMqttConnectFlags::PASSWORD)
	{
		buffer[pointer++] = this->Password.Get("").Len() / 256; //MSB
		buffer[pointer++] = this->Password.Get("").Len() % 256; //LSB

		int32 pwLen = StringHelper::StringToTArray(this->Password.Get(""), buffer, this->Password.Get("").Len(), pointer);
		pointer += pwLen;
	}

	return buffer;
}


void UScillMqttPacketConnect::SetConnectFlags() {
	this->ConnectFlags = this->UserName.IsSet() ? ScillMqttConnectFlags::USER_NAME : 0;
	this->ConnectFlags += this->Password.IsSet() && this->UserName.IsSet() ? ScillMqttConnectFlags::PASSWORD : 0;
	this->ConnectFlags += this->WillRetain && this->WillMessage.IsSet() && this->WillTopic.IsSet() ? ScillMqttConnectFlags::WILL_RETAIN : 0;
	this->ConnectFlags += this->WillMessage.IsSet() && this->WillTopic.IsSet() ? this->WillQoS % 4 << 3 : 0;
	this->ConnectFlags += this->WillMessage.IsSet() && this->WillTopic.IsSet() ? ScillMqttConnectFlags::WILL : 0;
	this->ConnectFlags += this->CleanSession ? ScillMqttConnectFlags::CLEAN_SESSION : 0;
}

TArray<uint8> UScillMqttPacketBase::ToBuffer()
{
	TArray<uint8> result;
	result.AddDefaulted(0);
	return result;
}

UScillMqttPacketConnack* UScillMqttPacketConnack::FromBuffer(TArray<uint8> buffer)
{
	UScillMqttPacketConnack* pk = NewObject<UScillMqttPacketConnack>();

	uint64 pointer = 0;

	// Packet Type
	uint8 firstByte = buffer[pointer++];
	pk->PacketType = (ScillMqttPacketType)((firstByte & 0xf0) >> 4);

	// Skip Remaining Length, since it is always "2"
	pointer++;

	// Session Present
	pk->SessionPresent = (bool)buffer[pointer++];

	// Connection Response Code
	pk->Code = (ScillMqttConnackCode)buffer[pointer++];

	return pk;
}

ScillMqttPacketType UScillMqttPacketBase::GetPacketTypeFromBuffer(TArray<uint8> buffer)
{
	uint8 firstByte = buffer[0];
	return (ScillMqttPacketType)((firstByte & 0xf0) >> 4);
}

UScillMqttPacketBase* UScillMqttPacketBase::FromBuffer(TArray<uint8> buffer)
{
	auto messageType = UScillMqttPacketBase::GetPacketTypeFromBuffer(buffer);

	if (messageType == ScillMqttPacketType::CONNECT)
	{
		UE_LOG(LogTemp, Error, TEXT("Unexpected MQTT packet received: CONNECT"));
		UScillMqttPacketConnect* pk = NewObject<UScillMqttPacketConnect>();
		return pk;
	}
	if (messageType == ScillMqttPacketType::CONNACK)
	{
		return UScillMqttPacketConnack::FromBuffer(buffer);
	}
	if (messageType == ScillMqttPacketType::PUBLISH)
	{
		return UScillMqttPacketPublish::FromBuffer(buffer);
	}
	if (messageType == ScillMqttPacketType::PINGRESP)
	{
		return UScillMqttPacketPingResp::FromBuffer(buffer);
	}

	UScillMqttPacketBase* pk = NewObject<UScillMqttPacketBase>();
	return pk;
}

uint64 UScillMqttPacketBase::GetRemainingLengthFromBuffer(TArray<uint8> buffer)
{
	uint8 pointer = 1;

	uint32 multiplier = 1;
	uint64 length = 0;
	uint8 current = 0;

	do
	{
		current = buffer[pointer++];
		length += (current & 127) * multiplier;
		multiplier *= 128;
		if (multiplier > 128 * 128 * 128)
			UE_LOG(LogTemp, Error, TEXT("Error decoding MQTT message: Malformed Remaining Length."));
	} while ((current & 128) != 0);

	return length;
}

UScillMqttPacketPublish* UScillMqttPacketPublish::FromBuffer(TArray<uint8> buffer)
{
	UScillMqttPacketPublish* pk = NewObject<UScillMqttPacketPublish>();

	uint64 pointer = 0;

	// Packet Type
	uint8 firstByte = buffer[pointer++];
	pk->PacketType = (ScillMqttPacketType)((firstByte & 0xf0) >> 4);

	// Packet Flags
	pk->PacketFlags = firstByte & 0x0f;

	// Set Fields according to Packet Flags
	pk->Duplicate = (bool)(pk->PacketFlags & 0x01);
	pk->QoS = (uint8)((pk->PacketFlags & 0x06) >> 1);
	pk->Retain = (bool)(pk->PacketFlags & 0x08);

	// Remain Length
	pk->RemainLength = UScillMqttPacketBase::GetRemainingLengthFromBuffer(buffer);
	pk->Length = UScillMqttPacketBase::CalculateLengthFromRemaining(pk->RemainLength);
	pointer += UScillMqttPacketBase::FixedHeaderLengthFromRemaining(pk->RemainLength) - 1;

	// Topic Name
	uint16 tpLength = buffer[pointer++] * 256;
	tpLength += buffer[pointer++]; // MSB + LSB
	pk->TopicName = StringHelper::TArrayToString(buffer, pointer, tpLength);
	pointer += tpLength;

	// Packet Identifier
	if (pk->QoS)
	{
		pk->PacketIdentifier = buffer[pointer++] * 256;
		pk->PacketIdentifier += buffer[pointer++];
	}

	// Payload
	uint64 plLength = pk->Length - pointer;
	pk->Payload = StringHelper::TArrayToString(buffer, pointer, plLength);

	return pk;
}

TArray<uint8> UScillMqttPacketSubscribe::ToBuffer()
{
	//calculate length of packet
	uint64 varlength;

	// Packet Identifier in Variable Header
	varlength = 2;

	// Add Topic Filter Lengths
	for (int i = 0; i < this->TopicFilter.Num(); i++)
	{
		if (i > this->RequestedQoS.Num())
			break;
		// Topic Filter Length Bytes + Topic Filter Length + Requested QoS Length
		varlength += this->TopicFilter[i].Len() + 2 + 1;
	}
	// Set Remaining Length
	this->RemainLength = varlength;

	// Set Overall Length
	this->Length = UScillMqttPacketBase::CalculateLengthFromRemaining(this->RemainLength);

	// Write buffer
	TArray<uint8> buffer;
	buffer.AddDefaulted(this->Length);
	uint64 pointer = 0;

	// Packet Type and Flags
	buffer[pointer++] = (ScillMqttPacketType::SUBSCRIBE << 4) + 2;
	this->PacketType = ScillMqttPacketType::SUBSCRIBE;

	// Remaining Length
	uint64 x = varlength;
	do {
		buffer[pointer] = x % 128;
		x = x / 128;
		if (x > 0)
			buffer[pointer] += 128;
		pointer++;
	} while (x > 0);

	// Subscribe Variable Header
	buffer[pointer++] = this->PacketIdentifier / 256; //MSB
	buffer[pointer++] = this->PacketIdentifier % 256; //LSB

	// Subscribe Payload

	// Topic Filters and their respective QoS
	for (int i = 0; i < this->TopicFilter.Num(); i++)
	{
		if (i > this->RequestedQoS.Num())
			break;

		// Length of Topic Filter
		uint16 tfLength = this->TopicFilter[i].Len();
		buffer[pointer++] = tfLength / 256; //MSB
		buffer[pointer++] = tfLength % 256; //LSB

		// Topic Filter
		StringHelper::StringToTArray(this->TopicFilter[i], buffer, tfLength, pointer);
		pointer += tfLength;

		buffer[pointer++] = this->RequestedQoS[i];
	}

	return buffer;
}

TArray<uint8> UScillMqttPacketPing::ToBuffer()
{
	this->Length = 2;
	this->RemainLength = 0;

	TArray<uint8> buffer;
	buffer.AddDefaulted(2);

	// Packet Type and Flags
	buffer[0] = ScillMqttPacketType::PINGREQ * 16;

	// Remaining Length
	buffer[1] = 0;

	return buffer;
}

UScillMqttPacketPingResp* UScillMqttPacketPingResp::FromBuffer(TArray<uint8> buffer)
{
	UScillMqttPacketPingResp* pk = NewObject<UScillMqttPacketPingResp>();

	// Packet Type
	uint8 firstByte = buffer[0];
	pk->PacketType = (ScillMqttPacketType)((firstByte & 0xf0) >> 4);

	// Packet Length
	pk->Length = 2;

	return pk;
}

TArray<uint8> UScillMqttPacketDisconnect::ToBuffer()
{
	this->Length = 2;
	this->RemainLength = 0;

	TArray<uint8> buffer;
	buffer.AddDefaulted(2);

	// Packet Type and Flags
	buffer[0] = ScillMqttPacketType::DISCONNECT * 16;

	// Remaining Length
	buffer[1] = 0;

	return buffer;
}

uint64 UScillMqttPacketBase::CalculateLengthFromRemaining(uint64 remainingLength)
{
	return remainingLength + (remainingLength < 128 ? 2 : remainingLength < 16384 ? 3 : 4);
}

uint8 UScillMqttPacketBase::FixedHeaderLengthFromRemaining(uint64 remainingLength)
{
	return remainingLength < 128 ? 2 : remainingLength < 16384 ? 3 : 4;
}