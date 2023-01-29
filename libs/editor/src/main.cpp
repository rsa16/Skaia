/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include "GameApplication.h"
#include "components/Transform.h"
#include "components/Sprite.h"

#include "SDL.h"
#include "SDL_Image.h"
#include <sstream>

#ifdef _DEBUG
	#undef main
#endif

SkaiaCore::Coordinator coordinator;

class CustomSystem : public SkaiaCore::System {
private:
	SkaiaCore::Coordinator* coordinator;

public:
	CustomSystem(SkaiaCore::Coordinator* c) {
		coordinator = c;

		Signature signature;
		signature.set(coordinator->GetComponentType<Input>());
		signature.set(coordinator->GetComponentType<Transform>());
		coordinator->SetSystemSignature<CustomSystem>(signature);
	};

	void Initialize(void* data = nullptr) override {};
	void Render() override {};
	void Cleanup() override {};

	void Update() override {
		for (auto const& entity : mEntities)
		{
			auto& entityInputComp = coordinator->GetComponent<Input>(entity);
			auto& entityTransform = coordinator->GetComponent<Transform>(entity);

			if (entityInputComp.DOWN_PRESSED) {
				entityTransform.y += 10.0;
			}
			
			if (entityInputComp.UP_PRESSED) {
				entityTransform.y -= 10.0;
			}
			
			if (entityInputComp.LEFT_PRESSED) {
				entityTransform.x -= 10.0;
			}
			
			if (entityInputComp.RIGHT_PRESSED) {
				entityTransform.x += 10.0;
			}
		}
	};
};

int main(int argc, char* argv[])
{	
	GameApplication* game = new GameApplication(&coordinator, "Farming Sim", 500, 600);

	game->TrackSystem<CustomSystem>();
	
	// initialize the game
	game->Initialize();
	
	Entity rect = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(rect, 
		Transform {
			.x = (500 / 2) - (100 / 2),
			.y = (600 / 2) - (100 / 2),
			.width = 100,
			.height = 100
		});
		
	coordinator.AddComponent<Sprite>(rect, 
		Sprite {
			.color = { 0, 255, 255 }
		});

	coordinator.AddComponent<Input>(rect, Input{});

	game->Start();
	return 0;
}