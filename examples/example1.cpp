/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.
  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

// Include the necessary components and game application class
#include "GameApplication.h"
#include "components/Transform.h"
#include "components/Sprite.h"

// Global coordinator at the core of engine
// must be used
SkaiaCore::Coordinator coordinator;

// just to let our system only operate on the player
struct Player {
    std::string playerName;
};

// this custom system controls movement for players
// must publicly inherit SkaiaCore::System
class CustomSystem : public SkaiaCore::System {
private:
    // all systems must have a coordinator, otherwise engine will trigger error
	SkaiaCore::Coordinator* coordinator;

public:
	CustomSystem(SkaiaCore::Coordinator* c) {
        // the constructor must take a pointer to the coordinator
		coordinator = c;

        // the system's signature is the components that the system will operate on
        // the entity must have at least these components
        // behind the scenes this just a bitset
		Signature signature;
		signature.set(coordinator->GetComponentType<S_Input>());
		signature.set(coordinator->GetComponentType<S_Transform>());
        signature.set(coordinator->GetComponentType<Player>());
		coordinator->SetSystemSignature<CustomSystem>(signature);
	};

    // you'll get an error about an abstract class if these methods are not defined
    // however you can simmply leave the empty if they are not needed
	void Initialize(void* data = nullptr) override {};
	void Render() override {};
	void Cleanup() override {};

    // the update function happens before render
    // the input system is much like unity where UP is a specific key
    // here we are using wasd keys as default in our engine
	void Update() override {
        // this is for demonstrational purposes however we know for a fact
        // that the system will onlu ever operate on one entity
		for (auto const& entity : mEntities)
		{
            // get the entity's input and transform
			auto& entityInputComp = coordinator->GetComponent<S_Input>(entity);
			auto& entityS_Transform = coordinator->GetComponent<S_Transform>(entity);

            // adjust transform based on input
			if (entityInputComp.DOWN_PRESSED) {
				entityS_Transform.y += 10.0;
			}
			
			if (entityInputComp.UP_PRESSED) {
				entityS_Transform.y -= 10.0;
			}
			
			if (entityInputComp.LEFT_PRESSED) {
				entityS_Transform.x -= 10.0;
			}
			
			if (entityInputComp.RIGHT_PRESSED) {
				entityS_Transform.x += 10.0;
			}
		}
	};
};

int main(int argc, char* argv[])
{
    // S_GameApplication takes a pointer to the coordinator, a title, and the window size
    // whether its a pointer is up to preference
	S_GameApplication* game = new S_GameApplication(&coordinator, "Example Application", 500, 600);

    // Register our player component
    coordinator.RegisterComponent<Player>();

    // Make sure the game actually uses our system
	game->TrackSystem<CustomSystem>();
	
	// initialize the game (just calls the init method of all other systems)
	game->Initialize();
	
    // Entities are just ids with no data, however
    // the core performs tracking of components and entities in the background
	S_Entity rect = coordinator.CreateEntity();
    
    // AddComponent is on the coordinator instead of the entity
    // for performance reasons, since this is ECS components are just structs so we define them here
	coordinator.AddComponent<S_Transform>(rect, 
		S_Transform {
			.x = (500 / 2) - (100 / 2),
			.y = (600 / 2) - (100 / 2),
			.width = 100,
			.height = 100
		}); // put rectangle in center of screen and give it a width and height of 100
		
	coordinator.AddComponent<S_Sprite>(rect, 
		S_Sprite {
			.color = { 0, 255, 255 }
		}); // get a light bluish sort of color

	coordinator.AddComponent<S_Input>(rect, S_Input{}); // to let our system know the currently pressed keys
    coordinator.AddComponent<Player>(rect,
        Player {
            .playerName = "basically useless right now"
        }); // add player component so if we add another entity wih a transform, a sprite, and an input the system wont operate on it

	game->Start(); // start the game loop
	return 0;
}