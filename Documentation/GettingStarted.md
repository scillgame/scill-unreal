# Getting Started with SCILL and Unreal

This document will give you a quick introduction to the **Unreal SDK of SCILL** - it will guide you through setting up an account and implementing the SDK in your Unreal Project. In the end you will have a very basic setup and can send your first gameplay events to the scill backend and display challenges, battle passes and leaderboards of your player.

![GettingStartedTitle.png](/Documentation/attachments/GettingStartedTitle.png)

SCILL is a gamification service that manages the logic behind battle passes, challenges and achievements and leaderboards. Effectively you just need to send events with appropriate metadata to the SCILL backend to track the relevant information about your players and then poll the states of the achievements or leaderboards.

This guide is heavily based on the Tutorial Series on how to integrate the Unreal SDK of SCILL which can be found [here](https://www.youtube.com/watch?v=6oLQEylIhMg&list=PL6Hjbq3t2BfYm7Z51Pi5HkK2Z1n042dWK).

## Setting up our Environment

For this purpose we will have a look at a sample project - the [ActionRPG example](https://docs.unrealengine.com/4.27/en-US/Resources/SampleGames/ARPG/) by Epic Games - to have an easily accessible and prominent starting point for this tutorial. You can download that project directly from the Epic Games Launcher’s “Learning” section. Just scroll down there and select to download the example by clicking the button named **Free**. We will have a look at the project later in this section. In this project we will incorporate any changes that are needed to integrate with the SCILL API to showcase typical applications of SCILL.

For testing and development purposes, SCILL offers a [free test period](https://www.4players.io/4players-scill-engagement-toolkit/) - this is enough for what we need, and upgrading later for a launch or bigger tests of an application introduces no new work. So in order to start, go to the [SCILL homepage](https://www.4players.io/4players-scill-engagement-toolkit/) for developers, and create an account there, choosing the appropriate plan for your purposes and providing your data.

Once done we can start downloading the SCILL SDK for Unreal. You can go to [SCILL's Github](https://github.com/scillgame/scill-unreal) Repository and download the Code here or clone it to your local machine using the usual git workflow. The SDK is an [Unreal Plugin](https://docs.unrealengine.com/4.27/en-US/ProductionPipelines/Plugins/) and will be placed in the Plugins folder of your project. You do not need to build it manually - this is done by the Unreal Build Tool instead once you start the Project anew.

## Related Links and Documentation

This documentation has a [reference](/Documentation/Reference.md) for the used classes and functions available. Additionally you can have a look at the documentation of SCILL in general and the SDK specifically on the [4Players Homepage](https://developers.4players.io/scill/). Here you have resources explaining how the SCILL API exactly works and how you can integrate that in your projects. 

## Introduction to the Action RPG Example by Epic Games

Next we want to have a look at the project that we are working on to get an idea of where we will start to integrate Scill later on. This project is partly written in C++ but we can make all changes that we need in Blueprints - so no need to install any Programming Environment for this Tutorial - other than the Unreal Engine itself.

![ActionRPGExampleOverview.png](/Documentation/attachments/ActionRPGExampleOverview.png)

Once the project is open in the Unreal Editor we can explore the structure a little bit. The default map in the editor contains the whole game already - UI for example: that of the Main Menu or Inventory are simply blended on top of the game’s rendering.

Now let’s start the game to have a look at what it is about. In this sample game the player has to clear as many waves of enemies as they can. For killing an enemy they are rewarded souls that they can then spend on upgrades - either weapons or spells. While attacks only take some time to perform you will need to spend some mana on spells. Lastly you can collect health and mana potions that help you persist during your fights.

There are already some ideas for challenges that do both, introduce players to some aspects of your game and keep them having fun and playing your game. In this example project we will reward the player with souls - but we can implement any reward that we like, for example a new weapon that is only accessible through one of these retention features.

Our leaderboard could be based on the number of kills during a play session and rank the players accordingly to create some rivalry and thus more motivation among the players.

We can implement these ideas fairly easily by adding blueprints at some places in the project. The structure of this project consists mainly of the different visuals of the game elements - so we will not change anything in most of these folders here. The interesting part of the project for us is the Blueprints folder. Here we find the Player Character Class, Player Controller, Game Mode and Game Instance classes that we will need to manipulate in order to access the Scill API with the Unreal SDK. The other folders are indeed not as important to us, as they only hold visual assets, data tables or blueprints of the different Pickups, like Potions, Souls and Weapons.

## Overview of the SCILL API

In this section we will look at both, the SCILL API in general and the Unreal SDK. We will discuss the intended workflows in the Unreal Project and have a look at common problems that you might run into.

So to start this off, we first want to look at SCILL in general. As described earlier, SCILL is a gamification service that you can use to boost your applications’ user motivation and, as a consequence, user retention. SCILL currently offers three types of tools for this: Personal Challenges, Battle Passes and Leaderboards. 

Although they’ve been designed with certain use cases in mind, they are quite generic and can each be used in different ways. 

Personal Challenges provide your users with specific objectives that they can try to fulfill in a given time to receive a certain reward. Personal Challenges can be used to create Daily, Weekly or otherwise repeating challenges, or create Achievements. The detailed life cycle of a Personal Challenge can be looked up in the [SCILL documentation](https://developers.4players.io/scill/api/challenges/#challenge-life-cycle). But generally a Personal Challenge starts in the “unlock” state for each user and, after unlocking, needs to be activated. Then the state of the Challenge is tracked using incoming [events](https://developers.4players.io/scill/api/events/) of your application. If an event matches the tracked event-type, the challenge is adjusted according to the event’s metadata. Once the challenge is completed it turns “unclaimed”, and after the user claims it, it either changes to complete or back to unlock.

![challenge_life_cycle.png](/Documentation/attachments/challenge_life_cycle.png)

[Battle Passes](https://developers.4players.io/scill/api/battlepasses/) work in a similar way, but they embed the challenges in a structure that is inspired by the famous battle passes that are present in many games nowadays. A battle pass consists of several [battle pass levels](https://developers.4players.io/scill/api/battlepasses/#the-battlepasslevel-object), that in turn consist of several [challenges](https://developers.4players.io/scill/api/battlepasses/#the-battlepasslevelchallenge-object). Once all challenges of a battle pass level are completed, the user can claim the battle pass reward. The Life Cycles of battle passes, battle pass levels and their challenges are adjusted accordingly.

Lastly there are [leaderboards](https://developers.4players.io/scill/api/leaderboards-v2/). They encourage users through rivalry. For each leaderboard you can determine which event type should be tracked in which way. Then each player’s score is calculated just the same way as with challenges and the rank is determined accordingly.

### The Scill Admin Panel

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

### Implementation notes

SCILL relies on a Server-Client structure of your game. While you do not need to have an Unreal server, you should really consider using any kind of Dedicated Game Server, so that you do not have to ship your App’s API Key with your Game Client to your users. The API Key is mainly used to retrieve an access token for a user and pass that to the Client. Other cases are to send SCILL events with verified meta data and retrieve updates about challenges and leaderboards and trigger the respective game events, like claiming a reward for a completed challenge. So while it is completely viable to create an [Unreal Game Server](https://docs.unrealengine.com/4.27/en-US/InteractiveExperiences/Networking/Server/), you could also use a small HTTP API on a secure Server that takes the Client’s Username and requests an Access Token on their behalf and receives the updates to initiate the proper events in your game. In that case we do not need to care about running an Unreal Server and we can just use the Scill Client Actor Component, which then only lives on the Game Client. If you are going for the Unreal Server method, we need the Scill Client Backend component, for this example we will go that way although we have a Single Player game and you will more likely have a dedicated Unreal Server on Multiplayer games.

### Scill Actor Components

The [Scill Client Backend](/documentation/reference.md#scillclientbackend-component) component holds all functions that should only be accessible for the Game Server. It can be used to [retrieve an Access token](/documentation/reference.md#generate-access-token) for a specified user or [send an event](/documentation/reference.md#send-scill-event). Another important function is the **Set API Key** function. Since you do not want to package the API Key in your game, you should make it accessible to your Unreal Server only and read it during the Runtime of your server’s unreal game. Then you can set the api key without having to make it accessible to your users. Surely the packaged unreal content is encrypted - but no encryption is 100% secure.

![ScillClientBackend.png](/Documentation/attachments/ScillClientBackend.png)

The [Scill Client](/documentation/reference.md#scillclient-component) component holds all functions that are needed to get information about your app's current state in the scope of the current player and send actions on their behalf. In this component you will need to set the generated access token from the Scill Client Backend Component.

![ScillClient.png](/Documentation/attachments/ScillClient.png)

Once that is done you can retrieve the status of [challenges](/documentation/reference.md#challenge), [battle passes](/documentation/reference.md#battle-pass) and [leaderboards](/documentation/reference.md#leaderboard-v2-results) activate, unlock or cancel challenges and battle passes, or claim their rewards. Additionally you can provide SCILL with player data, like a player name and an icon that is used in the leaderboards. Also you can start realtime updates on this component. You might want to do this on both, the Game Client and Game Server. The client will use the updates to adjust shown UI and the server will use it to trigger game events based on claimed rewards of challenges. 

Note that almost all functions of these two components use callback events or functions. This is because the calls are asynchonous and the time needed for requests from the SDK to the Scill HTTP API is not predictable to the SDK. Once a response is received the referenced callback will be executed, while the game can run normally in the meantime.

### Scill Level Persistence Interface

Lastly we have the [Scill Level Persistence Interface](/documentation/reference.md#level-persistency-interface). This should be implemented by the Game Instance of your game because it will only be present on your game’s client and is not destroyed when changing levels - unlike player controller or game mode. This is used to keep the user id and access token persistent between levels during the runtime. While most other objects are destroyed upon unloading a level, the game instance stays alive and thus has these properties unchanged in the next level.

![ScillPersistenceInterface.png](/Documentation/attachments/ScillPersistenceInterface.png)

## Implementing the SDK on your Game Client

Now that we have an overview of the SDK in general we can start and open the Unreal Project. We will need to add the components and interfaces to your projects like discussed in the last section. To keep the project a little bit cleaner we will just inherit from the existing Game Mode and Player Controller blueprints and then add the corresponding components to the inherited classes. Go to the blueprints folder and add a new folder for our Scill specific blueprints. Call it for example Scill_Sample or what you like. Inside the new folder you can right-click and hit **Blueprint Class**. In the upcoming dialog expand the **All Classes** tree view and search for the BP_PlayerController Class and select it. Give the new blueprint a name like BP_ScillPlayerController and repeat these steps for the BP_GameMode and BP_GameInstance classes.

![CreatePlayerController.png](/Documentation/attachments/CreatePlayerController.png)

### Preparing the Game Mode

In order to pass an access token to the client, like discussed in the previous chapter, we will first need to create the according method on the Backend component. Since an access token is required to access the Scill API at all from the client, we will do that first. So now we open the newly created Scill Game Mode blueprint and add the [Scill Client Backend Component](/documentation/reference.md#scillclientbackend-component) here. For testing you might also already copy and paste the API Key of your App to the Api Key property of this component - but as already mentioned, during production you would rather like this at a protected location only accessible to the Game Server and load it during Runtime. But for us the property is just okay to use. 

![SetApiKey.png](/Documentation/attachments/SetApiKey.png)

Now we create a function on the Game Mode that takes a String - the User Id - and calls the Generate Access token method on the Scill Client Backend. To do so you can click the **+** button in the top right of the functions list in the Blueprint Window of the Game Mode.

![CreateFunction.png](/Documentation/attachments/CreateFunction.png)

In order to properly handle the response we need to also pass a reference to a function that handles the incoming response from the Scill API. The Backend component is used only to provide the API Key and does not need to do anything with the response - so we can let the Game Client handle the response. Drag and drop the red delegate input from the Generate Access Token function on the input node to create a matching delegate input here. That’s it for now and we can finally switch over to the Scill Player Controller.

![GenerateAccessTokenFunction.png](/Documentation/attachments/GenerateAccessTokenFunction.png)

### Implementing the Scill Client Component

Now to understand the Scill Player Controller a little better, you need to remember that both the Game Server and the Owning Game Client have an instance of that class. This is in contrast to the Game Mode, which only exists on the server and not on any of the connected clients. Owning Client also means that the Player Controller only exists on that Game Client that is owning this specific player controller - all player controllers of any other player character only exist on the respective clients.

Now let us start to generate access tokens. Add a Scill Client Component to the Scill Player Controller. Again - for testing purposes - you can add a User Id and your App Id to the properties of the component. Contrary to the API Key, the App ID is safe to share, since it alone will not enable anyone to make changes to your application in any way and can be left as a default value for the component’s property. 

![ScillClientProperties.png](/Documentation/attachments/ScillClientProperties.png)

Next, add a Custom Event to your Event Graph - it will be called **SERVER_GenerateAccessToken**. We use the SERVER prefix to indicate that this event will be executed on the server instance of our player controller. To really do that as well, you will need to adjust the **Replicates** property on this event in the details panel and set it to **Run on Server**. This will call the event on the Server instance if it was called on the owning client. If the event is called on the server it just runs like any non-replicated event. Make the call Reliable since we really need the access token on the client side and do not want to lose the message. Normally only cosmetic replications are set to non-reliable. Reliable means that the engine will check whether or not the event has reached the server and retries the replication if the call got lost somewhere. This takes up performance and should not be done on calls that are made repeatedly and only if the events are crucial to game play.

![ServerReplicationProperties.png](/Documentation/attachments/ServerReplicationProperties.png)

The event is executed on the server and so we now have access to the Game Mode. We can now create the logic to generate an access token by calling the corresponding function on the game mode. To maintain some structure we will capsule that in a function. Create a function that is called something like **Execute Generate Access Token Call**. 

![PlayerControllerServerGenerateAccessToken.png](/Documentation/attachments/PlayerControllerServerGenerateAccessToken.png)

Here we get the Game Mode and get its Scill Client Backend component and if that succeeds we call the Generate Access Token function. Now drag off the delegate of that function, drop anywhere in the graph and select “Create Event” so that we can connect it to a function. In the dropdown you can either select an existing function or event, or we just create a matching one. Conveniently the editor directly jumps into the created function and we can handle the response of the API call here. 

![GenerateAccessTokenCall.png](/Documentation/attachments/GenerateAccessTokenCall.png)

The SDK simply returns the token as a string here and a boolean, indicating whether the request was processed successfully. So we check against that boolean and, if it is set, we need to set the access token property on our Scill Client. But remember that we are still on our Server instance of the player controller at that point. So we need to first pass to an event on the owning client. In the event graph again create a new event that takes a string, call that input access token and set the Replication enumeration to “Run on owning Client” this time. Also tick the reliable flag here again. To stay in the naming convention, call the event something like **CLIENT_SetAccessToken**. CLIENT indicates that it is running on the owning client, if it was called on the Server. 

![CallbackReceiveAccessToken.png](/Documentation/attachments/CallbackReceiveAccessToken.png)

In this event we set the access token on the Scill Client. If needed you can also call the **Retrieve User Info or Set to Default** function on the **Scill Client**. This way you make sure that the user has a default name and image set for their appearance on the leaderboards. Now that we have all necessary functions up, we just need to call them, so return to the begin play event, add the **SERVER_GenerateAccessToken** event, go to the callback function of the **Generate Access Token** call and add the **CLIENT_SetAccessToken** event here and we are done for now.

![ClientSetAccessToken.png](/Documentation/attachments/ClientSetAccessToken.png)

### Implementing the Scill Level Persistence Interface

Now this is all fine as long as we do not switch the level at any time and our player controller consequently gets destroyed. To get rid of that problem we will implement the Level Persistence Interface on our custom Game Instance now. Open the blueprint. Go to the Class Settings and add the **Scill Level Persistence Interface** to it. 

![ClassSettings.png](/Documentation/attachments/ClassSettings.png)

![AddInterface.png](/Documentation/attachments/AddInterface.png)

Here you want to add two string instance variables: UserId and AccessToken. Then go to the Interfaces and double click or right-click each of the methods to create a corresponding event or function. 

![GameInstanceMembers.png](/Documentation/attachments/GameInstanceMembers.png)

Set or get the corresponding instance variable and you are done. 

![SetUserId.png](/Documentation/attachments/SetUserId.png)

![GetUserId.png](/Documentation/attachments/GetUserId.png)

What the SDK does in the background is the following: the Scill Client component on startup searches for the Game Instance and tries to cast it to the Level Persistence Interface. If successful, it tries to read the User Id and Access Token to set it on its own instance variables. If there are none, nothing is set and the defaults are used instead. Also if you use the **Set Access Token** or **Set User Id** accessors on the Scill Client the client tries to set these on the game instance in the same way. So after implementing these interfaces you do not need to care about this logic anymore.

### Implementing the Scill Widgets

For this tutorial we do not need to call any other functions for now. Most of this is done in the UI Presets that we want to implement now. You can either use the classes directly or inherit your own widget blueprints from those classes or just copy and paste the blueprints to your game’s content folders to modify their appearance to your liking. For this tutorial we will leave them as they are.

Create input actions in your project properties that we will use to open the respective menus. In the Editor click on **Edit**, **Project Settings** and then in the **Engine** category on **Input**. Add **Action Mappings** with appropriate names and key bindings. For example we can use the **B**-key for the battle pass canvas, **C** for Challenges and **L** for Leaderboards. 

![InputBindings.png](/Documentation/attachments/InputBindings.png)

Once done you can add an event to your player controller for each input action. We will just create a logic to open and close the corresponding widget. To get the result shown below you will have to follow the next few steps:

![InputButtonsBlueprint.png](/Documentation/attachments/InputButtonsBlueprint.png)

We use an enumeration that is used to indicate the currently open menu. Right click in your Scill Sample folder and create an enumeration, we call it **Scill Menu**. Call its fields **None**, **BattlePass**, **Challenges** and **Leaderboards**. 

![ScillMenuEnum.png](/Documentation/attachments/ScillMenuEnum.png)

Now create an instance variable of that type on the player controller and call it **Current Menu**. We also add a **Scill Menu Reference** instance variable of type UserWidget. 

![PlayerControllerInstanceVariables.png](/Documentation/attachments/PlayerControllerInstanceVariables.png)

Add a function to the player controller and call it something like **Menu Button Pressed**. Pass a Scill Menu enumeration as input. In this function we check against the Current Menu and if they are the same, we just remove the **Scill Menu Reference** object by **Removing it from Parent** and then setting the **Scill Menu** to null - after that we change the Current Menu enumeration to **None**. Next we switch over the enumeration. For each case create a User Widget of the corresponding preset from the SDK. Then set the Scill Menu Reference to the newly created widget and set the enumeration accordingly. We can also add an action for closing all menus. For this we create another path for the **None** case and use that for this input action. 

![ScillMenuFunction1.png](/Documentation/attachments/ScillMenuFunction1.png)

![ScillMenuFunction2.png](/Documentation/attachments/ScillMenuFunction2.png)

This is all we need to do to integrate the UI Presets in your game - and as you can see, everything that you need to program yourself has to do with how you want to handle the UI in your specific game. Now we can test everything and see if it all works in conjunction with everything else.

## Implementing the SDK on your Game Server

### Sending Events

To implement the SDK on your Game Server let us first have a look at how to send events to the Scill API without caring too much about where to best put that in this project. So to test this out just go to the [Scill Game Mode](#preparing-the-game-mode) that we created in the last section. Here you can just drag and drop the [Scill Client Backend Component](/documentation/reference.md#scillclientbackend-component) anywhere in the Graph and drag off its value to place a Send Event node. Just like the client side nodes, this node creates a callback and thus needs to bind a proper event or function that will be called once a response is received. To create an event payload use any one of the many subclasses of the [EventMetaDataBase Class](/Documentation/Reference.md#event-meta-data-base) and use a **Construct Object from Class** node to create an instance of them. The payload of an event consists, besides others, of the **User Id** of the sending user - we can get that from the initiating player id. The session id determines whether or not we restart counting - if we set the session id to a new value, the current count of the event is reset. The Event Type determines how the event is handled in the Scill API. You can either set it to single, so that the scill backend will add the given amount to the corresponding challenges and leaderboards data. When setting it to group, it will instead set the current count to the given amount. This way you can group several events on your own backend and then send the result as a group-event.

![ConstructEvent.png](/Documentation/attachments/ConstructEvent.png)

The rest of the inputs needed for the event consist of a subset of a multitude of properties. Since Unreal Blueprints cannot handle optional values very well you are presented with all possible metadata at once. Remember to set the corresponding “Send X” boolean for any used optional number value. Strings are sorted out automatically if they are empty while numbers need to rely on the corresponding flag in the metadata. Refer to the [Scill Event Documentation](https://developers.4players.io/scill/events/) to get an overview of the different types of events and their properties.

## Good Practices to Collect and Send Events

Let us now have a look at how to handle this best in our game. We remember that we have challenges for killing a certain number of enemies in a single round, using items or specific actions, reaching a certain wave and so on. 

### Event Dispatchers

We want to track all these things in a centralized location before sending the corresponding events to the Scill API. Unreal offers a nice technique to send events to any game object that might track it: [Event Dispatchers](https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/Blueprints/UserGuide/EventDispatcher/). Whenever an interesting event is occuring in your game, the instigator will have to call an event of that centralized tracker. If you need to learn a little about Event Dispatchers you can have a look at the Unreal Engine documentation by Epic Games, they have some pretty good How Tos on that topic.

But in short an event dispatcher can be created on any blueprint to create a type of message that can be sent or received anywhere else in your blueprints. You only have to have a reference to the actor that holds the dispatcher to call all assigned events or assign new events to it.

### Adjusting the Game Mode

The Game Mode again is the perfect place to track all the changes in the game, since it always lives on the server and thus has all gameplay relevant information at hand at any time. It is only accessible from the Game Server but there you can access it from anywhere and also, there is only one instance of the Game Mode at any time. 

So to make it easier to track the different kinds of events, we will create the dispatchers on the Game Mode and then make them accessible to all relevant senders of these events. You can also create an own [Actor Component](https://docs.unrealengine.com/4.27/en-US/Basics/Components/) that handles all of this logic to make the code more re-usable. But for this tutorial we will just stick with putting it in the Game Mode directly. In our Scill Blueprints folder you might also want to create a [Blueprint Function or Macro Library](https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/Blueprints/UserGuide/Types/MacroLibrary/) for all Scill specific global blueprint functions. We could for example create a getter for the Scill Game Mode, that casts the current game mode accordingly before returning it - this will make working with it a little bit easier. 

![CreateFunctionLibrary.png](/Documentation/attachments/CreateFunctionLibrary.png)

![ScillFunction.png](/Documentation/attachments/ScillFunction.png)

In the Scill Game Mode again, for each SCILL-relevant gameplay event we will now create an [Event Dispatcher](https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/Blueprints/UserGuide/EventDispatcher/). Let’s do all this for the kill enemy event as an example so you can apply it to any other event you want to implement in your game.

![KillEnemyDispatcher.png](/Documentation/attachments/KillEnemyDispatcher.png)

Go to the Event Dispatchers of your Game Mode and add a new one called **Kill Enemy**. Add an integer input to its signature in the details panel called **Amount**. Now drag it into the blueprint right behind the **Parent: Begin Play** node and hit bind from the dropdown menu. Now drag off the Event pin and select “Create Event”. Here you can choose to create a matching function. In this function we will handle the **Kill Enemy** event.

![KillEnemyDispatcherBinding.png](/Documentation/attachments/KillEnemyDispatcherBinding.png)

For this you will need to create an instance variable that keeps track of how many enemies we have killed in the current game. Go to the Game Mode’s instance variables and add an integer called **Enemies Killed Count**. In the Receive Kill Event function add the incoming amount to the **Enemies Killed Count** and save it back to that Instance Variable.

![ReceiveKillEvent.png](/Documentation/attachments/ReceiveKillEvent.png)

### Tracking the Game State

Now in order to call that event we need to find the correct place in the existing blueprints of the sample project. 

![EnemyCharacterLocation.png](/Documentation/attachments/EnemyCharacterLocation.png)

The EnemyCharacter Blueprint has an **OnDeath** Event that occurs once the player defeats the enemy. Here we need to make sure to send an event with the amount of killed enemies to the Game Mode. Just retrieve the game mode with the blueprint function from the library we have created earlier, or get the Game Mode and cast it manually, and call the **Kill Enemy** dispatcher’s event from here.

![CallKillEnemy.png](/Documentation/attachments/CallKillEnemy.png)

### Sending the Event

Now we track the amount of enemies killed in our Game Mode, but we still do not send anything of that to the SCILL API. In the game mode we need to add the sending process at an appropriate point in time. A good dea is to do that once the game is over. This can happen in three ways in this game: The player can time out, because he killed too few enemies. He can lose all his health points or he can defeat all 20 waves. All these are handled in the **On Game Over** Event on the Sample Project’s Game Mode blueprint. So let us overwrite that event in our **Scill Game Mode** blueprint. Right Click anywhere in the event graph, find the Event **On Game Over** entry and click it to add it to the graph. Now Right-Click the node and select **Add call to parent function** and lastly connect the two nodes. Create a function that capsules the logic that is needed to send all the events to the SCILL API that need to be sent at the end of a game. 

![OnGameOver.png](/Documentation/attachments/OnGameOver.png)

For now this is the Kill Enemy event. Place a **Send Event** node from the Scill Client Backend component and drag off the **Response Received** pin to create a matching function - we do not need to do anything really with the response so we just leave it as it is. Then create an **Kill Enemy Meta Data** object. We care about the **User Id** and **Session Id** later on in this section. For now let us put the Event Type “single” in here and add the Meta Data itself. Bind the **Amount** property to our **Enemies Killed Count** instance variable. There are some additional optional values we could send, but we do not need them for our challenges so we can just leave this as it is. If you want to send optional number values just remember to also check the corresponding **Send Value** Flag.

![SendEventsInGameMode1.png](/Documentation/attachments/SendEventsInGameMode1.png)

### Implementing a User Id and Session Id

So now we need to make up a User Id. Of course you would rather use the User Id that you have associated with the player in your game’s backend. For this tutorial we want to use a Unique Id that we can create without having to program a custom backend first and that is still unique to the machine that this game is played on: [Get Device Id](https://docs.unrealengine.com/4.26/en-US/BlueprintAPI/Utilities/Platform/GetDeviceId/). This unique device id stays consistent over several play sessions and so is a perfect fit for our case. Next we need to take care of the Session Id. Each playthrough has to have a unique identifier as well - so we can surely use a [GUID](https://de.wikipedia.org/wiki/Globally_Unique_Identifier) - a Globally Unique Id and just store it in the game mode. We want to generate a new GUID each time the game starts. The Game Mode has an event for that again that we can overwrite: the **Start Game** event. Add it to the Scill Game Mode, call the parent event and then generate a [New Guid](https://docs.unrealengine.com/4.26/en-US/BlueprintAPI/Guid/NewGuid/), cast it to a string and promote it to an instance variable called **SessionId**. 

![CreateSessionId.png](/Documentation/attachments/CreateSessionId.png)

We can now use this in our **Send Events** function at the end of the game and bind it to our event's metadata.

![SendEventsInGameMode.png](/Documentation/attachments/SendEventsInGameMode.png)

This is all we need to do to send events at appropriate moments to the SCILL API. The workflow with placing everything related to that in the Game Mode is just a recommended practice, but there might be other ways that fit better into your specific game, so you really do not have to follow these steps 100% accurately. Also if there are events that you want to send at different points in time, e.g. immediately after the player triggers it - you can simply adjust to that in your custom Event Dispatcher’s handlers.

### Implementing Real-Time Updates

This should be enough for now on Scill Events. We still have one last topic to take a look at: Handling changes on the challenges, e.g. to reward players. The [Receive Realtime Updates](/Documentation/Reference.md#real-time-updates) functions live on the Scill Client component - the component we have placed on the Player Controller. So instead of handling this on the Game Mode we will make sure to handle it on the Server Side of each Player Controller. Of course we can also add a Scill Client component to the game mode just to handle the updates - but it will need to have the user’s Access Token nevertheless and as long as we are on the Game Server we can safely manipulate the game state.

Since we looked at the **kill-enemy** event in this tutorial, let us have a look at the Personal Challenge that is using that event name to track the player’s progress: Kill a certain amount of enemies in one play session. Once completed we will reward the player with 150 souls that he can spend on unlocking weapons or skills permanently for all following runs. You can use this same procedure for personal challenges, for battle passes and leaderboards. In the **Begin Play** event of the Scill Player Controller we need to add a check whether we are on the Game Server or Client by adding a **Switch Has Authority** node. If we are on the Game Server (i.e. we have authority) we can add a call to **On Realtime Connection Open** on the Scill Client. Again, you need to drag off the **On Connection Established** pin to create a matching function that is called once we can start to receive real-time updates. You can create a custom event here and then put a call to **Receive Challenge Updates** after it. This callback can be an event again or a function that is called each time a challenge of the current player has changed. We will implement such a function soon.

![StartRealtimeUpdates.png](/Documentation/attachments/StartRealtimeUpdates.png)

### Getting the Player's Access Token on the Game Server

First we need to handle something we did not handle earlier: when you try to run this you might notice that you cannot subscribe to the challenge updates - this is because your player controller on the server currently does not save the access token we generated earlier. Go to the function of our Player Controller that we have created back then that handles the response on the Server Side and calls the Client’s **Set Access Token Event**. Here we want to set the Access Token property of the Scill Client on our Server as well.

![OnReceiveAccessTokenServer.png](/Documentation/attachments/OnReceiveAccessTokenServer.png)

### Handling the Challenge Updates

Now head back to the Function that handles our Challenge Updates. We want to reward the player the correct amount of souls, once he completes a challenge. So we just need to check if we receive a challenge update of a now “finished” challenge that was previously either “unclaimed” or “in-progress”. This change indicates that the challenge had just been completed successfully and the reward was claimed afterwards. We can do this by checking against the type property of the new and old challenges like shown in the image below. If that is the case we can now reward the player with his earned souls. In the challenges we have created for this project we have used the challenge **Reward Type** *Coin* to indicate that we want to reward souls and the **Challenge Reward** to indicate how many souls. So check if the reward type is coin and then cast the reward to an integer and add it to your player controller’s souls count. The result can also be seen in the image. For other Reward Types you can make other code paths with different handlings - like adding items to the player's inventory with a specific id. Adding souls in this sample project is not properly handled for a server-client setup, so we would have to make slight adjustments to the code to make this work in our scenario - e.g. replicate the add souls function to the client. But this is specific to your game and how you handle your player’s inventory and other stats. Sometimes it might be enough to just start replicating an instance variable of a blueprint.

![ReceiveChallengeUpdate.png](/Documentation/attachments/ReceiveChallengeUpdate.png)

So now when we start the game we can see that not only we can keep track of our challenges, battle passes and the leaderboard, but we can also kill enemies to create high scores in the leaderboard and complete the corresponding challenges. Now all you have to do is to repeat the tracking and sending of gameplay events in a similar way to support all challenges, battle passes and leaderboards of your game properly. Also you can download the finished sample project, where we have a lot of cases that are slightly different from the discussed ones but might still be worth looking at.

## Authenticating your Player

Lastly we want to discuss a proper authentication mechanism of your players. SCILL is not providing an authentication mechanism itself. It expects every request from your users to come with an access token as parameter. That means that you need to implement user authentication yourself and provide every connected user with a token. But this also means that you have the freedom to integrate any authentication with SCILL so that you can build on your current mechanisms.

First, we will have a look at how to authenticate as a user in general with SCILL. Based on this we will take an existing authentication with Valve’s Steamworks SDK and use it to generate an authentication token for your user in a proper way.

In order to test our project you will later need to install the Steam Client on your machine and create a Steam Account if you do not already have one. Both can be done on the [Steam Homepage](https://store.steampowered.com/).

### General SCILL Authentication

The below diagram in the SCILL [developer documentation](https://developers.4players.io/scill/api/authentication/) shows how the SCILL API can be agnostic of your authentication. The Client App waits for a userId or session that it has with your Client Backend and identifies it as a specific user and sends that to the Client Backend. The Client Backend now adds your SCILL App’s API Key and sends both to the Authentication API of SCILL. This returns an access token that you can then send back to your Client App.

![access_token.png](https://developers.4players.io/images/scill/access_token.png)

Before sending the **Generate Access Token** action to the Authentication API, the Client Backend should first check whether the Client App can take actions on behalf of given user. At this point you need to add some logic to your Client App and Client Backend in order to properly authenticate the player.

### Common Authentication Flows

Generally, there are two ways to authenticate a user for a game: use your own self-hosted authentication service - or use an external authentication service.

In self-hosted authentication you can simply let your player send his credentials to your server to check them against your own authentication database. If it matches, the player is authenticated. The check would be done by any trusted source, in most cases your Client Backend. The Client App in return gets a user access token that it can use to authenticate itself at your Client Backend in this session. Only if that token is valid the Client Backend shall send the call  generateAccessToken and receive the accessToken needed to make requests on the SCILL API.

![CustomAuthorization.png](/Documentation/attachments/CustomAuthorization.png)

While this works very well if you own the credentials of your users, this cannot be done if you use an external authentication service like Steam. Steam will need to check three things: if the user can be trusted, but also if your application can be trusted - and if the user has given your application all the permissions that your application requests. So to act on behalf of a Steam User, you will have to also provide an App Id and an API Key for most calls.

![ExternalAuthorization.png](/Documentation/attachments/ExternalAuthorization.png)

### Authenticating a Steam User and Unreal Client

Authenticating a Steam User with your application can be done in several ways. For this tutorial we take advantage of an authentication through the Steam Client on the User’s device. The Unreal Client will act as though it was started by the Steam Client and so it already has a session with the Steam API through the running Steam Client. We use that session to authenticate the Unreal Client with the Steam Service. On our trusted Game Server we can now test if the session is valid and if so, we generate the accessToken for SCILL.

### Steam Online Subsystem

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

### Exposing Online Subsystem Functionality to Blueprints

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

### Add Authentication to your Blueprint Classes

Once we have everything setup, we can finally start adjusting our blueprints. 

Open your SCILL Player Controller and navigate to the event in the event graph that is called on the Game Server to generate an access token.

Here we will add a call to **Is User Logged In** and provide it with the index of the current Player Controller. If this returns true we use the Steam ID of that player to generate the accessToken for SCILL.

![AuthenticationInBlueprints.png](/Documentation/attachments/AuthenticationInBlueprints.png)

### Testing the Authentication

So now to test this code you will need to start your Steam Client and login. Once done you can go to the Play in Editor button in the Unreal Editor, and click the small triangle next to it. Here you choose to play in a Standalone Game. This is necessary because our executable needs to act as if it was started by an authenticated Steam Client. Now once we logged in you will have an access token to the Scill API for the Steam ID that you are logged in with on the Steam Client.

That is all you have to adjust in your blueprints in order to properly test if a user is signed in. You can change the used Online Subsystem implementation to whatever subsystem you would like to use - or you can write your own authentication and just replace the test for the logged in user with a call to your API. 

## Conclusion

This wraps up our getting started guide. You should now have a good idea of how to start working with the SCILL API in your Unreal Engine Project. You can follow our Video Tutorials that this guide is based on. Also have a deeper look at the [SDK's reference](/Documentation/Reference.md) and at the [General SCILL Documentation](https://developers.4players.io/scill/).
