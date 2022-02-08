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

#include "ScillApiWrapper/ScillApiLeaderboard.h"

#include "ScillSDKModule.h"
#include "ScillApiWrapper/ScillApiHelpers.h"

#include "Templates/SharedPointer.h"

namespace ScillSDK
{

void ScillApiLeaderboard::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	if (LeaderboardId.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("leaderboard_id")); WriteJsonValue(Writer, LeaderboardId.GetValue());
	}
	if (Name.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("name")); WriteJsonValue(Writer, Name.GetValue());
	}
	if (GroupedByUsers.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("grouped_by_users")); WriteJsonValue(Writer, GroupedByUsers.GetValue());
	}
	if (GroupedByTeams.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("grouped_by_teams")); WriteJsonValue(Writer, GroupedByTeams.GetValue());
	}
	if (NumTeams.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("num_teams")); WriteJsonValue(Writer, NumTeams.GetValue());
	}
	if (NumUsers.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("num_users")); WriteJsonValue(Writer, NumUsers.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool ScillApiLeaderboard::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("leaderboard_id"), LeaderboardId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("name"), Name);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("grouped_by_users"), GroupedByUsers);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("grouped_by_teams"), GroupedByTeams);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("num_teams"), NumTeams);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("num_users"), NumUsers);

	return ParseSuccess;
}

}
