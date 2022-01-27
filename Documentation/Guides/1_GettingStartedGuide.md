# Getting Started with SCILL and Unreal

This document will give you a quick introduction to the **Unreal SDK of SCILL** - it will guide you through setting up an account and implementing the SDK in your Unreal Project. In the end you will have a very basic setup and can send your first gameplay events to the scill backend and display challenges, battle passes and leaderboards of your player.

![GettingStartedTitle.png](/Documentation/attachments/GettingStartedTitle.png)

SCILL is a gamification service that manages the logic behind battle passes, challenges and achievements and leaderboards. Effectively you just need to send events with appropriate metadata to the SCILL backend to track the relevant information about your players and then poll the states of the achievements or leaderboards.

This guide is heavily based on the Tutorial Series on how to integrate the Unreal SDK of SCILL which can be found [here](https://www.youtube.com/watch?v=6oLQEylIhMg&list=PL6Hjbq3t2BfYm7Z51Pi5HkK2Z1n042dWK).

The other parts of this guide:

- Part 2: [SCILL API and Unreal SDK Overview](/Documentation/Guides/2_ScillApiOverviewGuide.md)
- Part 3: [Implementing the Unreal SDK on your Game Client](/Documentation/Guides/3_GameClientGuide.md)
- Part 4: [Implementing the Unreal SDK on your Game Server](/Documentation/Guides/4_GameServerGuide.md)
- Part 5: [Authenticating your Player](/Documentation/Guides/5_AuthenticatingYourPlayerGuide.md)

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

In the next chapter we will have a look at the [SCILL API and Unreal SDK in General](/Documentation/Guides/2_ScillApiOverviewGuide.md).
