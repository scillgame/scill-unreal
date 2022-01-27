# Implementing the SDK on your Game Client

The other parts of this guide:

- Part 1: [Getting Started with SCILL and Unreal](/Documentation/Guides/1_GettingStartedGuide.md)
- Part 2: [SCILL API and Unreal SDK Overview](/Documentation/Guides/2_ScillApiOverviewGuide.md)
- Part 4: [Implementing the Unreal SDK on your Game Server](/Documentation/Guides/4_GameServerGuide.md)
- Part 5: [Authenticating your Player](/Documentation/Guides/5_AuthenticatingYourPlayerGuide.md)

Now that we have an overview of the SDK in general we can start and open the Unreal Project. We will need to add the components and interfaces to your projects like discussed in the last section. To keep the project a little bit cleaner we will just inherit from the existing Game Mode and Player Controller blueprints and then add the corresponding components to the inherited classes. Go to the blueprints folder and add a new folder for our Scill specific blueprints. Call it for example Scill_Sample or what you like. Inside the new folder you can right-click and hit **Blueprint Class**. In the upcoming dialog expand the **All Classes** tree view and search for the BP_PlayerController Class and select it. Give the new blueprint a name like BP_ScillPlayerController and repeat these steps for the BP_GameMode and BP_GameInstance classes.

![CreatePlayerController.png](/Documentation/attachments/CreatePlayerController.png)

## Preparing the Game Mode

In order to pass an access token to the client, like discussed in the previous chapter, we will first need to create the according method on the Backend component. Since an access token is required to access the Scill API at all from the client, we will do that first. So now we open the newly created Scill Game Mode blueprint and add the [Scill Client Backend Component](/documentation/reference.md#scillclientbackend-component) here. For testing you might also already copy and paste the API Key of your App to the Api Key property of this component - but as already mentioned, during production you would rather like this at a protected location only accessible to the Game Server and load it during Runtime. But for us the property is just okay to use. 

![SetApiKey.png](/Documentation/attachments/SetApiKey.png)

Now we create a function on the Game Mode that takes a String - the User Id - and calls the Generate Access token method on the Scill Client Backend. To do so you can click the **+** button in the top right of the functions list in the Blueprint Window of the Game Mode.

![CreateFunction.png](/Documentation/attachments/CreateFunction.png)

In order to properly handle the response we need to also pass a reference to a function that handles the incoming response from the Scill API. The Backend component is used only to provide the API Key and does not need to do anything with the response - so we can let the Game Client handle the response. Drag and drop the red delegate input from the Generate Access Token function on the input node to create a matching delegate input here. That’s it for now and we can finally switch over to the Scill Player Controller.

![GenerateAccessTokenFunction.png](/Documentation/attachments/GenerateAccessTokenFunction.png)

## Implementing the Scill Client Component

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

## Implementing the Scill Level Persistence Interface

Now this is all fine as long as we do not switch the level at any time and our player controller consequently gets destroyed. To get rid of that problem we will implement the Level Persistence Interface on our custom Game Instance now. Open the blueprint. Go to the Class Settings and add the **Scill Level Persistence Interface** to it. 

![ClassSettings.png](/Documentation/attachments/ClassSettings.png)

![AddInterface.png](/Documentation/attachments/AddInterface.png)

Here you want to add two string instance variables: UserId and AccessToken. Then go to the Interfaces and double click or right-click each of the methods to create a corresponding event or function. 

![GameInstanceMembers.png](/Documentation/attachments/GameInstanceMembers.png)

Set or get the corresponding instance variable and you are done. 

![SetUserId.png](/Documentation/attachments/SetUserId.png)

![GetUserId.png](/Documentation/attachments/GetUserId.png)

What the SDK does in the background is the following: the Scill Client component on startup searches for the Game Instance and tries to cast it to the Level Persistence Interface. If successful, it tries to read the User Id and Access Token to set it on its own instance variables. If there are none, nothing is set and the defaults are used instead. Also if you use the **Set Access Token** or **Set User Id** accessors on the Scill Client the client tries to set these on the game instance in the same way. So after implementing these interfaces you do not need to care about this logic anymore.

## Implementing the Scill Widgets

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

This is all we need to do to integrate the UI Presets in your game - and as you can see, everything that you need to program yourself has to do with how you want to handle the UI in your specific game. Now we can test everything and see if it all works in conjunction with everything else. In the next chapter we will talk about [Implementing the Unreal SDK on your Game Server](/Documentation/Guides/4_GameServerGuide.md).