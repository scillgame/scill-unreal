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

#include "ScillApiWrapper/ScillApiAuthApiOperations.h"

#include "ScillSDK.h"
#include "ScillApiWrapper/ScillApiHelpers.h"

#include "Dom/JsonObject.h"
#include "Templates/SharedPointer.h"
#include "HttpModule.h"
#include "PlatformHttp.h"

namespace ScillSDK 
{

FString ScillApiAuthApi::GenerateAccessTokenRequest::ComputePath() const
{
	FString Path(TEXT("/api/v1/auth/access-token"));
	return Path;
}

void ScillApiAuthApi::GenerateAccessTokenRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = { TEXT("application/json") };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("POST"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
		// Body parameters
		FString JsonBody;
		JsonWriter Writer = TJsonWriterFactory<>::Create(&JsonBody);

		WriteJsonValue(Writer, ScillApiForeignUserIdentifier);
		Writer->Close();

		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
		HttpRequest->SetContentAsString(JsonBody);
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
		UE_LOG(LogScillSDK, Error, TEXT("Body parameter (ScillApiForeignUserIdentifier) was ignored, not supported in multipart form"));
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
		UE_LOG(LogScillSDK, Error, TEXT("Body parameter (ScillApiForeignUserIdentifier) was ignored, not supported in urlencoded requests"));
	}
	else
	{
		UE_LOG(LogScillSDK, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void ScillApiAuthApi::GenerateAccessTokenResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("Returns the access token"));
		break;
	case 403:
		SetResponseString(TEXT("Unauthorized"));
		break;
	case 404:
		SetResponseString(TEXT("The specified resource was not found"));
		break;
	case 500:
		SetResponseString(TEXT("Failed on server side"));
		break;
	}
}

bool ScillApiAuthApi::GenerateAccessTokenResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString ScillApiAuthApi::GetUserBattlePassNotificationTopicRequest::ComputePath() const
{
	FString Path(TEXT("/api/v1/auth/user-battle-pass-topic-link"));
	TArray<FString> QueryParams;
	QueryParams.Add(FString(TEXT("battle_pass_id=")) + ToUrlString(BattlePassId));
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void ScillApiAuthApi::GetUserBattlePassNotificationTopicRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
	}
	else
	{
		UE_LOG(LogScillSDK, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void ScillApiAuthApi::GetUserBattlePassNotificationTopicResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("Returns the socket token"));
		break;
	case 403:
		SetResponseString(TEXT("Unauthorized"));
		break;
	case 404:
		SetResponseString(TEXT("The specified resource was not found"));
		break;
	}
}

bool ScillApiAuthApi::GetUserBattlePassNotificationTopicResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString ScillApiAuthApi::GetUserChallengeNotificationTopicRequest::ComputePath() const
{
	FString Path(TEXT("/api/v1/auth/user-challenge-topic-link"));
	TArray<FString> QueryParams;
	QueryParams.Add(FString(TEXT("challenge_id=")) + ToUrlString(ChallengeId));
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void ScillApiAuthApi::GetUserChallengeNotificationTopicRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
	}
	else
	{
		UE_LOG(LogScillSDK, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void ScillApiAuthApi::GetUserChallengeNotificationTopicResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("Returns the socket token"));
		break;
	case 403:
		SetResponseString(TEXT("Unauthorized"));
		break;
	case 404:
		SetResponseString(TEXT("The specified resource was not found"));
		break;
	}
}

bool ScillApiAuthApi::GetUserChallengeNotificationTopicResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString ScillApiAuthApi::GetUserChallengesNotificationTopicRequest::ComputePath() const
{
	FString Path(TEXT("/api/v1/auth/user-challenges-topic-link"));
	return Path;
}

void ScillApiAuthApi::GetUserChallengesNotificationTopicRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
	}
	else
	{
		UE_LOG(LogScillSDK, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void ScillApiAuthApi::GetUserChallengesNotificationTopicResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("Returns the socket token"));
		break;
	case 403:
		SetResponseString(TEXT("Unauthorized"));
		break;
	case 404:
		SetResponseString(TEXT("The specified resource was not found"));
		break;
	}
}

bool ScillApiAuthApi::GetUserChallengesNotificationTopicResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

}