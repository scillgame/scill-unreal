/**
 * SCILL API
 * SCILL gives you the tools to activate, retain and grow your user base in your app or game by bringing you features well known in the gaming industry: Gamification. We take care of the services and technology involved so you can focus on your game and content.
 *
 * OpenAPI spec version: 1.0.0
 * Contact: support@scillgame.com
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * https://github.com/OpenAPITools/openapi-generator
 * Do not edit the class manually.
 */

#include "ScillApiWrapper/ScillApiEventDescription.h"

#include "ScillSDK.h"
#include "ScillApiWrapper/ScillApiHelpers.h"

#include "Templates/SharedPointer.h"

namespace ScillSDK
{

void ScillApiEventDescription::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	if (EventName.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("event_name")); WriteJsonValue(Writer, EventName.GetValue());
	}
	if (RequiredProperties.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("required_properties")); WriteJsonValue(Writer, RequiredProperties.GetValue());
	}
	if (OptionalProperties.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("optional_properties")); WriteJsonValue(Writer, OptionalProperties.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool ScillApiEventDescription::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("event_name"), EventName);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("required_properties"), RequiredProperties);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("optional_properties"), OptionalProperties);

	return ParseSuccess;
}

}
