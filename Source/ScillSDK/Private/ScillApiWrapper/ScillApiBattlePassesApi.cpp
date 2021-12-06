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

#include "ScillApiWrapper/ScillApiBattlePassesApi.h"

#include "ScillApiWrapper/ScillApiBattlePassesApiOperations.h"
#include "ScillSDK.h"

#include "HttpModule.h"
#include "Serialization/JsonSerializer.h"

namespace ScillSDK
{

ScillApiBattlePassesApi::ScillApiBattlePassesApi()
: Url(TEXT("https://virtserver.swaggerhub.com/4Players-GmbH/scill-gaas/1.0.0"))
{
}

ScillApiBattlePassesApi::~ScillApiBattlePassesApi() {}

void ScillApiBattlePassesApi::SetURL(const FString& InUrl)
{
	Url = InUrl;
}

void ScillApiBattlePassesApi::AddHeaderParam(const FString& Key, const FString& Value)
{
	AdditionalHeaderParams.Add(Key, Value);
}

void ScillApiBattlePassesApi::ClearHeaderParams()
{
	AdditionalHeaderParams.Reset();
}

bool ScillApiBattlePassesApi::IsValid() const
{
	if (Url.IsEmpty())
	{
		UE_LOG(LogScillSDK, Error, TEXT("ScillApiBattlePassesApi: Endpoint Url is not set, request cannot be performed"));
		return false;
	}

	return true;
}

void ScillApiBattlePassesApi::SetHttpRetryManager(FHttpRetrySystem::FManager& InRetryManager)
{
	if(RetryManager != &GetHttpRetryManager())
	{
		DefaultRetryManager.Reset();
		RetryManager = &InRetryManager;
	}
}

FHttpRetrySystem::FManager& ScillApiBattlePassesApi::GetHttpRetryManager()
{
	checkf(RetryManager, TEXT("ScillApiBattlePassesApi: RetryManager is null.  You may have meant to set it with SetHttpRetryManager first, or you may not be using a custom RetryManager at all."))
	return *RetryManager;
}

FHttpRequestRef ScillApiBattlePassesApi::CreateHttpRequest(const Request& Request) const
{
	if (!Request.GetRetryParams().IsSet())
	{
		return FHttpModule::Get().CreateRequest();
	}
	else
	{
		if (!RetryManager)
		{
			// Create default retry manager if none was specified
			DefaultRetryManager = MakeUnique<HttpRetryManager>(6, 60);
			RetryManager = DefaultRetryManager.Get();
		}

		const HttpRetryParams& Params = Request.GetRetryParams().GetValue();
		return RetryManager->CreateRequest(Params.RetryLimitCountOverride, Params.RetryTimeoutRelativeSecondsOverride, Params.RetryResponseCodes, Params.RetryVerbs, Params.RetryDomains);
	}
}

void ScillApiBattlePassesApi::HandleResponse(FHttpResponsePtr HttpResponse, bool bSucceeded, Response& InOutResponse) const
{
	InOutResponse.SetHttpResponse(HttpResponse);
	InOutResponse.SetSuccessful(bSucceeded);

	if (bSucceeded && HttpResponse.IsValid())
	{
		InOutResponse.SetHttpResponseCode((EHttpResponseCodes::Type)HttpResponse->GetResponseCode());
		FString ContentType = HttpResponse->GetContentType();
		FString Content;

		if (ContentType.IsEmpty())
		{
			return; // Nothing to parse
		}
		else if (ContentType.StartsWith(TEXT("application/json")) || ContentType.StartsWith("text/json"))
		{
			Content = HttpResponse->GetContentAsString();

			TSharedPtr<FJsonValue> JsonValue;
			auto Reader = TJsonReaderFactory<>::Create(Content);

			if (FJsonSerializer::Deserialize(Reader, JsonValue) && JsonValue.IsValid())
			{
				if (InOutResponse.FromJson(JsonValue))
					return; // Successfully parsed
			}
		}
		else if(ContentType.StartsWith(TEXT("text/plain")))
		{
			Content = HttpResponse->GetContentAsString();
			InOutResponse.SetResponseString(Content);
			return; // Successfully parsed
		}

		// Report the parse error but do not mark the request as unsuccessful. Data could be partial or malformed, but the request succeeded.
		UE_LOG(LogScillSDK, Error, TEXT("Failed to deserialize Http response content (type:%s):\n%s"), *ContentType , *Content);
		return;
	}

	// By default, assume we failed to establish connection
	InOutResponse.SetHttpResponseCode(EHttpResponseCodes::RequestTimeout);
}

FHttpRequestPtr ScillApiBattlePassesApi::ActivateBattlePassLevel(const ActivateBattlePassLevelRequest& Request, const FActivateBattlePassLevelDelegate& Delegate /*= FActivateBattlePassLevelDelegate()*/) const
{
	if (!IsValid())
		return nullptr;

	FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
	HttpRequest->SetURL(*(Url + Request.ComputePath()));

	for(const auto& It : AdditionalHeaderParams)
	{
		HttpRequest->SetHeader(It.Key, It.Value);
	}

	Request.SetupHttpRequest(HttpRequest);

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &ScillApiBattlePassesApi::OnActivateBattlePassLevelResponse, Delegate);
	HttpRequest->ProcessRequest();
	return HttpRequest;
}

void ScillApiBattlePassesApi::OnActivateBattlePassLevelResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FActivateBattlePassLevelDelegate Delegate) const
{
	ActivateBattlePassLevelResponse Response;
	HandleResponse(HttpResponse, bSucceeded, Response);
	Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr ScillApiBattlePassesApi::ClaimBattlePassLevelReward(const ClaimBattlePassLevelRewardRequest& Request, const FClaimBattlePassLevelRewardDelegate& Delegate /*= FClaimBattlePassLevelRewardDelegate()*/) const
{
	if (!IsValid())
		return nullptr;

	FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
	HttpRequest->SetURL(*(Url + Request.ComputePath()));

	for(const auto& It : AdditionalHeaderParams)
	{
		HttpRequest->SetHeader(It.Key, It.Value);
	}

	Request.SetupHttpRequest(HttpRequest);

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &ScillApiBattlePassesApi::OnClaimBattlePassLevelRewardResponse, Delegate);
	HttpRequest->ProcessRequest();
	return HttpRequest;
}

void ScillApiBattlePassesApi::OnClaimBattlePassLevelRewardResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FClaimBattlePassLevelRewardDelegate Delegate) const
{
	ClaimBattlePassLevelRewardResponse Response;
	HandleResponse(HttpResponse, bSucceeded, Response);
	Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr ScillApiBattlePassesApi::GetActiveBattlePasses(const GetActiveBattlePassesRequest& Request, const FGetActiveBattlePassesDelegate& Delegate /*= FGetActiveBattlePassesDelegate()*/) const
{
	if (!IsValid())
		return nullptr;

	FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
	HttpRequest->SetURL(*(Url + Request.ComputePath()));

	for(const auto& It : AdditionalHeaderParams)
	{
		HttpRequest->SetHeader(It.Key, It.Value);
	}

	Request.SetupHttpRequest(HttpRequest);

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &ScillApiBattlePassesApi::OnGetActiveBattlePassesResponse, Delegate);
	HttpRequest->ProcessRequest();
	return HttpRequest;
}

void ScillApiBattlePassesApi::OnGetActiveBattlePassesResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetActiveBattlePassesDelegate Delegate) const
{
	GetActiveBattlePassesResponse Response;
	HandleResponse(HttpResponse, bSucceeded, Response);
	Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr ScillApiBattlePassesApi::GetAllBattlePassLevels(const GetAllBattlePassLevelsRequest& Request, const FGetAllBattlePassLevelsDelegate& Delegate /*= FGetAllBattlePassLevelsDelegate()*/) const
{
	if (!IsValid())
		return nullptr;

	FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
	HttpRequest->SetURL(*(Url + Request.ComputePath()));

	for(const auto& It : AdditionalHeaderParams)
	{
		HttpRequest->SetHeader(It.Key, It.Value);
	}

	Request.SetupHttpRequest(HttpRequest);

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &ScillApiBattlePassesApi::OnGetAllBattlePassLevelsResponse, Delegate);
	HttpRequest->ProcessRequest();
	return HttpRequest;
}

void ScillApiBattlePassesApi::OnGetAllBattlePassLevelsResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetAllBattlePassLevelsDelegate Delegate) const
{
	GetAllBattlePassLevelsResponse Response;
	HandleResponse(HttpResponse, bSucceeded, Response);
	Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr ScillApiBattlePassesApi::GetBattlePass(const GetBattlePassRequest& Request, const FGetBattlePassDelegate& Delegate /*= FGetBattlePassDelegate()*/) const
{
	if (!IsValid())
		return nullptr;

	FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
	HttpRequest->SetURL(*(Url + Request.ComputePath()));

	for(const auto& It : AdditionalHeaderParams)
	{
		HttpRequest->SetHeader(It.Key, It.Value);
	}

	Request.SetupHttpRequest(HttpRequest);

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &ScillApiBattlePassesApi::OnGetBattlePassResponse, Delegate);
	HttpRequest->ProcessRequest();
	return HttpRequest;
}

void ScillApiBattlePassesApi::OnGetBattlePassResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetBattlePassDelegate Delegate) const
{
	GetBattlePassResponse Response;
	HandleResponse(HttpResponse, bSucceeded, Response);
	Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr ScillApiBattlePassesApi::GetBattlePassLevels(const GetBattlePassLevelsRequest& Request, const FGetBattlePassLevelsDelegate& Delegate /*= FGetBattlePassLevelsDelegate()*/) const
{
	if (!IsValid())
		return nullptr;

	FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
	HttpRequest->SetURL(*(Url + Request.ComputePath()));

	for(const auto& It : AdditionalHeaderParams)
	{
		HttpRequest->SetHeader(It.Key, It.Value);
	}

	Request.SetupHttpRequest(HttpRequest);

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &ScillApiBattlePassesApi::OnGetBattlePassLevelsResponse, Delegate);
	HttpRequest->ProcessRequest();
	return HttpRequest;
}

void ScillApiBattlePassesApi::OnGetBattlePassLevelsResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetBattlePassLevelsDelegate Delegate) const
{
	GetBattlePassLevelsResponse Response;
	HandleResponse(HttpResponse, bSucceeded, Response);
	Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr ScillApiBattlePassesApi::GetBattlePasses(const GetBattlePassesRequest& Request, const FGetBattlePassesDelegate& Delegate /*= FGetBattlePassesDelegate()*/) const
{
	if (!IsValid())
		return nullptr;

	FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
	HttpRequest->SetURL(*(Url + Request.ComputePath()));

	for(const auto& It : AdditionalHeaderParams)
	{
		HttpRequest->SetHeader(It.Key, It.Value);
	}

	Request.SetupHttpRequest(HttpRequest);

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &ScillApiBattlePassesApi::OnGetBattlePassesResponse, Delegate);
	HttpRequest->ProcessRequest();
	return HttpRequest;
}

void ScillApiBattlePassesApi::OnGetBattlePassesResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetBattlePassesDelegate Delegate) const
{
	GetBattlePassesResponse Response;
	HandleResponse(HttpResponse, bSucceeded, Response);
	Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr ScillApiBattlePassesApi::GetUnlockedBattlePasses(const GetUnlockedBattlePassesRequest& Request, const FGetUnlockedBattlePassesDelegate& Delegate /*= FGetUnlockedBattlePassesDelegate()*/) const
{
	if (!IsValid())
		return nullptr;

	FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
	HttpRequest->SetURL(*(Url + Request.ComputePath()));

	for(const auto& It : AdditionalHeaderParams)
	{
		HttpRequest->SetHeader(It.Key, It.Value);
	}

	Request.SetupHttpRequest(HttpRequest);

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &ScillApiBattlePassesApi::OnGetUnlockedBattlePassesResponse, Delegate);
	HttpRequest->ProcessRequest();
	return HttpRequest;
}

void ScillApiBattlePassesApi::OnGetUnlockedBattlePassesResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetUnlockedBattlePassesDelegate Delegate) const
{
	GetUnlockedBattlePassesResponse Response;
	HandleResponse(HttpResponse, bSucceeded, Response);
	Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr ScillApiBattlePassesApi::UnlockBattlePass(const UnlockBattlePassRequest& Request, const FUnlockBattlePassDelegate& Delegate /*= FUnlockBattlePassDelegate()*/) const
{
	if (!IsValid())
		return nullptr;

	FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
	HttpRequest->SetURL(*(Url + Request.ComputePath()));

	for(const auto& It : AdditionalHeaderParams)
	{
		HttpRequest->SetHeader(It.Key, It.Value);
	}

	Request.SetupHttpRequest(HttpRequest);

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &ScillApiBattlePassesApi::OnUnlockBattlePassResponse, Delegate);
	HttpRequest->ProcessRequest();
	return HttpRequest;
}

void ScillApiBattlePassesApi::OnUnlockBattlePassResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnlockBattlePassDelegate Delegate) const
{
	UnlockBattlePassResponse Response;
	HandleResponse(HttpResponse, bSucceeded, Response);
	Delegate.ExecuteIfBound(Response);
}

}
