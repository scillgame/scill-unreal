# Scill Unreal Plugin

Our Unreal Plugin offers easy access to the Scill HTTP API for simple requests and to the Scill MQTT Server for real-time updates. These functions enable access to the API from the Unreal Blueprint System. While you can also access these functions from C++ code of your plugin, this documentation focuses on Blueprints. Simply transfer the usage to C++ code (which should be trivial most of the times). The Plugin offers Components and Interfaces that are best added to your Game Mode, Player Controller and Game Instance.

Since this Plugin is completely open source you are welcomed to adjust them to your own needs, extending or changing the classes.

<!-- Headline Image -->

## Source Code

You can find the source code to our Unreal Plugin in our public Github repository: https://github.com/scillgame/scill-unreal. If you encounter any bugs or issues with the Plugin, please let us know in the Issues tab of Github.

If you fix a bug in our code base, please commit your bugfix in a separate branch and create a merge request with a short description what you have fixed. Of course, we will credit you and your game in the changelog and at the start page of our Github repository in this case!

## Installing the Plugin

Installation of the Plugin is fairly easy. Just download the source from our Github repository and copy the content into the `Plugins/ScillSDK` subdirectory of your Project. If not yet present, create any folder needed. 

<!-- Image of folder structure -->

After that you normally only have to open the project and start working. It might be necessary to enable the Plugin under `Edit->Plugins` in the Unreal Editor's menu bar.

<!-- Image of Plugins Window -->

You should not need to compile the source code. If this is not the case you will have to install Visual Studio with the correct workflow modules - refer to Epic Game's documentation about that for more details: https://docs.unrealengine.com/en-US/ProductionPipelines/DevelopmentSetup/VisualStudioSetup/index.html.

## Notes about Working with the Plugin

In order to properly work with this plugin and also ensure security in your game you most likely want to be familiar with the concept of [Game Modes](https://docs.unrealengine.com/en-US/InteractiveExperiences/Framework/GameMode/index.html), [Player Controllers](https://docs.unrealengine.com/en-US/InteractiveExperiences/Framework/Controller/PlayerController/index.html), [Pawns](https://docs.unrealengine.com/en-US/InteractiveExperiences/Framework/Pawn/index.html), [Game Instances](https://docs.unrealengine.com/en-US/InteractiveExperiences/Framework/GameFlow/index.html) and, for multiplayer games, [Networking](https://docs.unrealengine.com/en-US/InteractiveExperiences/Networking/index.html).

Besides these basic concepts in the Unreal Engine also make yourself familiar with the work-wise of the Scill API - this section assumes you have basic knowledge of the API, for a good starting point visit the [Scill Guides](https://developers.scillgame.com/guides/guides-overview.html).

This documentation contains a reference of Blueprint functions, most of which accept a binding to a delegate as input. While technically inputs, these are not listed as such in the functions' references. Instead the _signatures of these callbacks_ are listed, as this explains their specific usage a lot better.

## Plugin Code Structure

While the plugin's code basically consists of three parts, only one of it is important to the user: 

1. The Scill Blueprint Classes - these expose the API to Unreal Engine's Blueprint system and thus give easy access to the Scill Rest API.  You can use the same functions of the Blueprint Classes in the C++ code of your game without problems.

The other two parts of the code are:

1. ScillApiWrapper - this is code generated using the [OpenAPI UE4 Generator](https://openapi-generator.tech/). The Plugin uses this code to easily maintain changes to the Scill API. 
2. ScillHelpers - currently only a very rudimentary MQTT Client resides in this folder. It wraps Scill's MQTT Server to enable real-time updates.

The next sections describe the Blueprint Classes and how to use them in your project.

### Unreal Structures

In this section you can find a list of all used structure types in the unreal plugin. These are all used, mostly to represent responses of all different kinds from the Scill API.

#### Battle Pass

Represents a Battle Pass Object. Holds all meta data of it. Use its ID e.g. to request the details of its levels and challenges.

- **Battle Pass Id**: String. Unique id of this battle pass.
- **App Id**: String. Unique id of the app.
- **Battle Pass Name**: String. The name of the battle bass.
- **Battle Pass Description**: String. The description of the battle bass. You can set that in the Admin Panel and it can also be HTML.
- **Battle Pass Short Description**: String. A short description of the battle bass. You can set that in the Admin Panel and it can also be HTML.
- **Battle Pass Disclaimer**: String. Use this to provide some terms and conditions following along this battle passes purchase.
- **Battle Pass Priority**: int. The priority of the battle pass. I.e. if multiple are available you can use this field to sort them.
- **Package Sku Ios/Android**: String.  If you want to sell Battle Passes you can use this field to trigger in-app purchase products within your mobile app. You can set this value in the Admin Panel. There is one for iOS and one for Android.
- **Image Xs/S/M/L/Xl**: String. Differently sized images. These fields provide names or urls. You can determine the best size distribution yourself and depends on your application or UI.
- **StartDate/EndDate**: String. The date (in iso format) when the Battle Pass starts. Tracking begins once this date is passed or stops once the end is reached and users will not be able to progress further than what they have achieved up to that point.
- **Read More Link**: String. If the Battle Pass costs “money” you may want to route the user to a web site/page, where they can learn more about this battle pass. You can also use this field to route the user inside your application by providing a path or whatever works for you.
- **s Unlocked Incrementally**: bool. Indicates if one level after the other must be activated or if users can activate whichever level they want. Typically battle passes are unlocked level by level, but if battle passes are used for other applications (like user referal programs) it can be useful to set this to false.
- **Is Active**: bool. Indicated if this battle pass is currently active.
- **Unlocked At**: String. The date in iso format when the user unlocked this Battle Pass.
- **Can Purchase With Money/Coins**: bool. Indicates that this Battle Pass can be purchased via in-app purchase or with SCILL Coins respectively. This can be set in the Admin Panel.

#### Battle Pass Level

This is the representation of a battle pass level. A battle pass normally consists of multiple levels that each have several challenges. Use the battle pass functions on the [Scill Client](#scill-client) to receive details about battle pass levels of a specific battle pass.

- **Level Id**: String. Unique identifier of the Battle Pass Level.
- **App Id**: String. Unique identifier of the associated App.
- **Battle Pass Id**: String. Unique identifier of the associated Battle Pass.
- **Reward Amount**: String. In the Admin Panel you can set different types of rewards. You can also set an identifier of an in-game-item or anything you like. Use this to include the reward into your own business logic.
- **Reward Type Name**: String. There are different types of rewards available. Possible values are Coins, Voucher, Money and Experience. This is deprecated in favor of level_reward_type which uses a slug instead of a human readable expression
- **Level Reward Type**: String. The reward type in a machine readable slug. Available values are nothing, coin, experience, item.
- **Level Completed**: bool. Indicates if this level is completed, i.e. all challenges have been completed.
- **Level Priority**: String. Indicates the position of the level.
- **Reward Claimed**: bool. Indicates if this level has already be claimed.
- **Activated At**: String. The date when this level has been activated or emptyif it's not activated.
- **Challenges**: [BattlePassLevelChallenge](#battle-pass-level-challenge). An array of BattlePassLevelChallenge objects. Please note, not all values are available from the challenge object, as battle passes handle the lifecycle of challenges.

#### Battle Pass Level Challenge

Represents Battle Pass Level Challenge. This is usually nested inside a Battle Pass Level. While the nesting Battle Pass Level is active, any changes through events are tracked. This object differs from the Personal Challenge object.

- **Challenge Id**: String. The unique id of this challenge.

- **Challenge Name**: String. The name of the challenge.

- **Challenge Goal**: int. Indicates how many “tasks” must be completed or done to complete this challenge.

- **Challenge Goal Condition**: int. With this you can set the way how the SCILL system approaches the challenges state. 0 means, that the counter of the challenge must be brought above the goal. If this is 1, then the counter must be kept below the goal. This is often useful for challenges that include times, like: Manage the level in under 50 seconds.

- **User Challenge Current Score**: int. Indicates how many tasks the user already has completed. Use this in combination with Challenge Goal to render a nice progress bar.

- **Challenge Icon/HD**: In the admin panel you can set a string representing an image. This can be a URL, but it can also be an image or texture that you have in your games asset database. Can also have an HD variant.

- **Type**: String. Indicates the status of the challenge. This can be one of the following
  
  - `unlock`: Challenge does not track anything.
  
  - `in-progress`: Challenge is active and tracking.
  
  - `overtime`: User did not manage to finish the challenge in time. 
  
  - `unclaimed`: The challenge has been completed but the reward has not yet been claimed. 
  
  - `finished`: The challenge has been successfully be completed and the reward has been claimed

### Level Persistency Interface

### ScillClient Component

This component should be added to your game's custom `PlayerController`. It handles all requests that the client of your game has. Since it lives on the client installed on the player's device, it only polls the state of Scill challenges, battle passes etc.

<!-- Image of Scill Client Component in Player Controller with sample Blueprint class -->

#### Variables

The Scill Client retains the User Id, Access Token and App Id for its lifetime. This is normally from loading a level to unloading it (except when you stream levels and thus retain the Player Controller between levels).

##### User Id and Access Token handling on the Client

Use the Access Token and User Id variables of the Scill Client to read or write them from your Blueprint Graph.

<!-- Image of Access Token Setter and Getter and User Id Setter and Getter -->

The setter and getter functions of the Access Token and User Id also try to set and get these on the current Game Instance. If the client's Game Instance implements the [Level Persistency Interface](#level-persistency-interface) these functions set and get the access token and user id there. This ensures that these values are persistent across levels or lobby menues. If the Game Instance does not implement that interface it simply uses the values present on the Scill Client Component. In that case you need to make sure to share these values across levels yourself.

<!-- Image of Game Instance implementing the Level Persistency Interface -->

Note that from C++ code you cannot simply use the respective instance variables but need to use the `GetAccessToken`, `SetAccessToken`, `GetUserId` and `SetUserId` functions instead.

Before calling any other function you should make sure to have an access token ready - this is needed for any other API call. Use the [ScillClientBackend Component's Generate Access Token](#Generate-Access-Token) function for this.

##### App Id

The App Id should not change during game play and thus can be entered as a default value directly in the details pane of the Scill Client Component. Note that this is **not your ApiKey!**

#### Personal Challenges Functions

The Scill Client provides several functions to access the Personal Challenge of the current User. Before calling any of these functions, make sure to generate an access token using the [ScillClientBackend Component's Generate Access Token](#Generate-Access-Token) function.

##### Activate Personal Challenge

Activate a personal challenge by id. After activating the challenge tracks changes coming from events.

<!-- Function Image -->

**Inputs:**

- Challenge Id: String. Id of the challenge to be activated. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Challenge: [Challenge](#challenge). The activated challenge
- Success: boolean. whether the Request was processed successfully

##### Cancel Personal Challenge

Cancels an active personal challenge by id. This stops tracking changes coming from events.

<!-- Function Image -->

**Inputs:**

- Challenge Id: String. Id of the challenge to be cancelled. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Challenge: [Challenge](#challenge). the cancelled challenge
- Success: boolean. whether the Request was processed successfully

##### Claim Personal Challenge Reward

Claims the Reward of a completed personal challenge. Once claimed the challenge may be activated again if it is defined as repeatable.

<!-- Function Image -->

**Inputs:**

- Challenge Id: String. Id of the challenge to be claimed. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Challenge: [Challenge](#challenge). the claimed challenge.
- Success: boolean. whether the Request was processed successfully

##### Get Active Personal Challenges

Retrieves a list of all active personal challenges. I.e. a list of all challenges that are currently tracking changes from events.

<!-- Function Image -->

**Inputs:**

_none_

**Callback Signature:**

- ChallengeCategories: [ChallengeCategory[]](#challenge-category). an array of challenge categories containing all active personal challenges.
- Success: boolean. whether the Request was processed successfully

##### Get All Personal Challenges

Retrieves a list of all personal challenges.

<!-- Function Image -->

**Inputs:**

_none_

**Callback Signature:**

- ChallengeCategories: [ChallengeCategory[]](#challenge-category). an array of challenge categories containing all personal challenges.
- Success: boolean. whether the Request was processed successfully

##### Get Personal Challenges

Retrieves a list of uncompleted personal challenges.

<!-- Function Image -->

**Inputs:**

_none_

**Callback Signature:**

- ChallengeCategories: [ChallengeCategory[]](#challenge-category). an array of challenge categories containing all uncompleted personal challenges.
- Success: boolean. whether the Request was processed successfully

##### Get Unresolved Personal Challenges

Retrieves a list of unfinished personal challenges.

<!-- Function Image -->

**Inputs:**

_none_

**Callback Signature:**

- ChallengeCategories: [ChallengeCategory[]](#challenge-category). an array of challenge categories containing all unfinished personal challenges.
- Success: boolean. whether the Request was processed successfully

##### Get Personal Challenge By Id

Retrieves a specific personal challenge by id.

<!-- Function Image -->

**Inputs:**

- Challenge Id: String. Id of the challenge to be retrieved. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Challenge: [Challenge](#challenge). the retrieved challenge
- Success: boolean. whether the Request was processed successfully

##### Unlock Personal Challenge

Unlocks a specific personal challenge by id. After that it can be activated (if not set to activate automatically).

<!-- Function Image -->

**Inputs:**

- Challenge Id: String. Id of the challenge to be unlocked. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Challenge: [Challenge](#challenge). the unlocked challenge
- Success: boolean. whether the Request was processed successfully

#### Battle Passes

The Scill Client provides several functions to access the app's battle passes and their challenges. Before calling any of these functions, make sure to generate an access token using the [ScillClientBackend Component's Generate Access Token](#Generate-Access-Token) function.

##### Activate Battle Pass Level

Activates a specific battle pass level by id. It then tracks changes on its challenges.

<!-- Function Image -->

**Inputs:**

- Level Id: String. Id of the battle pass to be activate. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Success: boolean. whether the request was processed successfully

##### Claim Battle Pass Level

Claims the reward of a specific battle pass level by id. This will then trigger according webhooks so that you can unlock the reward on your game's server.

<!-- Function Image -->

**Inputs:**

- Level Id: String. Id of the battle pass id to be unlocked. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Success: boolean. whether the request was processed successfully

##### Get Active Battle Passes

Retrieves all active battle passes associated with this user.

<!-- Function Image -->

**Inputs:**

_none_

**Callback Signature:**

- BattlePasses: [BattlePass[]](#battle-pass). an array of all retrieved battle passes.
- Success: boolean. whether the request was processed successfully

##### Get Battle Pass

Retrieves a battle passes specified by id.

<!-- Function Image -->

**Inputs:**

- Battle Pass Id: String. the id of the battle pass to be retrieved.

**Callback Signature:**

- Battle Pass: [BattlePass](#battle-pass). the retrieved battle passes
- Success: boolean. whether the request was processed successfully

##### Get Battle Pass Levels

Retrieves all levels associated with the specified battle pass.

<!-- Function Image -->

**Inputs:**

- Battle Pass Id: String. the id of the battle pass whose levels should be retrieved.

**Callback Signature:**

- Battle Pass Level: [BattlePassLevel[]](#battle-pass-level). the retrieved battle pass levels
- Success: boolean. whether the request was processed successfully

##### Get Battle Passes

Retrieves all battle passes associated with your app.

<!-- Function Image -->

**Inputs:**

_none_

**Callback Signature:**

- Battle Passes: [BattlePass[]](#battle-pass). an array of all retrieved battle passes.
- Success: boolean. whether the request was processed successfully

##### Unlock Battle Pass

Unlocks a battle pass for the user. It can then start to activate its levels for challenge tracking.

<!-- Function Image -->

**Inputs:**

- Battle Pass Id: String. the id of the battle pass to be unlocked.
- Purchase Price: float. the price that the user paid for the battle pass. can be used for statistical purposes.
- Purchase Currency: String. the currency identifier for the purchase. can be used for statistical purposes.

**Callback Signature:**

- Battle Pass Unlock Info: [BattlePass[]](#battle-pass). an array of all retrieved battle passes.
- Success: boolean. whether the request was processed successfully

#### Real-time Updates

These functions start monitoring changes to either a specific battle pass or all personal challenges of a user. These can be used either on the game client's side or on the server side to properly process changes and either display them in the client's UI or to react to them in the game play. A popular example for the latter is providing a player with a reward, after the client has called ["Claim Personal Challenge Reward"](#claim-personal-challenge-reward). If your game does not have a server you can of course also react on the game's client.

##### Receive Battle Pass Updates

Starts monitoring changes to the specified battle pass. Whenever a change occurs, the provided callback is executed. There are three different types of battle pass changes currently: 

- Battle Pass Challenge Changed occurs when anything (mostly progress) on a battle pass challenge has changed.
- Battle Pass Reward Claimed occurs when the reward of a battle pass has changed. Use this to trigger gameplay events on your server to provide the claiming player with his reward.
- Battle Pass Expired occurs once the battle pass is no longer active. This battle pass is not tracking any changes via events anymore.

Unlike the other functions on these classes, the callback function here will be stored permanently and called multiple times instead of once.

<!-- Function Image -->

**Inputs:**

- Battle Pass Id: String. the id of the battle pass to be unlocked.

**Callback Signature:**

- Battle Pass Payload Type: [BattlePassPayloadType](#battle-pass-payload-type). the type of the callback. 
  - 0: Challenge Changed
  - 1: Reward Claimed
  - 2: Expired
- Battle Pass Changed: [BattlePassChanged](#battle-pass-changed). if the payload type is Challenge Changed this provides the respective details. otherwise no values are set on this.
- Battle Pass Level Claimed: [BattlePassLevelClaimed](#battle-pass-level-claimed). if the payload type is Reward Claimed this provides the respective details. otherwise no values are set on this.
- Battle Pass Expired: [BattlePassExpired](#battle-pass-expired). if the payload type is Expired this provides the repsective details. otherwise no values are set on this.

##### Receive Challenge Updates

Starts monitoring changes to all personal challenges of the current user. Whenever a change occurs, the provided callback is executed.

Unlike the other functions on these classes, the callback function here will be stored permanently and called multiple times instead of once.

<!-- Function Image -->

**Inputs:**

_none_

**Callback Signature:**

- Payload: [ChallengeChanged](#challenge-changed). Provides details about how the personal challenge has changed.

### ScillClientBackend Component

#### Events

#### Generate Access Token

#### Api Key Handling & Security
