# Skaia Engine
A general-purpose, ECS-driven (Entity Component System), 2d game engine created by a single individual with no particular goal. The engine is flexible and can be powerful if used correctly however is not reccomended for use of actual development over engines such as Unity and Godot. The engine was created for learning purposes.

This project is currently in development and is not useable whatsoever. Until the project reaches its alpha stages (a point where its even somewhat useable), please do not submit pull requests or attempt to build it (refer to "Building From Source" for an exception). I'm not even sure if cmake is going to work properly on other systems.

*This project adheres to the Pitchfork File Structure guide lines described [here](https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs)*

## Features
Most of these features are not implemented yet but we are planning to add them.
### Barebone
- A rendering engine (SDL)
- Math utilities
- Physics Engine (maybe integrate Box2d?)
- Game loop (update, render, that kinda thing)
- Input System
- Debug System

### Core
- Audio System
- Level System
- Animation
- File System
- Camera
- Basic Meshes
- Textures
- Collisions

### Extras
- Network
- Localization
- Memory Management
- Cinematics

## Building From Source
The project uses cmake (because its more or less the standard build system generator) for building. The project builds just like any other cmake project.

*Unfortunately, I have not been able to build for linux or mac at the moment as I have specifically specified the engine to use `__declspec(dllexport)`. When I find time, I will add linux support as I have my own laptop to test with, however at the moment this project is only available for windows. If you want to contribute to this part in particular, I am open to pull requests.*
```
$ mkdir build
$ cd build
$ cmake ..
```
Then we build.
```
$ cmake --build . --config Release
## OR ##
$ cmake -- build . --config Debug
```
