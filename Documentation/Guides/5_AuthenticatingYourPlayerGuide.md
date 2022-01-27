# Authenticating your Player

- Part 1: [Getting Started with SCILL and Unreal](/Documentation/Guides/1_GettingStartedGuide.md)
- Part 2: [SCILL API and Unreal SDK Overview](/Documentation/Guides/2_ScillApiOverviewGuide.md)
- Part 3: [Implementing the Unreal SDK on your Game Client](/Documentation/Guides/3_GameClientGuide.md)
- Part 4: [Implementing the Unreal SDK on your Game Server](/Documentation/Guides/4_GameServerGuide.md)

Lastly we want to discuss a proper authentication mechanism of your players. SCILL is not providing an authentication mechanism itself. It expects every request from your users to come with an access token as parameter. That means that you need to implement user authentication yourself and provide every connected user with a token. But this also means that you have the freedom to integrate any authentication with SCILL so that you can build on your current mechanisms.

First, we will have a look at how to authenticate as a user in general with SCILL. Based on this we will take an existing authentication with Valve’s Steamworks SDK and use it to generate an authentication token for your user in a proper way.

In order to test our project you will later need to install the Steam Client on your machine and create a Steam Account if you do not already have one. Both can be done on the [Steam Homepage](https://store.steampowered.com/).

## General SCILL Authentication

The below diagram in the SCILL [developer documentation](https://developers.4players.io/scill/api/authentication/) shows how the SCILL API can be agnostic of your authentication. The Client App waits for a userId or session that it has with your Client Backend and identifies it as a specific user and sends that to the Client Backend. The Client Backend now adds your SCILL App’s API Key and sends both to the Authentication API of SCILL. This returns an access token that you can then send back to your Client App.

![access_token.png](https://developers.4players.io/images/scill/access_token.png)

Before sending the **Generate Access Token** action to the Authentication API, the Client Backend should first check whether the Client App can take actions on behalf of given user. At this point you need to add some logic to your Client App and Client Backend in order to properly authenticate the player.

## Common Authentication Flows

Generally, there are two ways to authenticate a user for a game: use your own self-hosted authentication service - or use an external authentication service.

In self-hosted authentication you can simply let your player send his credentials to your server to check them against your own authentication database. If it matches, the player is authenticated. The check would be done by any trusted source, in most cases your Client Backend. The Client App in return gets a user access token that it can use to authenticate itself at your Client Backend in this session. Only if that token is valid the Client Backend shall send the call  generateAccessToken and receive the accessToken needed to make requests on the SCILL API.

![CustomAuthorization.png](/Documentation/attachments/CustomAuthorization.png)

While this works very well if you own the credentials of your users, this cannot be done if you use an external authentication service like Steam. Steam will need to check three things: if the user can be trusted, but also if your application can be trusted - and if the user has given your application all the permissions that your application requests. So to act on behalf of a Steam User, you will have to also provide an App Id and an API Key for most calls.

![ExternalAuthorization.png](/Documentation/attachments/ExternalAuthorization.png)

## Authenticating a Steam User and Unreal Client

Authenticating a Steam User with your application can be done in several ways. For this tutorial we take advantage of an authentication through the Steam Client on the User’s device. The Unreal Client will act as though it was started by the Steam Client and so it already has a session with the Steam API through the running Steam Client. We use that session to authenticate the Unreal Client with the Steam Service. On our trusted Game Server we can now test if the session is valid and if so, we generate the accessToken for SCILL.

## Steam Online Subsystem

To accomplish this kind of authentication we will use the [Online Subsystem of Unreal Engine 4](https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/Online/). This is an Interface that abstracts the usage of any kind of Online Services - Identity Providers, Stores, Friends, Sessions and so on. The [Steam Online Subsystem](https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/Online/Steam/) is one of its implementations and is deployed with the Unreal Engine as a Plugin. 

You can simply enable it in the Plugin Settings of your Project. Go to the menu bar of the Unreal Editor, click "Edit" and "Plugins..." and search for the **Online Subsystem** and **Online Subsystem Steam** Plugins in the Plugin Browser of your Project and enable them. After that you have to close your Project in the Unreal Editor - but you do not need to restart it yet.

First we will open the DefaultEngine.ini of your project and add the following lines of code - they are copied and pasted from the [Online Subsystem Steam Documentation](https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/Online/Steam/) of the Unreal Engine:

```
[/Script/Engine.GameEngine]
+NetDriverDefinitions=(DefName="GameNetDriver",DriverClassName="OnlineSubsystemSteam.SteamNetDriver",DriverClassNameFallback="OnlineSubsystemUtils.IpNetDriver")

[OnlineSubsystem]
DefaultPlatformService=Steam

[OnlineSubsystemSteam]
bEnabled=true
SteamDevAppId=480

; If using Sessions
; bInitServerOnClient=true

[/Script/OnlineSubsystemSteam.SteamNetDriver]
NetConnectionClassName="OnlineSubsystemSteam.SteamNetConnection"
```

Note that although their documentation says that you need to install the Steamworks SDK, you do not need to do that currently. Epic Games takes care of providing the correct libraries together with each version of the engine since some releases.

Once you have done that you can re-open your project. With these settings you do not need to have a developer’s account with the Steam Service. The provided Steam Dev App Id is shared among all developers and you can use it to test many of its endpoints - most importantly for us, the user authentication.

For this example this is just fine, but for your own game you will need to create a proper App Id on the Steamworks page for it before shipping.

## Exposing Online Subsystem Functionality to Blueprints

In order to work with the Online Subsystem from Blueprints we will need to either use the already exposed Blueprint Calls, use a third party library or write some extra C++ code.

In this tutorial we want to use Blueprints only, so we need to take care of that - you can either write this small Blueprint Library yourself or you can use the plugin in the sample project on the GitHub of SCILL. **GetOssUserId()** does nothing more than just returning the “platform specific user id” - in our case the Steam Id. The **Is User Logged In** function returns whether a user is properly signed in or not.

Header File:

```
// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/PlayerController.h"

#include "SimpleOnlineSubsystemBlueprintsBPLibrary.generated.h"

UCLASS()
class USimpleOnlineSubsystemBlueprintsBPLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_UCLASS_BODY()

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get OSSUser Id", Keywords = "SimpleOnlineSubsystemBlueprints"), Category = "SimpleOnlineSubsystemBlueprints")
    static FString GetOssUserId(int id);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is User Logged In", Keywords = "SimpleOnlineSubsystemBlueprints"), Category = "SimpleOnlineSubsystemBlueprints")
        static bool IsUserLoggedIn(int id);
};
```

Code File:

```
// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleOnlineSubsystemBlueprintsBPLibrary.h"
#include "SimpleOnlineSubsystemBlueprints.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystemTypes.h"
#include "Engine/LocalPlayer.h"

USimpleOnlineSubsystemBlueprintsBPLibrary::USimpleOnlineSubsystemBlueprintsBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FString USimpleOnlineSubsystemBlueprintsBPLibrary::GetOssUserId(int id)
{
    return IOnlineSubsystem::Get()->GetIdentityInterface()->GetUniquePlayerId(id)->ToString();
}

bool USimpleOnlineSubsystemBlueprintsBPLibrary::IsUserLoggedIn(int id)
{
    return IOnlineSubsystem::Get()->GetIdentityInterface()->GetLoginStatus(id);
}
```

## Add Authentication to your Blueprint Classes

Once we have everything setup, we can finally start adjusting our blueprints. 

Open your SCILL Player Controller and navigate to the event in the event graph that is called on the Game Server to generate an access token.

Here we will add a call to **Is User Logged In** and provide it with the index of the current Player Controller. If this returns true we use the Steam ID of that player to generate the accessToken for SCILL.

![AuthenticationInBlueprints.png](/Documentation/attachments/AuthenticationInBlueprints.png)

## Testing the Authentication

So now to test this code you will need to start your Steam Client and login. Once done you can go to the Play in Editor button in the Unreal Editor, and click the small triangle next to it. Here you choose to play in a Standalone Game. This is necessary because our executable needs to act as if it was started by an authenticated Steam Client. Now once we logged in you will have an access token to the Scill API for the Steam ID that you are logged in with on the Steam Client.

That is all you have to adjust in your blueprints in order to properly test if a user is signed in. You can change the used Online Subsystem implementation to whatever subsystem you would like to use - or you can write your own authentication and just replace the test for the logged in user with a call to your API. 

## Conclusion

This wraps up our getting started guides. You should now have a good idea of how to start working with the SCILL API in your Unreal Engine Project. You can follow our Video Tutorials that this guide is based on. Also have a deeper look at the [SDK's reference](/Documentation/Reference.md) and at the [General SCILL Documentation](https://developers.4players.io/scill/).
