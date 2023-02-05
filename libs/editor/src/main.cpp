/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include "GameApplication.h"
#include "components/Transform.h"
#include "components/Sprite.h"
#include "behaviors/SkaiaImaging.h"

#include "SDL.h"
#include "SDL_Image.h"
#include <sstream>
#undef main

SkaiaCore::Coordinator coordinator;

class CustomSystem : public SkaiaCore::System {
private:
	SkaiaCore::Coordinator* coordinator;

public:
	CustomSystem(SkaiaCore::Coordinator* c) {
		coordinator = c;

		Signature signature;
		signature.set(coordinator->GetComponentType<S_Input>());
		signature.set(coordinator->GetComponentType<S_Transform>());
		coordinator->SetSystemSignature<CustomSystem>(signature);
	};

	void Initialize(void* data = nullptr) override {};
	void Render() override {};
	void Cleanup() override {};

	void Update() override {
		
		for (auto const& entity : mEntities)
		{
			auto& entityInputComp = coordinator->GetComponent<S_Input>(entity);
			auto& entityS_Transform = coordinator->GetComponent<S_Transform>(entity);

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
	S_GameApplication* game = new S_GameApplication(&coordinator, "Farming Sim", 500, 600);
	SDL_Renderer* pRenderer = game->GetRenderer();

	game->TrackSystem<CustomSystem>();
	
	// initialize the game
	game->Initialize();

	S_Entity rect = coordinator.CreateEntity();
	coordinator.AddComponent<S_Transform>(rect, 
		S_Transform {
			.x = (500 / 2) - (100 / 2),
			.y = (600 / 2) - (100 / 2),
			.width = 100,
			.height = 100
		});
		
	coordinator.AddComponent<S_Sprite>(rect, 
		S_Sprite {
			.color = { 0, 255, 255 }
		});

	coordinator.AddComponent<S_Input>(rect, S_Input{});

	game->Start();
	return 0;
}