# Classes, Components and Structs reference

This document provides you with an overview of all Classes, Components and Structs inside this plugin.

## Plugin Code Structure

While the plugin's code basically consists of three parts, only one of it is important to the user: 

1. The Scill Blueprint Classes - these expose the API to Unreal Engine's Blueprint system and thus give easy access to the Scill Rest API.  You can use the same functions of the Blueprint Classes in the C++ code of your game without problems.

The other two parts of the code are:

1. ScillApiWrapper - this is code generated using the [OpenAPI UE4 Generator](https://openapi-generator.tech/). The Plugin uses this code to easily maintain changes to the Scill API. 
2. ScillHelpers - currently only a very rudimentary MQTT Client resides in this folder. It wraps Scill's MQTT Server to enable real-time updates.

![PluginStructure.png](/Documentation/attachments/PluginStructure.png)

The next sections describe the Blueprint Classes and how to use them in your project.

This documentation contains a reference of Blueprint functions, most of which accept a binding to a delegate as input. While technically inputs, these are not listed as such in the functions' references. Instead the _signatures of these callbacks_ are listed, as this explains their specific usage a lot better.

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
- **Is Unlocked Incrementally**: bool. Indicates if one level after the other must be activated or if users can activate whichever level they want. Typically battle passes are unlocked level by level, but if battle passes are used for other applications (like user referal programs) it can be useful to set this to false.
- **Is Active**: bool. Indicated if this battle pass is currently active.
- **Unlocked At**: String. The date in iso format when the user unlocked this Battle Pass.
- **Can Purchase With Money/Coins**: bool. Indicates that this Battle Pass can be purchased via in-app purchase or with SCILL Coins respectively. This can be set in the Admin Panel.

#### Battle Pass Level

This is the representation of a battle pass level. A battle pass normally consists of multiple levels that each have several challenges. Use the battle pass functions on the [Scill Client](#scillclient-component) to receive details about battle pass levels of a specific battle pass.

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

#### Battle Pass Level Reward

Provides all information about the reward of a battle pass level.

- **Level Id**: String. Unique identifier of the Battle Pass Level.

- **App Id**: String. Unique identifier of the associated App.

- **Battle Pass Id**: String. Unique identifier of the associated Battle Pass.

- **User Id**: String. This is your user id. You can set this to whatever you like, either your real user id or an obfuscated user id. However you need to be consistent here. Events linked to this user id only track if challenges or battle passes are unlocked with the same user id.

- **Level Position Index**: int. Typical usage pattern is to load battle pass levels with getBattlePassLevels operation and store them for rendering. Using this value you can quickly identify the index of the level that changed.

- **Reward Amount**: String. In the Admin Panel you can set different types of rewards. You can also set an identifier of an in-game-item or anything you like. Use this to include the reward into your own business logic.

- **Reward Type Name**: There are different types of rewards available. Possible values are Coins, Voucher, Money and Experience.

#### Battle Pass Challenge State

This represents one state of a battle pass challenge. While very similar to a Battle Pass Challenge there is some additional information about the associated battle pass level, battle pass etc.

- **Level Id**: String. Unique identifier of the Battle Pass Level.

- **App Id**: String. Unique identifier of the associated App.

- **Battle Pass Id**: String. Unique identifier of the associated Battle Pass.

- **User Id**: String. This is your user id. You can set this to whatever you like, either your real user id or an obfuscated user id. However you need to be consistent here. Events linked to this user id only track if challenges or battle passes are unlocked with the same user id.

- **Level Position Index**: int. Typical usage pattern is to load battle pass levels with GetBattlePassLevels operation and store them for rendering. Using this value you can quickly identify the index of the level that changed.

- **Challenge Id**: String. The unique id of this challenge. Every challenge is linked to a product.

- **Challenge Position Index**: int. Same as level_position_index. Use this index to identify the challenge that changed within the levels challenges array. Typical usage pattern is to update the previously stored score and type.

- **Challenge Goal**: int. Indicates how many “tasks” must be completed or done to complete this challenge.

- **User Challenge Current Score**: int. Indicates how many tasks the user already has completed. Use this in combination with challenge_goal to render a nice progress bar.

- **Type**: String. Indicates the status of the challenge. This can be one of the following:
  
  - `unlock`: Challenge does not track anything. 
  
  - `in-progress`: Challenge is active and tracking. 
  
  - `overtime`: User did not manage to finish the challenge in time. 
  
  - `unclaimed`: The challenge has been completed but the reward has not yet been claimed. 
  
  - `finished`: The challenge has been successfully be completed and the reward has been claimed

#### Battle Pass State

This provides most important information about the current state of a battle pass. Get more detailed information with e.g. the Get Battle Pass operations.

- **App Id**: String. Unique identifier of the associated App.

- **Battle Pass Id**: String. Unique identifier of the associated Battle Pass.

- **Battle Pass Priority**: int. The priority of the battle pass. I.e. if multiple are available you can use this field to sort them.

- **StartDate/EndDate**: String. The date (in iso format) when the Battle Pass starts. Tracking begins once this date is passed or stops once the end is reached and users will not be able to progress further than what they have achieved up to that point.

- **Is Active**: bool. Indicated if this battle pass is currently active.

#### Battle Pass Unlock Info

This provides most important information about the process of unlocking a battle pass.

- **Battle Pass Id**: String. Unique identifier of the associated Battle Pass.

- **Purchase Id**: The id of this battle pass purchase

- **User Id**: The id of the associated user

- **Purchase Price**: float. The price paid for this battle pass

- **Purchase Currency**: The currency used to purchase this battle pass

- **Purchased At**: String. The date this battle pass has been purchased 

- **Battle Pass Completed**: bool. Indicates if this battle pass has been completed

#### Battle Pass Changed

Is used to notify about changes on a challenge in a [monitored](#receive-battle-pass-updates) battle pass. 

- **Webhook Type**: String. The type of the notification. If you receive this payload, it's most likely battlepass-challenge-changed

- **Old Battle Pass Challenge**: [Battle Pass Challenge State](#battle-pass-challenge-state). The old state of the battle pass challenge that has updated.

- **New Battle Pass Challenge**:[Battle Pass Challenge State](#battle-pass-challenge-state). The newstate of the battle pass challenge that has updated.

#### Battle Pass Expired

Is used to notify about the expiration of a [monitored](#receive-battle-pass-updates) battle pass.

- **Webhook Type**: String. The type of the notification. If you receive this payload, it's most likely battlepass-challenge-changed

- **Old Battle Pass**: [Battle Pass State](#battle-pass-state). The old state of the battle pass challenge that has updated.

- **New Battle Pass**:[Battle Pass State](#battle-pass-state). The newstate of the battle pass challenge that has updated.

#### Battle Pass Level Claimed

Is used to notify about the claim of a [monitored](#receive-battle-pass-updates) battle pass level's reward. Use this callback on your game server to provide the claiming player with their reward.

- **Webhook Type**: String. The type of the notification. If you receive this payload, it's most likely battlepass-challenge-changed

- **Battle Pass Level Reward**: [Battle Pass Level Reward](#battle-pass-level-reward). The old state of the battle pass challenge that has updated.

#### Challenge

This represents a personal challenge. While similar to a [Battle Pass Level Challenge](#battle-pass-level-challenge) this is a different type of object - as it resides in your app directly (sorted into [Challenge Categories](#challenge-category)) and not in a [Battle Pass Level](#battle-pass-level).

- **Challenge Id**: String. The unique id of this challenge. Every challenge is linked to a product.

- **Challenge Name**: String. The name of the challenge in the language set by the language parameter.

- **Challenge Duration Time**: int. The duration of the challenge in seconds. Challenges auto lock after time-out and need to be unlocked again.

- **Live Date**: String. The date this challenge should start. Use that field to create challenges that start in the future.

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

- **Challenge Price**: int. If you purchase the challenge, you can set a price.

- **Challenge Reward**: String. Set a reward for this challenge. This is a string value that you can map to anything in your code. Use in combination with Challenge Reward Type.

- **Challenge Reward Type**: String. The reward type can be set to various different settings. Use it to implement different reward types on your side and use challenge_reward to set the value or amount of this reward.

- **Challenge Xp**: int. If you have experience, player rankings whatever, you can use this field to set the gain in that when this challenge is rewarded.

- **Repeatable**: bool. If this challenge can be only activated once per user this will be false. Otherwise this challenge will always be added to list of available challenges (see personal or alliance challenges).

- **Is Claimed**: bool. If the challenge reward has been claimed this is true otherwise its false.

- **User Challenge Unlocked At**: String. This is the timestamp the challenge has been unlocked.

- **User Challenge Activated At**: String. This is the timestamp the challenge has been activated.

- **User Challenge Is Claimed**: bool. Indicates if this challenge has been claimed.

- **User Challenge Status**: int. Gives indication in what state the challenge is.

#### Challenge Category

A list of challenges is always represented as a list of several challenge categories. This way you can easily filter and organize challenges to display them properly. E.g. you can have daily challenges, achievements, team challenges etc.

- **Category Slug**: String. A short name without special chars to make it easier to refer to a specific category (in code) that is language and id agnostic.

- **Category Name**: String. The name of the category in the local language set as the query parameter.

- **Category Id**: String. Indicates how many “tasks” must be completed or done to complete this challenge.

- **Is Daily Cateogry**: bool. Indicates if this is the daily category, bringing up new challenges every day for the user to tackle.

- **Category Position**: int. In the admin panel you set the order of the categories. This is the position index and indicates the position within the categories array.

- **Challenges**: [Challenge[]](#challenge). An array of all contained challenge objects.

#### Challenge Changed

This object is returned once a challenge of a [monitoring](#receive-personal-challenge-updates) user has changed. This only has one type currently.

- **Webhook Type**: String. The type of the notification. If you receive this payload, it's most likely battlepass-challenge-changed

- **Category Position**: float. The index of the category this challenge is linked to. When you request personal challenges, you get an array of categories which contain an array of challenges in their challenges property. This value indicates in which category this challenge can be found. Speeds up updating UI as you don't need to iterate through all catagories and challenges to find the challenge.

- **User Token**: String. The access token for the user of that challenge. You can use that user_token to directly send another event and therefore to chain different SCILL pieces together. For example you can send another event driving another challenge or battle pass whenever a user has completed a challenge.

- **Old Challenge**: [Challenge](#challenge). The old state of the personal challenge.

- **New Challenge**: [Challenge](#challenge). The new state of the personal challenge.

#### Leaderboard V2 Results

This object contains information about a leaderboard - like the name and the id, but also contains all rankings, sorted by users and teams.

- **LeaderboardId**: String. The id of the leaderboard.
- **LeaderboardName**: String. The display name of the leaderboard.
- **Leaderboard Results By Member Type**: [Leaderboard V2 Results Leaderboard Results By Member Type](#leaderboard-v2-results-leaderboard-results-by-member-type). Contains a list of leaderboard rankings for all different types of member types - currently users and teams.
- **Leaderboard Sort Order Ascending**: Boolean. If true the order of the results is ascending, if false it is descending.

#### Leaderboard V2 Results Leaderboard Results By Member Type

This object holds arrays for each different type of members in a leaderboard with rankings of these members.

- **User**: [Leaderboard V2 Member Type Ranking](#leaderboard-v2-member-type-ranking). An array of LeaderboardRanking Items for users.
- **Team**: [Leaderboard V2 Member Type Ranking](#leaderboard-v2-member-type-ranking). An array of LeaderboardRanking Items for teams. Provide a team_id in the event payload to also create leaderboards for teams.

#### Leaderboard V2 Member Type Ranking

This object holds a Count and an array of rankings of a specified member type.

- **Count**: int. Number of entries.
- **Members**: [Leaderboard V2 Member[]](#leaderboard-v2-member). A list of members' rankings on the leaderboard.

#### Leaderboard V2 Member

This is the ranking for the user or team in the leaderboard.

- **Member Id**: String. The id of the user or team - its the same user id you used to create the access token and the same team id you used to send the events.
- **Member Type**: String: Indicates what type this entry is, it's either user or team.
- **Score**: int. The score achieved as an integer value. If you want to store floats, for example laptimes you need to convert them into an int before (i.e. multiply by 100 to get hundreds of seconds and format back to float in UI)
- **Rank**: int. The position within the leaderboard.
- **Metadata Results**: [Leaderboard V2 MemberMetadata[]](#leaderboard-v2-member-metadata). Holds a list of found metadata of the member on that leaderboard.
- **Additional Info**: [UserInfo](#user-info). Info about the user.

#### Leaderboard V2 Member Metadata

This is an object holding information about a member on a leaderboard.

- **Key**: String. The event type of the leaderboard.
- **Ranked**: Boolean. Determines if the member is ranked for that event type. If false no score and rank is provided.
- **Score**: int. The achieved score of the member as an integer value.
- **Rank**: int. The rank of the user in the leaderboard.

#### Leaderboard V2 Member Ranking

You get these object if you query the leaderboard ranking for a specific user. Only rankings for the requested user will be returned.

- **Leaderboard Id**: String. The id of the leaderboard this ranking is in.
- **LeaderboardName**: String. The name of the leaderboard.
- **LeaderboardMember**: [Leaderboard V2 Member](#leaderboard-v2-member). Info about the user and their ranking.
- **Sort Order Ascending**: bool. True if this leaderboard sorts the score ascending or false if the ranking is defined by a descending score.

#### Leaderboard V2 Update Payload

The payload used for [realtime updates](#receive-leaderboard-updates) if a leaderboard's ranking is updated.

- **Webhook Type**: String. The type of the webhook, in this case it is leaderboard-ranking-changed.
- **Leaderboard Data**: [Leaderboard V2 Info](#leaderboard-v2-info). Info about the changed leaderboard.
- **Member Data**: [Leaderboard V2 Member](#leaderboard-v2-member). Info about the ranking that has changed.
- **Old Leaderboard Ranking**: [LeaderboardScore](#leaderboard-score). The old score of the user in this leaderboard.
- **New Leaderboard Ranking**: [LeaderboardScore](#leaderboard-score). The new score of the user in this leaderboard.

#### Leaderboard V2 Changed

The payload used for [realtime updates](#receive-leaderboard-updates) if a leaderboard is updated.

- **Webhook Type**: String. The type of the webhook, in this case it is leaderboard-changed.
- **Old Leaderboard**: [Leaderboard V2 Info](#leaderboard-v2-info). Old data of the leaderboard.
- **New Leaderboard**: [Leaderboard V2 Info](#leaderboard-v2-info). New data of the leaderboard.

#### Leaderboard Score

Contains info about rank and score of a member in a leaderboard.

- **Score**: int. The score achieved as an integer value. If you want to store floats, for example laptimes you need to convert them into an int before (i.e. multiply by 100 to get hundreds of seconds and format back to float in UI).
- **Rank**: int. The position within the leaderboard.

#### Leaderboard V2 Info

The Leaderboard Info object contains information about the leaderboard itself like the name and the id.

- **App Id**: String. The id of the app.
- **Leaderboard Id**: String. The id of the leaderboard.
- **LeaderboardName**: String. The display name of the leaderboard.
- **Event Type**: String. The event type that triggers this leaderboard.
- **Sort Order Ascending**: bool. True if this leaderboard sorts the score ascending or false if the ranking is defined by a descending score.

#### User Info

Can be any object that is attached to the user. You can set these values in the user service. For example you can provide a user name and an avatar image url.

- **Username**: String. The user name of the user.
- **Avatar Image**: String. The name or URL of an avatar image for a user.

#### Event Meta Data Base

This class holds all information about an event that you send to the SCILLAPI. An event is created in your game server and then sent to the SCILL Event API to update all currently active challenges, that this event is relevant to. Use one of the many classes derived from Event Meta Data Base to create the correct metadata payload for each event type. See the [Scill Event Reference](https://developers.4players.io/scill/events/#available-events) for more information about the different event types.

Some of the integer inputs of an Event Meta Data are optional - since blueprints do not support optional pins, you have to make sure to set the corresponding boolean of an optional input to true.

![Event.png](/Documentation/attachments/Event.png)

- **User Id**: String. This is your user id. You can set this to whatever you like, either your real user id or an obfuscated user id. However you need to be consistent here. Events linked to this user id only track if challenges or battle passes are unlocked with the same user id.

- **Session Id**: String. This is required if event_type is single and identifies a session. This can be anything used to group events together. For example this can be a level or a match id.

- **Event Type**: String. This is either single or group. You can send multiple events in one request (group) or send events in sequence. Please note, that depending on your tier you might run into rate limits.

- A number of **Strings** and **Integer Numbers** that are specific to each kind of event.

#### Scill Event Payload (deprecated)

Use this struct to create the payload for sending an event to the SCILL Api. An Event is created on the server and then sent to the SCILL Event Api to update any currently active challenges.

- **User Id**: String. This is your user id. You can set this to whatever you like, either your real user id or an obfuscated user id. However you need to be consistent here. Events linked to this user id only track if challenges or battle passes are unlocked with the same user id.

- **Session Id**: String. This is required if event_type is single and identifies a session. This can be anything used to group events together. For example this can be a level or a match id.

- **Event Name**: String. This is the event type as a string. These have predefined event names for many games and applications. It’s wise to use those as this allows us to analyse data and help you balancing your application or game.

- **Event Type**: String. This is either single or group. You can send multiple events in one request (group) or send events in sequence. Please note, that depending on your tier you might run into rate limits.

- **Meta Data**: [Event Meta Data](#event-meta-data). This is the meta data of the event, describing what exactly happened in the game.

#### Event Meta Data (deprecated)

Use this struct to tell the SCILL Api what exactly happened in your game so that it can properly update any related challenges. Simply set those fields of the struct that are interesting for your type of event (defined in the [Scill Event Payload](#scill-event-payload)). You can safely ignore all other fields.

- **Action Object**: String. The object that is the source of the action

- **Action Subject**: String. The object that is the target of the action

- **Action Type**: String. The name of the action

- **Ammo Used**: int. Number of ammonition used

- **Amount**: int. A general indicator for number of items (i.e. number of kills in kill-enemy event)

- **Amount Gained**: int. The number of ammonition gained

- **Amount Given**: int. The number of amminition given

- **Animal Name**: String. The name of an animal

- **Armor**: int. The health state of the armor.

- **Away Team Id**: String. The id of the opponent team

- **Away Score**: int. The score of the opponent team

- **Battle Status**: int. An integer value indicating the battle status (map it to an enum for example in your code)

- **Bounty Name**: String. The name of the bounty

- **Building Id**: String. The id or name of a building

- **Building Level**: int. The level of the building

- **Card Type**: String. The name of the card

- **Character Name**: String. The name of a character

- **Checkpoint Id**: String. The id/name of a checkpint

- **Coordinate X/Y**: The x/y coordinate in your coordinate system, used for example to store position on a map

- **Crew Name**: String. The name of a crew

- **Damage Amount**: int. The amount of damage

- **Distance**: int. The distance measured in any coordinate system of your choice. Please note: This is an integer field. If you need more precision multiple your floating point value with 1000 or so to keep the precision but storing it as an integer value

- **Duration**: int. The duration in any unit you like

- **Effect Id**: String. The effect id or name

- **Enemy Character**: String. The character type or name of an enemy

- **Enemy Type**: String. The type of an enemy

- **Event Type**: String. The event type

- **Fuel Consumed**: int. The number of fuel consumed

- **Health**. int. The health

- **Hit Type**: String. The type of a hit (i.e. head, torso, leg)

- **Home Team Id**: String. The id or name of your or the home team

- **Home Score**: int. The score of your or the home team

- **Item Id**: String. The id of an item

- **Item Name**: String. The name of an item

- **Item Type**: String. The type of an item

- **Kill Type**: String. The type of a kill

- **Lap Position**: int. The position in a lap

- **Level Id**: String. The id of a level

- **Map Name**: String. The name of a map

- **Map Section Name**: String. The name of a section of a map

- **Mission Id**: String. The mission id

- **Player Character**: String. The name of the player character

- **Puzzle Id**: int. The id of a puzzle

- **Race Position**: int. The position within a race

- **Realm**: String. The realm

- **Required Time**: int. The time required involed in this event. I.e. in a reach-checkpoint event this could be the time in seconds required to reach that checkpoint from the last checkpoint.

- **Resource Gained**: String. The name/id of the resource gained

- **Resource Given**: String. The name/id of the resource given (to someone else)

- **Resource Name**: String. The name of the resource

- **Round Id**: int. The id of the round

- **Round Type**: String. The type of the round

- **Score**: int. The score

- **Stat Type**: String. The type of the stats item

- **Time Condition**: String. The timing condition

- **Transport Id**: String. The id of the transport

- **Type**: String. The name/id of a type.

- **Unit Type**: String. The name/id of a unit type

- **Upgrade Type**: String. The name of the upgrade

- **Weapon Action**: String. The action taken on a weapon (i.e. infrared-activated)

- **Weapon id**: String. The id of the weapon

- **Weapon Type**: String. The type of the weapon

- **Weapon Used**: String. The name/id of a weapon used in a kill or similar event

- **Zone Name**: String. The name of the zone

### Level Persistency Interface

The Level Persistency Interface is best implemented by your `GameInstance`. It holds methods for setting and getting the User Id and Access Token. These will be automatically read by the [ScillClient](#scillclient-component) on load of a level and when you set these on the ScillClient it will communicate this to this interface automatically as well.

Effectively what you need to do is implement this on your Game Instance. Create a new Blueprint somewhere in your Unreal Engine project and derive it from `Game Instance`.

Open it and go the _Class Settings_. Then in the Details Pane you can select to implement this interface on the class. Now, in the Variables Pane, you can right click the interface methods and select to implement corresponding functions or events.

Best practice is to simply create an instance variable for each, the user id and access token, and just set or read them on the respective methods.

![GameInstance.png](/Documentation/attachments/GameInstance.png)

### ScillClient Component

This component should be added to your game's custom `PlayerController`. It handles all requests that the client of your game has. Since it lives on the client installed on the player's device, it only polls the state of Scill challenges, battle passes etc.

![ScillClientComponent.png](/Documentation/attachments/ScillClientComponent.png)

#### Variables

The Scill Client retains the User Id, Access Token and App Id for its lifetime. This is normally from loading a level to unloading it (except when you stream levels and thus retain the Player Controller between levels).

Additionally it holds the last queried [User Info](#user-info) object. This eases the access to the additional user info, since the client does not need to start an HTTP request each time the game needs it.

##### User Id and Access Token handling on the Client

Use the Access Token and User Id variables of the Scill Client to read or write them from your Blueprint Graph.

![SetAccessToken.png](/Documentation/attachments/SetAccessToken.png)

The setter and getter functions of the Access Token and User Id also try to set and get these on the current Game Instance. If the client's Game Instance implements the [Level Persistency Interface](#level-persistency-interface) these functions set and get the access token and user id there. This ensures that these values are persistent across levels or lobby menues. If the Game Instance does not implement that interface it simply uses the values present on the Scill Client Component. In that case you need to make sure to share these values across levels yourself.

Note that from C++ code you cannot simply use the respective instance variables but need to use the `GetAccessToken`, `SetAccessToken`, `GetUserId` and `SetUserId` functions instead.

Before calling any other function you should make sure to have an access token ready - this is needed for any other API call. Use the [ScillClientBackend Component's Generate Access Token](#Generate-Access-Token) function for this.

##### App Id

The App Id should not change during game play and thus can be entered as a default value directly in the details pane of the Scill Client Component. Note that this is **not your ApiKey!**

![ScillClientVariables.png](/Documentation/attachments/ScillClientVariables.png)

#### Personal Challenges Functions

The Scill Client provides several functions to access the Personal Challenge of the current User. Before calling any of these functions, make sure to generate an access token using the [ScillClientBackend Component's Generate Access Token](#Generate-Access-Token) function.

##### Activate Personal Challenge

Activate a personal challenge by id. After activating the challenge tracks changes coming from events.

![ActivatePersonalChallenge.png](/Documentation/attachments/ActivatePersonalChallenge.png)

**Inputs:**

- Challenge Id: String. Id of the challenge to be activated. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Challenge: [Challenge](#challenge). The activated challenge
- Success: boolean. whether the Request was processed successfully

##### Cancel Personal Challenge

Cancels an active personal challenge by id. This stops tracking changes coming from events.

![CancelPersonalChallenge.png](/Documentation/attachments/CancelPersonalChallenge.png)

**Inputs:**

- Challenge Id: String. Id of the challenge to be cancelled. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Challenge: [Challenge](#challenge). the cancelled challenge
- Success: boolean. whether the Request was processed successfully

##### Claim Personal Challenge Reward

Claims the Reward of a completed personal challenge. Once claimed the challenge may be activated again if it is defined as repeatable.

![ClaimPersonalChallengeReward.png](/Documentation/attachments/ClaimPersonalChallengeReward.png)

**Inputs:**

- Challenge Id: String. Id of the challenge to be claimed. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Challenge: [Challenge](#challenge). the claimed challenge.
- Success: boolean. whether the Request was processed successfully

##### Get Active Personal Challenges

Retrieves a list of all active personal challenges. I.e. a list of all challenges that are currently tracking changes from events.

![GetActivePersonalChallenges.png](/Documentation/attachments/GetActivePersonalChallenges.png)

**Inputs:**

_none_

**Callback Signature:**

- ChallengeCategories: [ChallengeCategory[]](#challenge-category). an array of challenge categories containing all active personal challenges.
- Success: boolean. whether the Request was processed successfully

##### Get All Personal Challenges

Retrieves a list of all personal challenges.

![GetAllPersonalChallenges.png](/Documentation/attachments/GetAllPersonalChallenges.png)

**Inputs:**

_none_

**Callback Signature:**

- ChallengeCategories: [ChallengeCategory[]](#challenge-category). an array of challenge categories containing all personal challenges.
- Success: boolean. whether the Request was processed successfully

##### Get Personal Challenges

Retrieves a list of uncompleted personal challenges.

![GetActivePersonalChallenges.png](/Documentation/attachments/GetActivePersonalChallenges.png)

**Inputs:**

_none_

**Callback Signature:**

- ChallengeCategories: [ChallengeCategory[]](#challenge-category). an array of challenge categories containing all uncompleted personal challenges.
- Success: boolean. whether the Request was processed successfully

##### Get Unresolved Personal Challenges

Retrieves a list of unfinished personal challenges.

![GetPersonalChallenges.png](/Documentation/attachments/GetPersonalChallenges.png)

**Inputs:**

_none_

**Callback Signature:**

- ChallengeCategories: [ChallengeCategory[]](#challenge-category). an array of challenge categories containing all unfinished personal challenges.
- Success: boolean. whether the Request was processed successfully

##### Get Personal Challenge By Id

Retrieves a specific personal challenge by id.

![GetPersonalChallengeById.png](/Documentation/attachments/GetPersonalChallengeById.png)

**Inputs:**

- Challenge Id: String. Id of the challenge to be retrieved. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Challenge: [Challenge](#challenge). the retrieved challenge
- Success: boolean. whether the Request was processed successfully

##### Unlock Personal Challenge

Unlocks a specific personal challenge by id. After that it can be activated (if not set to activate automatically).

![UnlockPersonalChallenge.png](/Documentation/attachments/UnlockPersonalChallenge.png)

**Inputs:**

- Challenge Id: String. Id of the challenge to be unlocked. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Challenge: [Challenge](#challenge). the unlocked challenge
- Success: boolean. whether the Request was processed successfully

#### Battle Passes Functions

The Scill Client provides several functions to access the app's battle passes and their challenges. Before calling any of these functions, make sure to generate an access token using the [ScillClientBackend Component's Generate Access Token](#Generate-Access-Token) function.

##### Activate Battle Pass Level

Activates a specific battle pass level by id. It then tracks changes on its challenges.

![ActivateBattlePassLevel.png](/Documentation/attachments/ActivateBattlePassLevel.png)

**Inputs:**

- Level Id: String. Id of the battle pass to be activate. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Success: boolean. whether the request was processed successfully

##### Claim Battle Pass Level

Claims the reward of a specific battle pass level by id. This will then trigger according webhooks so that you can unlock the reward on your game's server.

![ClaimBattlePassLevel.png](/Documentation/attachments/ClaimBattlePassLevel.png)

**Inputs:**

- Level Id: String. Id of the battle pass id to be unlocked. Best retrieved by one of the other functions in this section.

**Callback Signature:**

- Success: boolean. whether the request was processed successfully

##### Get Active Battle Passes

Retrieves all active battle passes associated with this user.

![GetActiveBattlePasses.png](/Documentation/attachments/GetActiveBattlePasses.png)

**Inputs:**

_none_

**Callback Signature:**

- BattlePasses: [BattlePass[]](#battle-pass). an array of all retrieved battle passes.
- Success: boolean. whether the request was processed successfully

##### Get Battle Pass

Retrieves a battle passes specified by id.

![GetBattlePass.png](/Documentation/attachments/GetBattlePass.png)

**Inputs:**

- Battle Pass Id: String. the id of the battle pass to be retrieved.

**Callback Signature:**

- Battle Pass: [BattlePass](#battle-pass). the retrieved battle passes
- Success: boolean. whether the request was processed successfully

##### Get Battle Pass Levels

Retrieves all levels associated with the specified battle pass.

![GetBattlePassLevels.png](/Documentation/attachments/GetBattlePassLevels.png)

**Inputs:**

- Battle Pass Id: String. the id of the battle pass whose levels should be retrieved.

**Callback Signature:**

- Battle Pass Level: [BattlePassLevel[]](#battle-pass-level). the retrieved battle pass levels
- Success: boolean. whether the request was processed successfully

##### Get Battle Passes

Retrieves all battle passes associated with your app.

![GetBattlePasses.png](/Documentation/attachments/GetBattlePasses.png)

**Inputs:**

_none_

**Callback Signature:**

- Battle Passes: [BattlePass[]](#battle-pass). an array of all retrieved battle passes.
- Success: boolean. whether the request was processed successfully

##### Unlock Battle Pass

Unlocks a battle pass for the user. It can then start to activate its levels for challenge tracking.

![UnlockBattlePass.png](/Documentation/attachments/UnlockBattlePass.png)

**Inputs:**

- Battle Pass Id: String. the id of the battle pass to be unlocked.
- Purchase Price: float. the price that the user paid for the battle pass. can be used for statistical purposes.
- Purchase Currency: String. the currency identifier for the purchase. can be used for statistical purposes.

**Callback Signature:**

- Battle Pass Unlock Info: [BattlePass[]](#battle-pass). an array of all retrieved battle passes.
- Success: boolean. whether the request was processed successfully

#### Leaderboard Functions

The Scill Client provides several functions to access the app's leaderboards and their rankings. Before calling any of these functions, make sure to generate an access token using the [ScillClientBackend Component's Generate Access Token](#Generate-Access-Token) function.

##### Get Leaderboard

Provides the current leaderboard rankings for a specific leaderboard.

![GetLeaderboard.png](/Documentation/attachments/GetLeaderboard.png)

**Inputs:**

- Board Id: String. The id of the leaderboard.
- Current Page: CurrentPage. The page index starting at 1. The number of pageSize elements are returned for each page. Default value is 1.
- Page Size: int. The number of elements per page. Default is 25.
- Language: String. Set the language. Content can be translated in the Admin Panel. Values can be international language codes like de, en, fr, it, ...

**Callback Signature:**

- Leaderboard: [Leaderboard](#leaderboard). The returned leaderboard object. Holds all important information of the requested leaderboard.
- Success: boolean. Whether the request was processed successfully.

##### Get Leaderboard Ranking

Returns a LeaderboardMemberRanking item for the specified leaderboard. Use this function to get the position of a user or team in a specified leaderboard.

![GetLeaderboardRanking.png](/Documentation/attachments/GetLeaderboardRanking.png)

**Input:**

- Member Type: String. The member type, can be _user_ or _team_ (right now) and sets which leaderboards should be selected.
- Mebmer Id: String. Either the user_id or team_id you used when sending the events. The memberType flag identifies which one is used.
- Leaderboard Id: String. The id of the leaderboard
- Language: String.Set the language. Content can be translated in the Admin Panel. Values can be international language codes like de, en, fr, it, ...

**Callback Signature:**

- Leaderboard Ranking: [Leaderboard Member Ranking](#leaderboard-member-ranking). The returned Leaderboard Ranking object for the user.
- Success: boolean. Whether the request was processed successfully.

##### Get Leaderboard Rankings

Returns an array of LeaderboardRanking items defined for all leaderboards in the application specified for the user.

![GetLeaderboardRankings.png](/Documentation/attachments/GetLeaderboardRankings.png)

**Inputs:**

- Member Type: String. The member type, can be user or team (right now) and sets which leaderboards should be selected.
- Member Id: String. Either the user_id or team_id you used when sending the events. The memberType flag identifies which one is used.
- Language: String. Set the language. Content can be translated in the Admin Panel. Values can be international language codes like de, en, fr, it, ...

**Callback Signature:**

- Leaderboard Rankings: [Leaderboard Member Ranking[]](#leaderboard-member-ranking). The returned Leaderboard Ranking objects for the user of each leaderboard they are present.
- Success: boolean. Whether the request was processed successfully.

##### Get Leaderboards

Returns an array of Leaderboard items defined for the application.

![GetLeaderboards.png](/Documentation/attachments/GetLeaderboards.png)

**Inputs:**

- Current Page: int. The page index starting at 1. The number of pageSize elements are returned for each page. Default value is 1.
- Page Size: int. The number of elements per page. Default is 25.
- Language: String. Set the language. Content can be translated in the Admin Panel. Values can be international language codes like de, en, fr, it, ...

**Callback Signature:**

- Leaderboards: [Leaderboard[]](#leaderboard). The leaderboard object holding all information necessary to draw it in a widget.
- Success: boolean. Whether the request was processed successfully.

##### Set User Data

Sets user info like username and avatar image which is returned as part of the user rankings in leaderboards.

![SetUserData.png](/Documentation/attachments/SetUserData.png)

**Inputs:**

- User Info: [UserInfo](#user-info). UserInfo object that is to be stored in the SCILL database for the user

**Callback Signature:**

- User Info: [UserInfo](#user-info). The new User Info object.
- Success: boolean. Whether the request was processed successfully.

##### Get User Data

Returns additional info object with usernames and avatar image for a user which is used in the leaderboard system.

![GetUserData.png](/Documentation/attachments/GetUserData.png)

**Inputs:**

_none_

**Callback Signature:**

- User Info: [UserInfo](#user-info). The returned User Info object.
- Success: boolean. Whether the request was processed successfully.

#### Real-time Updates

These functions start monitoring changes to either a specific battle pass, a specific leaderboard or all personal challenges of a user. These can be used either on the game client's side or on the server side to properly process changes and either display them in the client's UI or to react to them in the game play. A popular example for the latter is providing a player with a reward, after the client has called ["Claim Personal Challenge Reward"](#claim-personal-challenge-reward). If your game does not have a server you can of course also react on the game's client.

Since the `PlayerController` and thus also the `ScillClient` live on both the client and the game server, you can start real-time updates on both of them. On the client you can handle anything UI related and on the server you can handle anything game play related then (e.g. paying out a claimed battle pass reward).

##### Receive Battle Pass Updates

Starts monitoring changes to the specified battle pass. Whenever a change occurs, the provided callback is executed. There are three different types of battle pass changes currently: 

- **Battle Pass Challenge Changed** occurs when anything (mostly progress) on a battle pass challenge has changed.
- **Battle Pass Reward Claimed** occurs when the reward of a battle pass has changed. Use this to trigger gameplay events on your server to provide the claiming player with his reward.
- **Battle Pass Expired** occurs once the battle pass is no longer active. This battle pass is not tracking any changes via events anymore.

Unlike the other functions on these classes, the callback function here will be stored permanently and called multiple times instead of once.

![ReceiveBattlePassUpdates.png](/Documentation/attachments/ReceiveBattlePassUpdates.png)

**Inputs:**

- **Battle Pass Id**: String. the id of the battle pass to be unlocked.

**Callback Signature:**

- **Battle Pass Payload Type**: [BattlePassPayloadType](#battle-pass-payload-type). the type of the callback. 
  - 0: Challenge Changed
  - 1: Reward Claimed
  - 2: Expired
- **Battle Pass Changed**: [BattlePassChanged](#battle-pass-changed). if the payload type is Challenge Changed this provides the respective details. otherwise no values are set on this.
- **Battle Pass Level Claimed**: [BattlePassLevelClaimed](#battle-pass-level-claimed). if the payload type is Reward Claimed this provides the respective details. otherwise no values are set on this.
- **Battle Pass Expired**: [BattlePassExpired](#battle-pass-expired). if the payload type is Expired this provides the repsective details. otherwise no values are set on this.

##### Receive Challenge Updates

Starts monitoring changes to all personal challenges of the current user. Whenever a change occurs, the provided callback is executed.

Unlike the other functions on these classes, the callback function here will be stored permanently and called multiple times instead of once.

![ReceiveChallengeUpdates.png](/Documentation/attachments/ReceiveChallengeUpdates.png)

**Inputs:**

_none_

**Callback Signature:**

- Payload: [ChallengeChanged](#challenge-changed). Provides details about how the personal challenge has changed.

##### Receive Leaderboards Updates

Starts monitoring changes to all rankings inside a specified leaderboard. Whenever a change occurs, the provided callback is executed.

Unlike the other functions on these classes, the callback function here will be stored permanently and called multiple times instead of once.

![ReceiveChallengeUpdates.png](/Documentation/attachments/ReceiveChallengeUpdates.png)

**Inputs:**

- Leaderboard Id: String. The leaderboard id of the leaderboard that you want to monitor.

**Callback Signature:**

- UpdatePayload: [LeaderboardV2UpdatePayload](#leaderboard-v2-update-payload). Provides details about what has changed in the leaderboard rankings.
- ChangedPayload: [LeaderboardV2Changed](#leaderboard-v2-changed). Provides details about what has changed in the leaderboard.

##### On Realtime Connection Open

Waits for the Realtime Update Connection to open and then executes the callback function. This is used to call the Start Realtime Updates functions only once the underlying connection is ready for subscriptions.

![OnRealtimeConnectionOpen.png](/Documentation/attachments/OnRealtimeConnectionOpen.png)

This function has no input arguments and the callback signature has no arguments as well.

### ScillClientBackend Component

This component should be added to your game's custom `GameMode`. It has authority to send events, generate access tokens and the like. Also, it holds the API Key, so this should not live on your game's client executable. Since the `GameMode` is defined to only reside on the server this is the perfect place. Also make sure to load your API Key during Runtime from a configuration file and do not store it directly in your source code or blueprint assets. Although deployed encrypted to your players, it is not impossible for a user to decrypt your game's assets and thus API Key.

#### Send Event

This can be used to send an event to the SCILL Api that will process the corresponding active challenges and battle passes.

![SendEvent.png](/Documentation/attachments/SendEvent.png)

**Inputs:**

- **Payload**: [Scill Event Payload](#scill-event-payload). This provides all information of the sent event.

**Callback Signature:**

- Success: boolean. whether the request was processed successfully

#### Generate Access Token

Generates an access token. Should be initiated by a client and then, using replication, passed to be processed on the server. Use the callback to pass the access token back to the client. In the [Getting Started Guide](Index/#generate-access-token) you can see an illustration of what the blueprint would look like roughly.

**Inputs:**

- **User Id**: String. The id of the user that you want to generate the access token for.

**Callback Signature:**

- **Token**: String. The generated access token

- Success: boolean. whether the request was processed successfully