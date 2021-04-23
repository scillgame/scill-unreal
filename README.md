# SCILL Unreal SDK

SCILL gives you the tools to activate, retain and grow your user base in your app or game by bringing you features well known 
in the gaming industry: Gamification. We take care of the services and technology involved so you can focus on your game and content.

This SDK is currently in development. If you are interested in joining our beta test please let us know: support@scillgame.com.

## About SCILL

SCILL is a fully customizable toolkit that enables you to integrate tailored challenges and full-fledged Battle Passes 
to your game, app and website. SCILL connects seamlessly to your user account and payment systems, adding new retention 
and monetization layers within minutes.

Learn more about SCILL here: [https://www.scillgame.com](https://www.scillgame.com).

Developer documentation can be found here: [https://developers.scillgame.com](https://developers.scillgame.com/sdks/csharp.html)



## Documentation

See [here](/Documentation/Index.md) for more information on how to download, install and get started with this plugin. Also you can find a detailed reference for each implemented class and function.

## Working on the Code

In order to start working on the plugin's code you need to add it to any working Unreal Engine 4 Project.
These steps might be in parts specific to Windows 10 systems and Visual Studio 2019:

1. After checking it out, add the plugin code to your Unreal Project's `Plugins/ScillSDK` subdirectory. If not present yet, create any folder needed.
2. Open the Project in the Unreal Editor.
3. Open the Plugin Preferences in the editor's main menu bar `Edit->Plugins` and search for `ScillSDK`to enable it in the list.
4. While it is okay for the project to be a Blueprint-Only project if you just want to use the plugin - it is crucial to make the project a Source Code project.
   1. If this is not the case, you can go to the menu bar's `File->New C++ Class` and follow the upcoming wizatrd's instructions.
5. Right-Click your project's `.uproject`file in the Explorer and click the `Generate Visual Studio project files` entry in the context menu.
6. Open the solution file and you can start working on the plugin's code. In the Solution Explorer it is located in your game's project under `Plugins/ScillSDK`.

### Updating the Generated Code

To generate the base API wrapper code for the Unreal Plugin use the following command in any npm console. For other package managers adjust accordingly.

```
npx @openapitools/openapi-generator-cli generate -i https://raw.githubusercontent.com/scillgame/openapi/main/scill.yaml -g cpp-ue4 --model-name-prefix ScillApi -o <desiredOutputFolder> --additional-properties=unrealModuleName=ScillSDK
```

#### Notes

The current version of the OpenAPI's cpp-ue4 generator is not compatible with UE 4.26. There is a workaround though: you can change all occurences of `TSharedRef<IHttpRequest>` to `FHttpRequestRef`. This wrapper of TSharedRef ensures backwards-compatibility with older UE4 versions as well.

To keep some structure in the Plugin's Code we have moved the generated code into the `ScillApiWrapper` subfolder. So you need to adjust to that as well. Move the Files in the generated `Public` Directory to `Public/ScillApiWrapper`. Do not copy `ScillSDKModule.h` and `ScillSDKModule.cpp`.  Lastly add the `ScillApiWrapper` subfolder to all relevant includes.