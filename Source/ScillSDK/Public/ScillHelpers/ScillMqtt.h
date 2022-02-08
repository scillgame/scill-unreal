// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WebSocketsModule.h"
#include "IWebSocket.h"
#include "ScillBlueprintClasses/ScillStructs.h"
#include "ScillMqtt.generated.h"

/* Webhook type of your Battle Pass Update.
*/
UENUM(meta = (DisplayName="Battle Pass Payload Type"))
enum BattlePassPayloadType
{
	ChallengeChanged = 0,
	RewardClaimed = 1,
	Expired = 2
};

DECLARE_DYNAMIC_DELEGATE_FourParams(FBattlePassChangeReceived, BattlePassPayloadType, Type, FBattlePassChanged, BattlePassChanged, FBattlePassLevelClaimed, BattlePassLevelClaimed, FBattlePassExpired, BattlePassExpired);
DECLARE_DYNAMIC_DELEGATE_OneParam(FChallengeChangeReceived, FChallengeChanged, Payload);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FLeaderboardChangeReceived, FLeaderboardV2UpdatePayload, UpdatePayload, FLeaderboardV2Changed, ChangedPayload);
DECLARE_MULTICAST_DELEGATE(FMqttConnectionEstablished);

/**
	*
	*/
UCLASS()
class UScillMqtt : public UObject
{
public:
	GENERATED_BODY()

	UScillMqtt();

	void SubscribeToTopicBP(FString Topic, FBattlePassChangeReceived callback);
	void SubscribeToTopicC(FString Topic, FChallengeChangeReceived callback);
	void SubscribeToTopicL(FString Topic, FLeaderboardChangeReceived callback);
	void SubscribeToTopic(FString Topic);

	bool MqttConnected;
	bool Destroyed = false;
	void Ping();
	void Destroy();

	FMqttConnectionEstablished MqttConnectionEstablishedDelegate;

	int leaderboardVersion = 2;
private:
	void OnConnect();
	void OnConnectionError(const FString& Error);
	void OnRawMessage(const void* data, SIZE_T Size, SIZE_T BytesRemaining);
	void Disconnect();

	/*Key: Topic, Value: Callback*/
	mutable TMap<FString, FBattlePassChangeReceived> callbacksBattlePassChanges;
	mutable TMap<FString, FChallengeChangeReceived> callbacksChallengeChanges;
	mutable TMap<FString, FLeaderboardChangeReceived> callbacksLeaderboardChanges;

	uint16 CurrentPacketIdentifier = 0;


	TSharedPtr<IWebSocket> mqttWs;
};

enum ScillMqttPacketType {
	CONNECT = 1,
	CONNACK = 2,
	PUBLISH = 3,
	PUBACK = 4,
	PUBREC = 5,
	PUBREL = 6,
	PUBCOMP = 7,
	SUBSCRIBE = 8,
	SUBACK = 9,
	UNSUBSCRIBE = 10,
	UNSUBACK = 11,
	PINGREQ = 12,
	PINGRESP = 13,
	DISCONNECT = 14
};

enum ScillMqttPacketFlags {
	RETAIN = 1,
	QOS = 6,
	DUP = 8
};

enum ScillMqttConnectFlags {
	CLEAN_SESSION = 2,
	WILL = 4,
	WILL_QOS = 24,
	WILL_RETAIN = 32,
	PASSWORD = 64,
	USER_NAME = 128
};

UCLASS()
class UScillMqttPacketBase : public UObject
{
	GENERATED_BODY()
public:
	virtual TArray<uint8> ToBuffer();
	static UScillMqttPacketBase* FromBuffer(TArray<uint8> buffer);
	static ScillMqttPacketType GetPacketTypeFromBuffer(TArray<uint8> buffer);
	static uint64 GetRemainingLengthFromBuffer(TArray<uint8> buffer);
	static uint64 CalculateLengthFromRemaining(uint64 remainingLength);
	static uint8 FixedHeaderLengthFromRemaining(uint64 remainingLength);

	ScillMqttPacketType PacketType;
	uint8 PacketFlags;
	uint64 RemainLength;
	TArray<uint8> Buffer;
	uint64 Length;
};

UCLASS()
class UScillMqttPacketConnect : public UScillMqttPacketBase
{
	GENERATED_BODY()
public:
	TArray<uint8> ToBuffer() override;
	void SetConnectFlags();

	FString ProtocolName = TEXT("MQTT");
	uint8 ProtocolLevel = 4;
	uint8 ConnectFlags;
	uint16 KeepAlive;
	bool WillRetain;
	uint8 WillQoS;
	bool CleanSession;
	FString ClientId;
	TOptional<FString> WillTopic;
	TOptional<FString> WillMessage;
	TOptional<FString> UserName;
	TOptional<FString> Password;
};

enum ScillMqttConnackCode
{
	ACCEPTED = 0,				// Connection Accepted
	REFUSED_VERSION = 1,		// Connection Refused, unacceptable protocol version						// The Server does not support the level of the MQTT protocol requested by the Client
	REFUSED_ID = 2,				// Connection Refused, identifier rejected									// The Client identifier is correct UTF-8 but not allowed by the Server
	REFUSED_UNAVAILABLE = 3,	// Connection Refused, Server unavailable									// The Network Connection has been made but the MQTT service is unavailable
	REFUSED_USER = 4,			// Connection Refused, bad user name or password							// The data in the user name or password is malformed
	REFUSED_AUTH = 5			// Connection Refused, not authorized										// The Client is not authorized to connect
};

UCLASS()
class UScillMqttPacketConnack : public UScillMqttPacketBase
{
	GENERATED_BODY()
public:
	static UScillMqttPacketConnack* FromBuffer(TArray<uint8> buffer);

	ScillMqttConnackCode Code;
	bool SessionPresent;
};

UCLASS()
class UScillMqttPacketPublish : public UScillMqttPacketBase
{
	GENERATED_BODY()
public:
	static UScillMqttPacketPublish* FromBuffer(TArray<uint8> buffer);

	bool Duplicate;
	uint8 QoS;
	bool Retain;

	FString TopicName;
	uint16 PacketIdentifier;

	FString Payload;
};

UCLASS()
class UScillMqttPacketSubscribe : public UScillMqttPacketBase
{
	GENERATED_BODY()
public:
	TArray<uint8> ToBuffer() override;

	uint16 PacketIdentifier;
	TArray<FString> TopicFilter;

	TArray<uint8> RequestedQoS;
};

UCLASS()
class UScillMqttPacketPing : public UScillMqttPacketBase
{
	GENERATED_BODY()
public:
	TArray<uint8> ToBuffer() override;
};

UCLASS()
class UScillMqttPacketDisconnect : public UScillMqttPacketBase
{
	GENERATED_BODY()
public:
	TArray<uint8> ToBuffer() override;
};

UCLASS()
class UScillMqttPacketPingResp : public UScillMqttPacketBase
{
	GENERATED_BODY()
public:
	static UScillMqttPacketPingResp* FromBuffer(TArray<uint8> buffer);
};

namespace StringHelper
{
	static FString BytesToStringFixed(const uint8* In, int32 Count)
	{
		FString Broken = BytesToString(In, Count);
		FString Fixed;

		for (int i = 0; i < Broken.Len(); i++)
		{
			const TCHAR c = Broken[i] - 1;
			Fixed.AppendChar(c);
		}

		return Fixed;
	}

	static int32 StringToBytesFixed(const FString& String, uint8* OutBytes, int32 MaxBufferSize)
	{
		int32 count = StringToBytes(String, OutBytes, MaxBufferSize);

		for (int i = 0; i < count; i++)
		{
			OutBytes[i] += 1;
		}

		return count;
	}

	static FString TArrayToString(const TArray<uint8> In, int32 Start, int32 Count)
	{
		uint8* buffer = new uint8[Count];

		for (int i = 0; i < Count; i++)
		{
			buffer[i] = In[i + Start];
		}
		
		FString result = BytesToStringFixed(buffer, Count);

		delete buffer;

		return result;
	}

	static int32 StringToTArray(const FString& String, TArray<uint8>& OutArray, int32 MaxBufferSize, int32 Start)
	{
		uint8* buffer = new uint8[MaxBufferSize];

		int32 count = StringToBytesFixed(String, buffer, MaxBufferSize);

		for (int i = 0; i < count; i++)
		{
			OutArray[i + Start] = buffer[i];
		}

		delete buffer;

		return count;
	}
}