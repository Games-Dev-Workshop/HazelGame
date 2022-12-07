# Hazel Game 

Looking to develop a game using the Hazel engine as part of the games dev workshop. Probably based one of the Pitches from the pitch section on Teams. 

## Getting Started 

The Hazel developers recommend Visual Studio 2017 or 2019, Hazel is officially untested on other development environments their focus on a Windows build. I'll try and add Linux/Mac build instructions where possible. Updated Windows instructions follow (based on the original ones from https://github.com/TheCherno/Hazel)

<ins>**1. Downloading the repository:**</ins>

Start by cloning the repository with `git clone --recursive https://github.com/Games-Dev-Workshop/HazelGame`.

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.

*Edit:* If using ```gh``` on the commandline then ```gh repo clone Games-Dev-Workshop/HazelGame -- --recurse-submodules```

<ins>**2. Configuring the dependencies:**</ins>

1. Run the [Setup.bat](https://github.com/TheCherno/Hazel/blob/master/scripts/Setup.bat) file found in `scripts` folder. This will download the required prerequisites for the project if they are not present yet.
2. One prerequisite is the Vulkan SDK. If it is not installed, the script will execute the `VulkanSDK.exe` file, and will prompt the user to install the SDK.
3. After installation, run the [Setup.bat](https://github.com/TheCherno/Hazel/blob/master/scripts/Setup.bat) file again. If the Vulkan SDK is installed properly, it will then download the Vulkan SDK Debug libraries. (This may take a longer amount of time)
4. After downloading and unzipping the files, the [Win-GenProjects.bat](https://github.com/TheCherno/Hazel/blob/master/scripts/Win-GenProjects.bat) script file will get executed automatically, which will then generate a Visual Studio solution file for user's usage.

If changes are made, or if you want to regenerate project files, rerun the [Win-GenProjects.bat](https://github.com/TheCherno/Hazel/blob/master/scripts/Win-GenProjects.bat) script file found in `scripts` folder.

## GDD 

### Overview 

The game premise is based on an episode of [Red Dwarf](https://en.wikipedia.org/wiki/The_Beginning_(Red_Dwarf)) in the space battle scene the unarmed hero ship moves between enemy vessels and once they have fired uses a device which changes the ships hull to allow objects to pass though it.  The game will be two dimensional and contain a number of randomly generated levels of increasing difficulty. 

This has some simularity to [Ikaruga](https://en.wikipedia.org/wiki/Ikaruga) see video [here](https://www.youtube.com/watch?v=SDsrVrQlWuY), but is less complicated. 

### Player Mechanics

The player can move, in two dimensions and turn off collision detection on the ship allowing objects pass though. The player ship is not able to fire.

### NPC Mechanics

Aim to surround player and fire a projectile. 

### Levels

These will be procedurally generated, there will be a number of NPC ships ... perhaps something else to make it more interseting?


#### Hazel Engine [![License](https://img.shields.io/github/license/TheCherno/Hazel.svg)](https://github.com/TheCherno/Hazel/blob/master/LICENSE)

