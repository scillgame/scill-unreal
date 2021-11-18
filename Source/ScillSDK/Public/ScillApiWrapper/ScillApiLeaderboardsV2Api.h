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

#include "CoreMinimal.h"
#include "ScillApiWrapper/ScillApiBaseModel.h"

namespace ScillSDK
{

class SCILLSDK_API ScillApiLeaderboardsV2Api
{
public:
	ScillApiLeaderboardsV2Api();
	~ScillApiLeaderboardsV2Api();

	/* Sets the URL Endpoint.
	* Note: several fallback endpoints can be configured in request retry policies, see Request::SetShouldRetry */
	void SetURL(const FString& Url);

	/* Adds global header params to all requests */
	void AddHeaderParam(const FString& Key, const FString& Value);
	void ClearHeaderParams();

	/* Sets the retry manager to the user-defined retry manager. User must manage the lifetime of the retry manager.
	* If no retry manager is specified and a request needs retries, a default retry manager will be used.
	* See also: Request::SetShouldRetry */
	void SetHttpRetryManager(FHttpRetrySystem::FManager& RetryManager);
	FHttpRetrySystem::FManager& GetHttpRetryManager();

	class GetLeaderboardV2Request;
	class GetLeaderboardV2Response;
	class GetLeaderboardV2RankingRequest;
	class GetLeaderboardV2RankingResponse;
	class GetLeaderboardV2RankingsRequest;
	class GetLeaderboardV2RankingsResponse;
	class GetLeaderboardsV2Request;
	class GetLeaderboardsV2Response;
	class ResetLeaderboardV2RankingsRequest;
	class ResetLeaderboardV2RankingsResponse;
	
    DECLARE_DELEGATE_OneParam(FGetLeaderboardV2Delegate, const GetLeaderboardV2Response&);
    DECLARE_DELEGATE_OneParam(FGetLeaderboardV2RankingDelegate, const GetLeaderboardV2RankingResponse&);
    DECLARE_DELEGATE_OneParam(FGetLeaderboardV2RankingsDelegate, const GetLeaderboardV2RankingsResponse&);
    DECLARE_DELEGATE_OneParam(FGetLeaderboardsV2Delegate, const GetLeaderboardsV2Response&);
    DECLARE_DELEGATE_OneParam(FResetLeaderboardV2RankingsDelegate, const ResetLeaderboardV2RankingsResponse&);
    
    FHttpRequestPtr GetLeaderboardV2(const GetLeaderboardV2Request& Request, const FGetLeaderboardV2Delegate& Delegate = FGetLeaderboardV2Delegate()) const;
    FHttpRequestPtr GetLeaderboardV2Ranking(const GetLeaderboardV2RankingRequest& Request, const FGetLeaderboardV2RankingDelegate& Delegate = FGetLeaderboardV2RankingDelegate()) const;
    FHttpRequestPtr GetLeaderboardV2Rankings(const GetLeaderboardV2RankingsRequest& Request, const FGetLeaderboardV2RankingsDelegate& Delegate = FGetLeaderboardV2RankingsDelegate()) const;
    FHttpRequestPtr GetLeaderboardsV2(const GetLeaderboardsV2Request& Request, const FGetLeaderboardsV2Delegate& Delegate = FGetLeaderboardsV2Delegate()) const;
    FHttpRequestPtr ResetLeaderboardV2Rankings(const ResetLeaderboardV2RankingsRequest& Request, const FResetLeaderboardV2RankingsDelegate& Delegate = FResetLeaderboardV2RankingsDelegate()) const;
    
private:
    void OnGetLeaderboardV2Response(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetLeaderboardV2Delegate Delegate) const;
    void OnGetLeaderboardV2RankingResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetLeaderboardV2RankingDelegate Delegate) const;
    void OnGetLeaderboardV2RankingsResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetLeaderboardV2RankingsDelegate Delegate) const;
    void OnGetLeaderboardsV2Response(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetLeaderboardsV2Delegate Delegate) const;
    void OnResetLeaderboardV2RankingsResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FResetLeaderboardV2RankingsDelegate Delegate) const;
    
	FHttpRequestRef CreateHttpRequest(const Request& Request) const;
	bool IsValid() const;
	void HandleResponse(FHttpResponsePtr HttpResponse, bool bSucceeded, Response& InOutResponse) const;

	FString Url;
	TMap<FString,FString> AdditionalHeaderParams;
	mutable FHttpRetrySystem::FManager* RetryManager = nullptr;
	mutable TUniquePtr<HttpRetryManager> DefaultRetryManager;
};

}
