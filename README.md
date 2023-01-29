# Skaia Engine
A general-purpose, ECS-driven (Entity Component System), 2d game engine created by a single individual with no particular goal. The engine is flexible and can be powerful if used correctly however is not reccomended for use of actual development over engines such as Unity and Godot. The engine was created for learning purposes.

This project is currently in development and is not useable whatsoever. Until the project reaches its alpha stages (a point where its even somewhat useable), please do not submit pull requests. Currently, Skaia compiles on Windows and Linux with slight hitches, documented in the Building From Source section. While it should compile on Mac as well, I have no way to test whether it works or not, as I do not have a MacBook or a virtual machine of one in possession.

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
```
$ git clone https://github.com/rsa16/Skaia
$ cd Skaia
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


## File Structure
```
├───build
├───bin
├───cmake
├───docs
├───examples
├───external
│   ├───sdl
│   └───sdl_image
└───libs
    ├───editor
    │   ├───docs
    │   └───src
    ├───engine
    │   ├───docs
    │   ├───src
    │   └───bin
    └───ght
        └───docs
```
- `build` is for build files
- `docs` is for documentation, which we don't have yet.
- `examples` is for examples on how to use the engine correctly, which we have not implmented
- `bin`is where all executable files will be placed
- `external` is the location of all our third party submodules
- `libs`our subprojects, editor, engine, and the game header tool
