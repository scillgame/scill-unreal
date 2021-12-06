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

#include "ScillApiWrapper/ScillApiLeaderboardMemberRanking.h"

#include "ScillSDK.h"
#include "ScillApiWrapper/ScillApiHelpers.h"

#include "Templates/SharedPointer.h"

namespace ScillSDK
{

void ScillApiLeaderboardMemberRanking::WriteJson(JsonWriter& Writer) const
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
	if (Member.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("member")); WriteJsonValue(Writer, Member.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool ScillApiLeaderboardMemberRanking::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("leaderboard_id"), LeaderboardId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("name"), Name);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("member"), Member);

	return ParseSuccess;
}

}
