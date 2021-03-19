// Fill out your copyright notice in the Description page of Project Settings.


#include "ScillHelpers/ScillMqtt.h"

UScillMqtt::UScillMqtt()
{
	mqttWs = FWebSocketsModule::Get().CreateWebSocket(TEXT("wss://mqtt.scillgame.com:8083/mqtt"), TEXT("mqtt"));

	mqttWs->OnConnected().AddUObject(this, &UScillMqtt::OnConnect);
	mqttWs->OnConnectionError().AddUObject(this, &UScillMqtt::OnConnectionError);

	mqttWs->OnRawMessage().AddUObject(this, &UScillMqtt::OnRawMessage);

	mqttWs->Connect();
}

void UScillMqtt::OnRawMessage(const void* data, SIZE_T Size, SIZE_T BytesRemaining)
{
	uint8* receivedMessage = (uint8*)data;

	ScillMqttPacketBase packet = ScillMqttPacketBase::FromBuffer(receivedMessage);

	if (packet.PacketType == ScillMqttPacketType::PUBLISH)
	{
		ScillMqttPacketPublish pubPacket = static_cast<ScillMqttPacketPublish&>(packet);
		UE_LOG(LogTemp, Warning, TEXT("Received MQTT Publish Message: %s"), *pubPacket.Payload);
	}

	return;
}

void UScillMqtt::OnConnectionError(const FString& Error)
{
	UE_LOG(LogTemp, Error, TEXT("Could not establish connection to MQTT Server: %s"), *Error);
	return;
}

void UScillMqtt::OnConnect()
{
	auto pk = ScillMqttPacketConnect();

	pk.KeepAlive = 6000;
	pk.WillRetain = false;
	pk.WillQoS = 0;
	pk.CleanSession = 1;

	pk.Buffer = pk.ToBuffer();

	mqttWs->Send(pk.Buffer, pk.Length, true);
}

uint8* ScillMqttPacketConnect::ToBuffer()
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

	if (varlength > 268435455) return nullptr;

	// add bytes for remaining length
	length += varlength < 128 ? 1 : varlength < 16384 ? 2 : varlength < 2097152 ? 3 : 4;

	// allocate array
	this->Length = length + varlength;
	this->RemainLength = varlength;
	uint8* buffer = new uint8[length + varlength];

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
	buffer[pointer++] = this->ProtocolName.Len() / 128; //MSB
	buffer[pointer++] = this->ProtocolName.Len() % 128; //LSB

	int32 pnLen = StringHelper::StringToBytesFixed(this->ProtocolName, buffer + pointer, this->ProtocolName.Len());
	pointer += pnLen;

	// Protocol Level, version 3.1.1
	buffer[pointer++] = 4;

	// Connect Flags
	this->SetConnectFlags();
	buffer[pointer++] = this->ConnectFlags;

	// Keep Alive
	buffer[pointer++] = this->KeepAlive / 128; //MSB
	buffer[pointer++] = this->KeepAlive % 128; //LSB

	// Payload

	// Client Identifier
	buffer[pointer++] = this->ClientId.Len() / 128; //MSB
	buffer[pointer++] = this->ClientId.Len() % 128; //LSB
	int32 cIdLen = StringHelper::StringToBytesFixed(this->ClientId, buffer + pointer, this->ClientId.Len());
	pointer += cIdLen;

	// Will Topic
	if (this->ConnectFlags & ScillMqttConnectFlags::WILL)
	{
		buffer[pointer++] = this->WillTopic.Get("").Len() / 128; //MSB
		buffer[pointer++] = this->WillTopic.Get("").Len() % 128; //LSB

		int32 wtLen = StringHelper::StringToBytesFixed(this->WillTopic.Get(""), buffer + pointer, this->WillTopic.Get("").Len());
		pointer += wtLen;
	}

	// Will Message
	if (this->ConnectFlags & ScillMqttConnectFlags::WILL)
	{
		buffer[pointer++] = this->WillMessage.Get("").Len() / 128; //MSB
		buffer[pointer++] = this->WillMessage.Get("").Len() % 128; //LSB

		int32 wmLen = StringHelper::StringToBytesFixed(this->WillMessage.Get(""), buffer + pointer, this->WillMessage.Get("").Len());
		pointer += wmLen;
	}

	// User Name
	if (this->ConnectFlags & ScillMqttConnectFlags::USER_NAME)
	{
		buffer[pointer++] = this->UserName.Get("").Len() / 128; //MSB
		buffer[pointer++] = this->UserName.Get("").Len() % 128; //LSB

		int32 unLen = StringHelper::StringToBytesFixed(this->UserName.Get(""), buffer + pointer, this->UserName.Get("").Len());
		pointer += unLen;
	}

	// Password
	if (this->ConnectFlags & ScillMqttConnectFlags::PASSWORD)
	{
		buffer[pointer++] = this->Password.Get("").Len() / 128; //MSB
		buffer[pointer++] = this->Password.Get("").Len() % 128; //LSB

		int32 pwLen = StringHelper::StringToBytesFixed(this->Password.Get(""), buffer + pointer, this->Password.Get("").Len());
		pointer += pwLen;
	}

	return buffer;
}


void ScillMqttPacketConnect::SetConnectFlags() {
	this->ConnectFlags = this->UserName.IsSet() ? ScillMqttConnectFlags::USER_NAME : 0;
	this->ConnectFlags += this->Password.IsSet() && this->UserName.IsSet() ? ScillMqttConnectFlags::PASSWORD : 0;
	this->ConnectFlags += this->WillRetain && this->WillMessage.IsSet() && this->WillTopic.IsSet() ? ScillMqttConnectFlags::WILL_RETAIN : 0;
	this->ConnectFlags += this->WillMessage.IsSet() && this->WillTopic.IsSet() ? this->WillQoS % 4 << 3 : 0;
	this->ConnectFlags += this->WillMessage.IsSet() && this->WillTopic.IsSet() ? ScillMqttConnectFlags::WILL : 0;
	this->ConnectFlags += this->CleanSession ? ScillMqttConnectFlags::CLEAN_SESSION : 0;
}

uint8* ScillMqttPacketBase::ToBuffer()
{
	return new uint8[0];
}

ScillMqttPacketConnack ScillMqttPacketConnack::FromBuffer(uint8* buffer)
{
	auto pk = ScillMqttPacketConnack();

	uint64 pointer = 0;

	// Packet Type
	uint8 firstByte = buffer[pointer++];
	pk.PacketType = (ScillMqttPacketType)((firstByte & 0xf0) >> 4);

	// Skip Remaining Length, since it is always "2"
	pointer++;

	// Session Present
	pk.SessionPresent = (bool)buffer[pointer++];

	// Connection Response Code
	pk.Code = (ScillMqttConnackCode)buffer[pointer++];

	return ScillMqttPacketConnack();
}

ScillMqttPacketType ScillMqttPacketBase::GetPacketTypeFromBuffer(uint8* buffer)
{
	uint8 firstByte = buffer[0];
	return (ScillMqttPacketType)((firstByte & 0xf0) >> 4);
}

ScillMqttPacketBase ScillMqttPacketBase::FromBuffer(uint8* buffer)
{
	auto messageType = ScillMqttPacketBase::GetPacketTypeFromBuffer(buffer);

	switch (messageType)
	{
		case ScillMqttPacketType::CONNECT:
			UE_LOG(LogTemp, Error, TEXT("Unexpected MQTT packet received: CONNECT"));
			return ScillMqttPacketConnect();
		case ScillMqttPacketType::CONNACK:
			return ScillMqttPacketConnack::FromBuffer(buffer);
		case ScillMqttPacketType::PUBLISH:
			return ScillMqttPacketPublish::FromBuffer(buffer);
	}

	return ScillMqttPacketBase();
}

uint64 ScillMqttPacketBase::GetRemainingLengthFromBuffer(uint8* buffer)
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

ScillMqttPacketPublish ScillMqttPacketPublish::FromBuffer(uint8* buffer)
{
	auto pk = ScillMqttPacketPublish();

	uint64 pointer = 0;

	// Packet Type
	uint8 firstByte = buffer[pointer++];
	pk.PacketType = (ScillMqttPacketType)((firstByte & 0xf0) >> 4);

	// Packet Flags
	pk.PacketFlags = firstByte & 0x0f;

	// Set Fields according to Packet Flags
	pk.Duplicate = (bool)(pk.PacketFlags & 0x01);
	pk.QoS = (uint8)((pk.PacketFlags & 0x06) >> 1);
	pk.Retain = (bool)(pk.PacketFlags & 0x08);

	// Remain Length
	pk.RemainLength = ScillMqttPacketBase::GetRemainingLengthFromBuffer(buffer);
	pk.Length = ScillMqttPacketBase::CalculateLengthFromRemaining(pk.RemainLength);
	pointer = ScillMqttPacketBase::FixedHeaderLengthFromRemaining(pk.RemainLength) - 1;

	// Topic Name
	uint16 tpLength = buffer[pointer++] * 128 + buffer[pointer++]; // MSB + LSB
	pk.TopicName = StringHelper::BytesToStringFixed(&buffer[pointer], tpLength);
	pointer += tpLength;

	// Packet Identifier
	if (pk.QoS)
	{
		pk.PacketIdentifier = buffer[pointer++] * 128 + buffer[pointer++];
	}

	// Payload
	uint64 plLength = pk.Length - pointer;
	pk.Payload = StringHelper::BytesToStringFixed(&buffer[pointer], plLength);

	return pk;
}

uint64 ScillMqttPacketBase::CalculateLengthFromRemaining(uint64 remainingLength)
{
	return remainingLength + (remainingLength < 128 ? 2 : remainingLength < 16384 ? 3 : 4);
}

uint8 ScillMqttPacketBase::FixedHeaderLengthFromRemaining(uint64 remainingLength)
{
	return remainingLength < 128 ? 2 : remainingLength < 16384 ? 3 : 4;
}