# Sven Internal v3.0.6

Sven Internal is a C++ plugin for [SvenMod](https://github.com/sw1ft747/SvenMod) that provides various cheats and gameplay enhancements for Sven Co-op.

Currently supported version of the game: 5.25

## Attribution

This project is based on [weedgirl68/sevin](https://github.com/weedgirl68/sevin), which is itself a fork of [YMY1666527646/sven_internal](https://github.com/YMY1666527646/sven_internal).

This version includes numerous bug fixes and stability improvements over the original.

## What's Fixed

### ESP
- Fixed box positioning - boxes now correctly span from feet to head instead of drawing below the entity
- Fixed box height calculation for ducking players
- Fixed box sizing for distant entities and items
- Fixed minimum bounds to prevent tiny boxes

### Chams
- Fixed depth buffer corruption during hidden pass - wall-behind entities now correctly show the hidden color
- Added `glDepthMask(GL_FALSE)` during hidden pass to prevent Z-buffer pollution
- Fixed conflict with wallhack's `glDepthRange` settings

### Wallhack
- Fixed transparent walls feature with proper OpenGL alpha blending

### Stability
- Fixed crashes during map changes by re-acquiring bone transform pointers on video init
- Added loading state protection to prevent rendering with invalid pointers
- Fixed bone data corruption by properly clearing on map transitions
- Fixed potential null pointer dereferences across multiple features

### Removed Features
The following unused/broken features were removed to improve stability:
- Skybox replacement (pattern failed on newer game versions)
- Models Manager (pattern failed on newer game versions)
- R_SetupFrame hook (caused initialization errors)
- Tertiary Attack Glitch (pattern failed)
- ex_interp/cl_updaterate patch (pattern failed)

## How to Install

First, if you don't have SvenMod installed, download and install it (see [SvenMod readme](https://github.com/sw1ft747/svenmod)). 

Download the archive `svenint.rar` from [releases](https://github.com/sw1ft747/sven_internal/releases) and place all files from the archive in the root folder of the game. 

Next, add the plugin `sven_internal.dll` to the file `plugins.txt` (see the header `Adding plugins` in SvenMod's [readme](https://github.com/sw1ft747/svenmod)).

## Features

- Menu (key **INSERT** as default)
- Customizable Configs
- ESP (boxes, skeleton, health, armor, distance, name)
- Wallhack (multiple modes including wireframe and transparent walls)
- Glow & Chams (with wall-behind visibility)
- Vectorial Strafer
- Auto Bunnyhop
- Auto Jumpbug
- Fast Run
- Fake Lag
- Color Pulsator
- Speed Hack
- Anti-AFK
- Cam Hack
- Key Spammer
- First-Person Roaming
- Various Visual Hacks (Velometer, Crosshair, etc.)
- Message Spammer
- Custom Vote Popup
- Custom Chat Colors

## Files of Plugin

The plugin uses subfolder `sven_internal` in the root directory of the game.

Path: `../Sven Co-op/sven_internal/`

This folder is used to save the config, load list of players (their Steam64 ID) for **Chat Colors** and load spam tasks for **Message Spammer**.

- Folder `config` contains all config files
- File `chat_colors_players.txt` allows changing nickname colors for specific players
- Folder `message_spammer` is used by **Message Spammer** to load spam tasks

The plugin will also execute `sven_internal.cfg` from `../Sven Co-op/svencoop/` on load.

## Console Variables/Commands

Type in the console: `sm printcvars all ? sc_`

This will print information about each CVar/ConCommand that belongs to the plugin.

## Chat Colors

This feature lets you change the color of player nicknames in chat.

File `chat_colors_players.txt` format: `STEAM64ID : COLOR_NUMBER`

To convert traditional SteamID to Steam64 ID: `sc_steamid_to_steam64id [SteamID]`

There are 6 color slots (0 = rainbow, 1-5 = custom colors configurable in Menu).

Example:
```
76561198819023292 : 0 # rainbow color
76561197962091295 : 5 # custom color slot 5
```

## Message Spammer

Uses `*.txt` files from folder `message_spammer`. Run with: `sc_ms_add <filename>`

Supports keywords: `loop`, `send [message]`, `sleep [delay]`

Example:
```
loop
send stuck
sleep 0.35
send play
sleep 0.35
```

## Building

Requirements:
- Visual Studio 2022 with C++ workload
- Windows SDK

Build using MSBuild:
```
MSBuild sven_internal.sln /p:Configuration=Release /p:Platform=x86
```

## License

MIT License

## Disclaimer

This project is for educational purposes only. Use at your own risk. The authors are not responsible for any consequences of using this software.
