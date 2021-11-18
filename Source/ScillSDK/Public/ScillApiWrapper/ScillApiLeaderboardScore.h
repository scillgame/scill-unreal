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

#pragma once


#include "ScillApiWrapper/ScillApiBaseModel.h"

namespace ScillSDK
{

/*
 * ScillApiLeaderboardScore
 *
 * Contains info about rank and score
 */
class SCILLSDK_API ScillApiLeaderboardScore : public Model
{
public:
    virtual ~ScillApiLeaderboardScore() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* The score achieved as an integer value. If you want to store floats, for example laptimes you need to convert them into an int before (i.e. multiply by 100 to get hundreds of seconds and format back to float in UI) */
	TOptional<int32> Score;
	/* The position within the leaderboard */
	TOptional<int32> Rank;
};

}
