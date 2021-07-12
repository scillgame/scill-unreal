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
#include "ScillApiWrapper/ScillApiEventsApi.h"

#include "ScillApiWrapper/ScillApiActionResponse.h"
#include "ScillApiWrapper/ScillApiEventDescription.h"
#include "ScillApiWrapper/ScillApiEventPayload.h"
#include "ScillApiWrapper/ScillApiUnknownChallengeError.h"

namespace ScillSDK 
{

/* Get all available events and required and optional properties
 *
 * Get all available events and required and optional properties
*/
class SCILLSDK_API ScillApiEventsApi::GetAvailableEventsRequest : public Request
{
public:
    virtual ~GetAvailableEventsRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;
    
};

class SCILLSDK_API ScillApiEventsApi::GetAvailableEventsResponse : public Response
{
public:
    virtual ~GetAvailableEventsResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
    
    TArray<ScillApiEventDescription> Content;
};

/* Post an event
 *
 * Post an event to the SCILL backend
*/
class SCILLSDK_API ScillApiEventsApi::SendEventRequest : public Request
{
public:
    virtual ~SendEventRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;
    
	/* Event payload or team event payload */
	ScillApiEventPayload ScillApiEventPayload;
};

class SCILLSDK_API ScillApiEventsApi::SendEventResponse : public Response
{
public:
    virtual ~SendEventResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
    
    ScillApiActionResponse Content;
};

}
