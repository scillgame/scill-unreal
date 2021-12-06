# Scill Unreal Plugin

Our Unreal Plugin offers easy access to the Scill HTTP API for simple requests and to the Scill MQTT Server for real-time updates. These functions enable access to the API from the Unreal Blueprint System. While you can also access these functions from C++ code of your plugin, this documentation focuses on Blueprints. Simply transfer the usage to C++ code (which should be trivial most of the times). The Plugin offers Components and Interfaces that are best added to your Game Mode, Player Controller and Game Instance.

Since this Plugin is completely open source you are welcomed to adjust them to your own needs, extending or changing the classes.

## Source Code

You can find the source code to our Unreal Plugin in our public Github repository: https://github.com/scillgame/scill-unreal. If you encounter any bugs or issues with the Plugin, please let us know in the Issues tab of Github.

If you fix a bug in our code base, please commit your bugfix in a separate branch and create a merge request with a short description what you have fixed. Of course, we will credit you and your game in the changelog and at the start page of our Github repository in this case!

## Installing the Plugin

Installation of the Plugin is fairly easy. Just download the source from our Github repository and copy the content into the `Plugins/ScillSDK` subdirectory of your Project. If not yet present, create any folder needed.

![PluginFolder.png](/Documentation/attachments/PluginFolder.png)

After that you normally only have to open the project and start working. It might be necessary to enable the Plugin under `Edit->Plugins` in the Unreal Editor's menu bar.

![MenuBar_Plugins.png](/Documentation/attachments/MenuBar_Plugins.png)

You should not need to compile the source code. If this is not the case you will have to install Visual Studio with the correct workflow modules - refer to Epic Game's documentation about that for more details: https://docs.unrealengine.com/en-US/ProductionPipelines/DevelopmentSetup/VisualStudioSetup/index.html.

## Notes about Working with the Plugin

In order to properly work with this plugin and also ensure security in your game you most likely want to be familiar with the concept of [Game Modes](https://docs.unrealengine.com/en-US/InteractiveExperiences/Framework/GameMode/index.html), [Player Controllers](https://docs.unrealengine.com/en-US/InteractiveExperiences/Framework/Controller/PlayerController/index.html), [Pawns](https://docs.unrealengine.com/en-US/InteractiveExperiences/Framework/Pawn/index.html), [Game Instances](https://docs.unrealengine.com/en-US/InteractiveExperiences/Framework/GameFlow/index.html) and, for multiplayer games, [Networking](https://docs.unrealengine.com/en-US/InteractiveExperiences/Networking/index.html).

Besides these basic concepts in the Unreal Engine also make yourself familiar with the work-wise of the Scill API - this section assumes you have basic knowledge of the API, for a good starting point visit the [Scill Guides](https://developers.scillgame.com/guides/guides-overview.html).

## Getting Started

This section gives you an overview of the steps to start integrating this plugin into your Unreal Project after it has been installed.

### C++

To enable the usage of the plugin's components and functions in your game's module inside your C++ Unreal Project, you first need to add it to your module's public dependencies. In your `Build.cs` file (located in your project in `Source/[YourGame]/[YourGame].Build.cs`) you need to add the `ScillSDK` module to the Public Dependency Module Names:

```C#
public class PluginCodeProject : ModuleRules
{
    public PluginCodeProject(ReadOnlyTargetRules Target) : base(Target)
    {
        // ...
        PublicDependencyModuleNames.AddRange(new string[] { "ScillSDK" });
        // ...
    }
}
```

Then you need to include the according header files wherever needed. E.g.:

`#include "ScillBlueprintClasses/ScillClient.h"`

In the rest of this guide we mostly refer to blueprints. All these information can be applied in the same way to the C++ counterparts and thus are left out of this guide.

### Placing the Components

After making sure, that the plugin is enabled you can start adding the needed components and implementing the interfaces in your game classes. Normally, three locations are best for this:

- [Player Controller](#player-controller-scill-client-component)
- [Game Mode](#game-mode-scill-client-backend-component)
- [Game Instance](#game-instance-scill-level-persistence-interface)

### Player Controller: Scill Client Component

The Scill Client Component communicates with the Scill API about everything related to player actions. This is mainly receiving information about the player's challenges and battle passes, activating them or claiming their rewards.

To access its functionality on your game client it is best to add it to the Player Controller. This way it has a representation on the game client as well as on the game server (if you are using one). Through replication the Player Controller can then communicate with the Scill Client Backend Component - which best resides on the server side of your game. We will take a look at why this is necessary later on.

![PlayerControllerComponent.png](/Documentation/attachments/PlayerControllerComponent.png)

### Game Mode: Scill Client Backend Component

The Scill Client Backend Component communicates on behalf of your application with the Scill API. Since it needs your API Key it is best to not distribute it to your game clients but rather keep it on your game server only. The Scill Client Backend Component is mainly used to receive game relevant information and generate access tokens for your client components.

To access its functionality on your game server it is best to add it to the Game Mode. This way it is only present on the game server and all its information will never be replicated to your game's clients. Remember that if you want to communicate with this component you may have to replicate a call to your game server first.

![GameModeComponent.png](/Documentation/attachments/GameModeComponent.png)

### Game Instance: Scill Level Persistence Interface

The Scill Level Persistence Interface offers methods to read and write the User ID and the Access Token. Most times, the user logs in before loading any unreal map or the user session should persist between several levels or matches. While the Game Instance persists across multiple levels this is best used to store the information about the current user. The Scill Client Component already searches for a Game Instance implementing the Scill Level Persistence Interface and sets or reads it (if already set), when you access it via their blueprint setters and getters of the Scill Client Component.

![UserIdPersistence.png](/Documentation/attachments/UserIdPersistence.png)

To access its functionality on your game client it is best to add it as an interface to your Game Instance. This way it is only present on your game client and persists its state across the whole game session. To add an interface to a blueprint class, open the blueprint editor, find the "Class Settings" button and in the Details panel under "Interfaces" add an "Implemented Interface".

![GameInstanceInterface.png](/Documentation/attachments/GameInstanceInterface.png)

### User ID and Access Token

To properly generate an access token you need to follow several steps. First is to authenticate the player with your game's backend. Since this is no part of the Scill API and it even wants to be agnostic of your users, you can just do this the way that you prefer. It is just important to return a player-unique id in this process to your game client.

Save this User ID on your game client by calling the respective setter on the Scill Client Component in your Player Controller.

![UserIdPersistence.png](/Documentation/attachments/UserIdPersistence.png)

Afterwards you can use it to call the [Generate Access Token](#generate-access-token) function on your [Scill Client Backend](#scill-client-backend) inside the Game Mode. Make sure that your game client is already connected to a Game Server before calling this, so that the scill client backend already exists and is reachable, or has the correct API Key, respectively. Follow the steps in [Generate Access Token](#generate-access-token) to properly incorporate this mechanic into your project.

After retrieving and saving the access token to your Scill Client Component on your Player Controller on the Client side, you can call any other method on your Scill Client to communicate with the Scill API.

### Remarks

- The access token usually expires after 24 hours. So make sure to re-retrieve an access token in an appropriate time interval. Keep in mind that these calls also count towards your rate limit and you should not simply generate an access token before any other API call.
- Use the [Real-Time Updates](#real-time-updates) to start listening to any changes on a user's challenges or battle passes. The callbacks on these functions are used to process the corresponding payloads. This can be helpful to easily implement UI that is unrelated to the rest of your game logic.
- Before starting Realtime Updates, you must make sure, that the MQTT connection is established already. You can use the [On Realtime Connection Open](/Documentation/Reference.md) function and start the updates in the provided callback.

## Classes and Structs Reference

To get an overview of all Classes and Structs that are present in this plugin, see [Class Reference](/Documentation/Reference.md).

## User Widgets

To learn how to use the included User Widgets in your project, refer to the [User Widgets Guide](/Documentation/UserWidgets.md).
