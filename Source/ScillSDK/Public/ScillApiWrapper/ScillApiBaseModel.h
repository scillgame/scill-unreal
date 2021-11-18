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

#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonWriter.h"
#include "Dom/JsonObject.h"
#include "HttpRetrySystem.h"
#include "Containers/Ticker.h"

namespace ScillSDK
{

typedef TSharedRef<TJsonWriter<>> JsonWriter;
using namespace FHttpRetrySystem;

struct SCILLSDK_API HttpRetryManager : public FManager, public FTickerObjectBase
{
	using FManager::FManager;

	bool Tick(float DeltaTime) final;
};

struct SCILLSDK_API HttpRetryParams
{
	HttpRetryParams(
		const FRetryLimitCountSetting& InRetryLimitCountOverride = FRetryLimitCountSetting(),
		const FRetryTimeoutRelativeSecondsSetting& InRetryTimeoutRelativeSecondsOverride = FRetryTimeoutRelativeSecondsSetting(),
		const FRetryResponseCodes& InRetryResponseCodes = FRetryResponseCodes(),
		const FRetryVerbs& InRetryVerbs = FRetryVerbs(),
		const FRetryDomainsPtr& InRetryDomains = FRetryDomainsPtr()
	);

	FRetryLimitCountSetting              RetryLimitCountOverride;
	FRetryTimeoutRelativeSecondsSetting  RetryTimeoutRelativeSecondsOverride;
	FRetryResponseCodes					 RetryResponseCodes;
	FRetryVerbs                          RetryVerbs;
	FRetryDomainsPtr					 RetryDomains;
};

class SCILLSDK_API Model
{
public:
	virtual ~Model() {}
	virtual void WriteJson(JsonWriter& Writer) const = 0;
	virtual bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) = 0;
};

class SCILLSDK_API Request
{
public:
	virtual ~Request() {}
	virtual void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const = 0;
	virtual FString ComputePath() const = 0;

	/* Enables retry and optionally sets a retry policy for this request */
	void SetShouldRetry(const HttpRetryParams& Params = HttpRetryParams()) { RetryParams = Params; }
	const TOptional<HttpRetryParams>& GetRetryParams() const { return RetryParams; }

private:
	TOptional<HttpRetryParams> RetryParams;
};

class SCILLSDK_API Response
{
public:
	virtual ~Response() {}
	virtual bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) = 0;

	void SetSuccessful(bool InSuccessful) { Successful = InSuccessful; }
	bool IsSuccessful() const { return Successful; }

	virtual void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode);
	EHttpResponseCodes::Type GetHttpResponseCode() const { return ResponseCode; }

	void SetResponseString(const FString& InResponseString) { ResponseString = InResponseString; }
	const FString& GetResponseString() const { return ResponseString; }

	void SetHttpResponse(const FHttpResponsePtr& InHttpResponse) { HttpResponse = InHttpResponse; }
	const FHttpResponsePtr& GetHttpResponse() const { return HttpResponse; }

private:
	bool Successful;
	EHttpResponseCodes::Type ResponseCode;
	FString ResponseString;
	FHttpResponsePtr HttpResponse;
};

}
