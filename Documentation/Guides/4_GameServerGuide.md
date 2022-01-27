# Implementing the SDK on your Game Server

The other parts of this guide:

- Part 1: [Getting Started with SCILL and Unreal](/Documentation/Guides/1_GettingStartedGuide.md)
- Part 2: [SCILL API and Unreal SDK Overview](/Documentation/Guides/2_ScillApiOverviewGuide.md)
- Part 3: [Implementing the Unreal SDK on your Game Client](/Documentation/Guides/3_GameClientGuide.md)
- Part 5: [Authenticating your Player](/Documentation/Guides/5_AuthenticatingYourPlayerGuide.md)

## Sending Events

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

## Implementing a User Id and Session Id

So now we need to make up a User Id. Of course you would rather use the User Id that you have associated with the player in your game’s backend. For this tutorial we want to use a Unique Id that we can create without having to program a custom backend first and that is still unique to the machine that this game is played on: [Get Device Id](https://docs.unrealengine.com/4.26/en-US/BlueprintAPI/Utilities/Platform/GetDeviceId/). This unique device id stays consistent over several play sessions and so is a perfect fit for our case. Next we need to take care of the Session Id. Each playthrough has to have a unique identifier as well - so we can surely use a [GUID](https://de.wikipedia.org/wiki/Globally_Unique_Identifier) - a Globally Unique Id and just store it in the game mode. We want to generate a new GUID each time the game starts. The Game Mode has an event for that again that we can overwrite: the **Start Game** event. Add it to the Scill Game Mode, call the parent event and then generate a [New Guid](https://docs.unrealengine.com/4.26/en-US/BlueprintAPI/Guid/NewGuid/), cast it to a string and promote it to an instance variable called **SessionId**. 

![CreateSessionId.png](/Documentation/attachments/CreateSessionId.png)

We can now use this in our **Send Events** function at the end of the game and bind it to our event's metadata.

![SendEventsInGameMode.png](/Documentation/attachments/SendEventsInGameMode.png)

This is all we need to do to send events at appropriate moments to the SCILL API. The workflow with placing everything related to that in the Game Mode is just a recommended practice, but there might be other ways that fit better into your specific game, so you really do not have to follow these steps 100% accurately. Also if there are events that you want to send at different points in time, e.g. immediately after the player triggers it - you can simply adjust to that in your custom Event Dispatcher’s handlers.

## Implementing Real-Time Updates

This should be enough for now on Scill Events. We still have one last topic to take a look at: Handling changes on the challenges, e.g. to reward players. The [Receive Realtime Updates](/Documentation/Reference.md#real-time-updates) functions live on the Scill Client component - the component we have placed on the Player Controller. So instead of handling this on the Game Mode we will make sure to handle it on the Server Side of each Player Controller. Of course we can also add a Scill Client component to the game mode just to handle the updates - but it will need to have the user’s Access Token nevertheless and as long as we are on the Game Server we can safely manipulate the game state.

Since we looked at the **kill-enemy** event in this tutorial, let us have a look at the Personal Challenge that is using that event name to track the player’s progress: Kill a certain amount of enemies in one play session. Once completed we will reward the player with 150 souls that he can spend on unlocking weapons or skills permanently for all following runs. You can use this same procedure for personal challenges, for battle passes and leaderboards. In the **Begin Play** event of the Scill Player Controller we need to add a check whether we are on the Game Server or Client by adding a **Switch Has Authority** node. If we are on the Game Server (i.e. we have authority) we can add a call to **On Realtime Connection Open** on the Scill Client. Again, you need to drag off the **On Connection Established** pin to create a matching function that is called once we can start to receive real-time updates. You can create a custom event here and then put a call to **Receive Challenge Updates** after it. This callback can be an event again or a function that is called each time a challenge of the current player has changed. We will implement such a function soon.

![StartRealtimeUpdates.png](/Documentation/attachments/StartRealtimeUpdates.png)

### Getting the Player's Access Token on the Game Server

First we need to handle something we did not handle earlier: when you try to run this you might notice that you cannot subscribe to the challenge updates - this is because your player controller on the server currently does not save the access token we generated earlier. Go to the function of our Player Controller that we have created back then that handles the response on the Server Side and calls the Client’s **Set Access Token Event**. Here we want to set the Access Token property of the Scill Client on our Server as well.

![OnReceiveAccessTokenServer.png](/Documentation/attachments/OnReceiveAccessTokenServer.png)

### Handling the Challenge Updates

Now head back to the Function that handles our Challenge Updates. We want to reward the player the correct amount of souls, once he completes a challenge. So we just need to check if we receive a challenge update of a now “finished” challenge that was previously either “unclaimed” or “in-progress”. This change indicates that the challenge had just been completed successfully and the reward was claimed afterwards. We can do this by checking against the type property of the new and old challenges like shown in the image below. If that is the case we can now reward the player with his earned souls. In the challenges we have created for this project we have used the challenge **Reward Type** *Coin* to indicate that we want to reward souls and the **Challenge Reward** to indicate how many souls. So check if the reward type is coin and then cast the reward to an integer and add it to your player controller’s souls count. The result can also be seen in the image. For other Reward Types you can make other code paths with different handlings - like adding items to the player's inventory with a specific id. Adding souls in this sample project is not properly handled for a server-client setup, so we would have to make slight adjustments to the code to make this work in our scenario - e.g. replicate the add souls function to the client. But this is specific to your game and how you handle your player’s inventory and other stats. Sometimes it might be enough to just start replicating an instance variable of a blueprint.

![ReceiveChallengeUpdate.png](/Documentation/attachments/ReceiveChallengeUpdate.png)

So now when we start the game we can see that not only we can keep track of our challenges, battle passes and the leaderboard, but we can also kill enemies to create high scores in the leaderboard and complete the corresponding challenges. Now all you have to do is to repeat the tracking and sending of gameplay events in a similar way to support all challenges, battle passes and leaderboards of your game properly. Also you can download the finished sample project, where we have a lot of cases that are slightly different from the discussed ones but might still be worth looking at. In the last chapter of this guide we will have a look at how to [Authenticate your Players](/Documentation/Guides/5_AuthenticatingYourPlayerGuide.md).