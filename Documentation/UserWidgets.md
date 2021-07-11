# Scill SDK User Widgets Presets

This page gives you insight into how to setup the built-in User Widgets and gives starting points on how to change them to your liking.

## Remarks

- These Widgets show case the implementation of the Scill API into your Unreal Project. While most of the logic can be re-used in most of the use-cases, there is no guarantee that the widgets cover all use-cases of the API.
- You can use any of the Blueprint Widgets in your Blueprint Classes directly or you can inherit your own classes from them. Additionally these Blueprint Widgets are inherited from C++-Classes that take care of the business logic - like polling and distributing the needed data. You can also derive your own classes from these - either in Blueprints or in C++.
- Since these classes are part of the plugin, they can be found in the `ScillSDK Content` folder of your project after the plugin was enabled. This folder can be accessed via the tree view in the Content Browser or via the button that is highlighted in the image below.

![SwitchToScillSDKContent.png](/Documentation/attachments/SwitchToScillSDKContent.png)

## Getting Started with the Blueprint Widgets

To use the Blueprint Widgets you only need to add one of the `[...]Canvas` Widgets to the Viewport anywhere needed. For them to function properly you will need to add the [Scill Client Component](/Documentation/Blueprints#scill-client-component). to the Player Controller of your game client and use proper values for the App Id and User Id. Once setup, the widgets generate a reference to the Scill Client Component automatically and use it for all needed requests to the Scill API.

[AddToViewport.png](/Documentation/attachments/AddToViewport.png)

Classes that can be added to the viewport directly are:

- **Scill Battle Pass Canvas**
- **Scill Leaderboard Canvas**
- **Scill Personal Challenges Canvas**

### Scill Battle Pass Canvas

This Canvas creates UI to interact with the Battle Passes of your Scill app in the role of a specific user. This Canvas by default shows the first found Battle Pass in your app that is visible to the user. Change the `Battle Pass Id` field on the Widget object before adding it to the Viewport in order to change to a different Battle Pass.

If you use this canvas as a child of some other class that is taking care of the business logic make sure to disable the `Get Battle Pass From Api`field.

### Scill Leaderboard Canvas

This Canvas creates UI to interact with the Leaderboards of your Scill app in the role of a specific user. This Canvas by default shows the first found Leaderboard in your app. Change the `Leaderboard Index`field on the Widget object before adding it to the Viewport in order to change to a different Leaderboard.

This widget also holds a configurator for the User Data (which is used in leaderboards). This allows for changing the User Name and the Avatar of the logged in User.

If you use this canvas as a child of some other class that is taking care of the business logic make sure to disable the `Get Leaderboards From Api` field.

### Scill Personal Challenges Canvas

This Canvas creates UI to interact with the Personal Challenges of your Scill app in the role of a specific user. This Canvas by default shows the first found Personal Challenges Category in your app. Change the `Challenge Category Slug`field on the Widget object before adding it to the Viewport in order to change to the Challenge Category with the specified Slug or Id.

If you use this canvas as a child of some other class that is taking care of the business logic make sure to disable the `Get Challenges From Api`field.

## Creating your own sub-classes in Blueprints

In order to create your own look you can either inherit from any of the provided Blueprint Widget Classes in the `ScillSDK Content/Widgets` folder. Or you can directly inherit from the C++ Classes inside the plugin - they are contained in the `ScillSDK C++ Classes/ScillSDK/Public/Widgets` folder.

While inheriting you can use the hints in the compilation results to create widgets that are then bound to the corresponding Properties of the base widgets and their visuals are set automatically when querying the corresponding data. Of course you can also just change the look of the existing blueprints if that is easier.

## Creating your own sub-classes in C++

Instead of working with blueprints you can also create widgets in C++ - although this is a lot less intuitive without Unreal Editor's Widget Editor. After setting up your game's module to include the Plugin's classes you can inherit from any of the Widgets. Then you can build your Widgets like you are used to and still use the already existing business logic inside the provided example Widgets. Just include the corresponding header files by:

`#include "Widgets/[DesiredUserWidget].h`

Then you can create instances of your derived C++ Widget Classes inside your other C++ Classes.