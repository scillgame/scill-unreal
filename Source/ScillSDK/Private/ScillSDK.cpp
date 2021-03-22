// Copyright Epic Games, Inc. All Rights Reserved.

#include "ScillSDK.h"
#include "WebSocketsModule.h"

#define LOCTEXT_NAMESPACE "SCILLSDK_API"

void ScillSDKModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FWebSocketsModule webSocketModule = FModuleManager::LoadModuleChecked<FWebSocketsModule>(TEXT("WebSockets"));
}

void ScillSDKModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(ScillSDKModule, ScillSDK);
DEFINE_LOG_CATEGORY(LogScillSDK);