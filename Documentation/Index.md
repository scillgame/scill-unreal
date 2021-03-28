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

##### Cancel Personal Challenge

Cancels an active personal challenge by id. This stops tracking changes coming from events.

<!-- Function Image -->

**Inputs:**

- Challenge Id: String. Id of the challenge to be cancelled. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Challenge: [Challenge](#challenge). the cancelled challenge

##### Claim Personal Challenge Reward

Claims the Reward of a completed personal challenge. Once claimed the challenge may be activated again if it is defined as repeatable.

<!-- Function Image -->

**Inputs:**

- Challenge Id: String. Id of the challenge to be claimed. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Challenge: [Challenge](#challenge). the claimed challenge.

##### Get Active Personal Challenges

Retrieves a list of all active personal challenges. I.e. a list of all challenges that are currently tracking changes from events.

<!-- Function Image -->

**Inputs:**

_none_

**Callback Signature:**

- ChallengeCategories: [ChallengeCategory[]](#challenge-category). an array of challenge categories containing all active personal challenges.

##### Get All Personal Challenges

Retrieves a list of all personal challenges.

<!-- Function Image -->

**Inputs:**

_none_

**Callback Signature:**

- ChallengeCategories: [ChallengeCategory[]](#challenge-category). an array of challenge categories containing all personal challenges.

##### Get Personal Challenges

Retrieves a list of uncompleted personal challenges.

<!-- Function Image -->

**Inputs:**

_none_

**Callback Signature:**

- ChallengeCategories: [ChallengeCategory[]](#challenge-category). an array of challenge categories containing all uncompleted personal challenges.

##### Get Unresolved Personal Challenges

Retrieves a list of unfinished personal challenges.

<!-- Function Image -->

**Inputs:**

_none_

**Callback Signature:**

- ChallengeCategories: [ChallengeCategory[]](#challenge-category). an array of challenge categories containing all unfinished personal challenges.

##### Get Personal Challenge By Id

Retrieves a specific personal challenge by id.

<!-- Function Image -->

**Inputs:**

- Challenge Id: String. Id of the challenge to be retrieved. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Challenge: [Challenge](#challenge). the retrieved challenge

##### Unlock Personal Challenge

Unlocks a specific personal challenge by id.

<!-- Function Image -->

**Inputs:**

- Challenge Id: String. Id of the challenge to be unlocked. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Challenge: [Challenge](#challenge). the retrieved challenge

#### Battle Passes

#### Real-time Updates

### ScillClientBackend Component

#### Events

#### Generate Access Token

#### Api Key Handling & Security

### Level Persistency Interface

### Unreal Structures
