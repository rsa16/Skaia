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

namespace Components = Skaia::Components;

Skaia::Core::Coordinator coordinator;

class CustomSystem : public Skaia::Core::System {
private:
	Skaia::Core::Coordinator* coordinator;

public:
	CustomSystem(Skaia::Core::Coordinator* c) {
		coordinator = c;

		Skaia::Signature signature;
		signature.set(coordinator->GetComponentType<Components::Input>());
		signature.set(coordinator->GetComponentType<Components::Transform>());
		coordinator->SetSystemSignature<CustomSystem>(signature);
	};

	void Initialize(void* data = nullptr) override {};
	void Render() override {};
	void Cleanup() override {};

	void Update() override {
		
		for (auto const& entity : mEntities)
		{
			auto& entityInputComp = coordinator->GetComponent<Components::Input>(entity);
			auto& entityS_Transform = coordinator->GetComponent<Components::Transform>(entity);

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
	Skaia::GameApplication* game = new Skaia::GameApplication(&coordinator, "Farming Sim", 500, 600);

	// pre game init
	game->TrackSystem<CustomSystem>();
	game->SetCounterOn();

	// make our player
	Skaia::Entity rect = coordinator.CreateEntity();
	coordinator.AddComponent<Components::Transform>(rect, // give our player position
		Components::Transform {
			.x = (500 / 2) - (100 / 2),
			.y = (600 / 2) - (100 / 2),
			.width = 100,
			.height = 100
		});
		
	coordinator.AddComponent<Components::Sprite>(rect, // give our player shape
		Components::Sprite {
			.color = { 0, 255, 255 }
		});

	coordinator.AddComponent<Components::Input>(rect, Components::Input{}); // and let us figure out its input

	game->Start();
	return 0;
}