# Overview of the SCILL API

In this section we will look at both, the SCILL API in general and the Unreal SDK. We will discuss the intended workflows in the Unreal Project and have a look at common problems that you might run into.

The other parts of this guide:

- Part 1: [Getting Started with SCILL and Unreal](/Documentation/Guides/1_GettingStartedGuide.md)
- Part 3: [Implementing the Unreal SDK on your Game Client](/Documentation/Guides/3_GameClientGuide.md)
- Part 4: [Implementing the Unreal SDK on your Game Server](/Documentation/Guides/4_GameServerGuide.md)
- Part 5: [Authenticating your Player](/Documentation/Guides/5_AuthenticatingYourPlayerGuide.md)

So to start this off, we first want to look at SCILL in general. As described earlier, SCILL is a gamification service that you can use to boost your applications’ user motivation and, as a consequence, user retention. SCILL currently offers three types of tools for this: Personal Challenges, Battle Passes and Leaderboards. 

Although they’ve been designed with certain use cases in mind, they are quite generic and can each be used in different ways. 

Personal Challenges provide your users with specific objectives that they can try to fulfill in a given time to receive a certain reward. Personal Challenges can be used to create Daily, Weekly or otherwise repeating challenges, or create Achievements. The detailed life cycle of a Personal Challenge can be looked up in the [SCILL documentation](https://developers.4players.io/scill/api/challenges/#challenge-life-cycle). But generally a Personal Challenge starts in the “unlock” state for each user and, after unlocking, needs to be activated. Then the state of the Challenge is tracked using incoming [events](https://developers.4players.io/scill/api/events/) of your application. If an event matches the tracked event-type, the challenge is adjusted according to the event’s metadata. Once the challenge is completed it turns “unclaimed”, and after the user claims it, it either changes to complete or back to unlock.

![challenge_life_cycle.png](/Documentation/attachments/challenge_life_cycle.png)

[Battle Passes](https://developers.4players.io/scill/api/battlepasses/) work in a similar way, but they embed the challenges in a structure that is inspired by the famous battle passes that are present in many games nowadays. A battle pass consists of several [battle pass levels](https://developers.4players.io/scill/api/battlepasses/#the-battlepasslevel-object), that in turn consist of several [challenges](https://developers.4players.io/scill/api/battlepasses/#the-battlepasslevelchallenge-object). Once all challenges of a battle pass level are completed, the user can claim the battle pass reward. The Life Cycles of battle passes, battle pass levels and their challenges are adjusted accordingly.

Lastly there are [leaderboards](https://developers.4players.io/scill/api/leaderboards-v2/). They encourage users through rivalry. For each leaderboard you can determine which event type should be tracked in which way. Then each player’s score is calculated just the same way as with challenges and the rank is determined accordingly.

## The Scill Admin Panel

To manage these you can use the [Scill Admin Panel](https://admin.scillgame.com/) or the [Scill Admin API](https://developers.4players.io/scill/admin-sdks/) - for this tutorial we will have a look at the Admin Panel. Login and add an [App](https://admin.scillgame.com/apps) if you have not yet done so. Follow the link and hit the button **Add Application**. 

![AdminPanel_AddApp.png](/Documentation/attachments/AdminPanel_AddApp.png)

You might also need to create an [API Key](https://admin.scillgame.com/app-api-keys) for that app as well - here you need to press the **Generate new API Key** button on the linked page. Once done let us quickly have a look at the App’s ID and API Key. You will not need them now, but later you will have to provide your App ID and API Key to the Unreal SDK. You can copy the App ID in the Apps tab by clicking the  Copy icon next to it. The API Key can also be copied in the App API Keys tab with this icon.

![AdminPanel_AddApiKey.png](/Documentation/attachments/AdminPanel_AddApiKey.png)

Now we will [create the challenges](https://developers.4players.io/scill/guides/create-challenges/) that we want to include in our app as well as create a simple [battle pass](https://developers.4players.io/scill/guides/create-battle-pass/) and [leaderboard](https://developers.4players.io/scill/guides/create-leaderboards/). Refer to these links to get a detailed description of how to accomplish that. In our example we track the most kills in a round in the leaderboard and have some achievements, like killing a certain amount of enemies in a round, using a certain amount of items, reaching a certain wave and so on. The player will be rewarded souls for each challenge. The battle pass consists of three levels and each level consists of three challenges that work as an introduction to the game and should produce motivation early in the game. Here we use the Value property to reference an icon for each battle pass level. The game will provide the player with some souls again for beating each battle pass level.

You can test your changes to your application in the [SCILL Playground App](https://playground.scillgame.com/). You can find it either behind the link or in the Apps tab in the actions column's button with the **play icon**. 

![AdminPanel_Playground.png](/Documentation/attachments/AdminPanel_Playground.png)

Here you can communicate with the SCILL API on behalf of a defined user. Explore the challenges, leaderboards and battle passes you just created and send according events to see if everything is configured correctly. 

This is a rough overview of the Scill API - again, if you need more detailed information look at their extensive documentation and getting started guide. Now we want to have a deeper look at the Unreal SDK and how that works.

## Unreal SDK Overview

You can have a look at the built example in [SCILL's Github repositories](https://github.com/scillgame/scill-unreal-examples). Download it and open the project. We have already added the SDK properly here to show where the needed assets should go. Before starting anything in your own project, again make sure to enable the Scill Plugin in the Plugins dialog of the Unreal Editor. Go to **Edit**->**Plugins** and search for **SCILL SDK** and enable it.

![ScillSDK_Plugin.png](/Documentation/attachments/ScillSDK_Plugin.png)

Generally the SDK consists of 2 Actor Components, an Interface and several UI Widgets. You can see them in the SCILL SDK Content - in the Content Browser of the Unreal Editor click on the **Folder Icon** next to the display of the current folder's path. Here you can jump to the Content folders of your activated plugins.

![ScillClasses.png](/Documentation/attachments/ScillClasses.png)

![ToScillContent.png](/Documentation/attachments/ToScillContent.png)

One Actor Component, the [Scill Client](/documentation/reference.md#scillclient-component), is best added to the [Player Controller](https://docs.unrealengine.com/4.27/en-US/InteractiveExperiences/Framework/Controller/PlayerController/) as it resides on both the Game Server and Client, the other Component, which is the [Scill Client Backend](/documentation/reference.md#scillclientbackend-component), is best added to the [Game Mode](https://docs.unrealengine.com/4.27/en-US/InteractiveExperiences/Framework/GameMode/) so that it is only present on the Game Server. Lastly we should implement the [Scill Level Persistence Interface](/documentation/reference.md#level-persistency-interface) in the [Game Instance](https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Engine/UGameInstance/).

## Implementation notes

SCILL relies on a Server-Client structure of your game. While you do not need to have an Unreal server, you should really consider using any kind of Dedicated Game Server, so that you do not have to ship your App’s API Key with your Game Client to your users. The API Key is mainly used to retrieve an access token for a user and pass that to the Client. Other cases are to send SCILL events with verified meta data and retrieve updates about challenges and leaderboards and trigger the respective game events, like claiming a reward for a completed challenge. So while it is completely viable to create an [Unreal Game Server](https://docs.unrealengine.com/4.27/en-US/InteractiveExperiences/Networking/Server/), you could also use a small HTTP API on a secure Server that takes the Client’s Username and requests an Access Token on their behalf and receives the updates to initiate the proper events in your game. In that case we do not need to care about running an Unreal Server and we can just use the Scill Client Actor Component, which then only lives on the Game Client. If you are going for the Unreal Server method, we need the Scill Client Backend component, for this example we will go that way although we have a Single Player game and you will more likely have a dedicated Unreal Server on Multiplayer games.

## Scill Actor Components

The [Scill Client Backend](/documentation/reference.md#scillclientbackend-component) component holds all functions that should only be accessible for the Game Server. It can be used to [retrieve an Access token](/documentation/reference.md#generate-access-token) for a specified user or [send an event](/documentation/reference.md#send-scill-event). Another important function is the **Set API Key** function. Since you do not want to package the API Key in your game, you should make it accessible to your Unreal Server only and read it during the Runtime of your server’s unreal game. Then you can set the api key without having to make it accessible to your users. Surely the packaged unreal content is encrypted - but no encryption is 100% secure.

![ScillClientBackend.png](/Documentation/attachments/ScillClientBackend.png)

The [Scill Client](/documentation/reference.md#scillclient-component) component holds all functions that are needed to get information about your app's current state in the scope of the current player and send actions on their behalf. In this component you will need to set the generated access token from the Scill Client Backend Component.

![ScillClient.png](/Documentation/attachments/ScillClient.png)

Once that is done you can retrieve the status of [challenges](/documentation/reference.md#challenge), [battle passes](/documentation/reference.md#battle-pass) and [leaderboards](/documentation/reference.md#leaderboard-v2-results) activate, unlock or cancel challenges and battle passes, or claim their rewards. Additionally you can provide SCILL with player data, like a player name and an icon that is used in the leaderboards. Also you can start realtime updates on this component. You might want to do this on both, the Game Client and Game Server. The client will use the updates to adjust shown UI and the server will use it to trigger game events based on claimed rewards of challenges. 

Note that almost all functions of these two components use callback events or functions. This is because the calls are asynchonous and the time needed for requests from the SDK to the Scill HTTP API is not predictable to the SDK. Once a response is received the referenced callback will be executed, while the game can run normally in the meantime.

## Scill Level Persistence Interface

Lastly we have the [Scill Level Persistence Interface](/documentation/reference.md#level-persistency-interface). This should be implemented by the Game Instance of your game because it will only be present on your game’s client and is not destroyed when changing levels - unlike player controller or game mode. This is used to keep the user id and access token persistent between levels during the runtime. While most other objects are destroyed upon unloading a level, the game instance stays alive and thus has these properties unchanged in the next level.

![ScillPersistenceInterface.png](/Documentation/attachments/ScillPersistenceInterface.png)

In the next chapter we will [Implement the Unreal SDK on your Game Client](/Documentation/Guides/3_GameClientGuide.md).
