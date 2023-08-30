/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.
  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include "GameApplication.h"
#include "components/Transform.h"
#include "components/Sprite.h"
#include "components/Hierarchy.h"
#include "components/Map.h"
#include "modules/SkaiaImaging.h"

namespace Components = Skaia::Components;

Skaia::Core::Coordinator coordinator;

struct MenuAnimation {
	int speed;
};

class MenuSystem : public Skaia::Core::System {
private:
	Skaia::Core::Coordinator* coordinator;

public:
	MenuSystem(Skaia::Core::Coordinator* c)
	{
		coordinator = c;
		Skaia::Signature signature;
		signature.set(coordinator->GetComponentType<Components::Sprite>());
		signature.set(coordinator->GetComponentType<Components::Transform>());
		signature.set(coordinator->GetComponentType<MenuAnimation>());
		coordinator->SetSystemSignature<MenuSystem>(signature);
	};

	void Initialize(void* data = nullptr) override {
		std::cout << "work pls" << "\n";
	};
	void Render() override {};
	void Cleanup() override {};
	void HandleUserEvent(void* data = nullptr) override {};

	void Update() override {
		for (auto& entity : mEntities)
		{
			auto& entitySprite = coordinator->GetComponent<Components::Sprite>(entity);
			auto& menuAnim = coordinator->GetComponent<MenuAnimation>(entity);

			if (entitySprite.color.a != 1.0f)
			{
				// std::cout << "menu anim speed: " << std::fixed << std::setprecision(3) << (float)(menuAnim.speed / 255.0f) << "\n";
				entitySprite.color.a += menuAnim.speed / 255.0f;
				// std::cout << entitySprite.color.a << "\n";
			}
		}
	};
};

int main(int argc, char* argv[])
{	
	// Initialize Game Application
	Skaia::GameApplication* game = new Skaia::GameApplication(&coordinator, "Farming Sim", 800, 550, false);
	SDL_Renderer* pr = game->GetRenderer();

	// Register components
	coordinator.RegisterComponent<MenuAnimation>();

	// Register System, turn FPS Counter on
	game->TrackSystem<MenuSystem>();
	game->SetFPSCounterOn();

	// Create Texture and Load Image
	Skaia::Imaging::Texture tx(pr);
	tx.LoadFile("data/images/background.jpg");

	// Set dimensions
	tx.SetWidth(800);
	tx.SetHeight(550);


	// Create background
	Skaia::Entity bg = coordinator.CreateEntity();

	// Add Transform component
	coordinator.AddComponent<Components::Transform>(bg,
		Components::Transform {
			.x = 0,
			.y = 0,

			.width = -1,
			.height = -1 // System will automatically change the Transform's width and height 
		}
	);

	// Add Sprite component
	coordinator.AddComponent<Components::Sprite>(bg,
		Components::Sprite {
			.tex = &tx,
			.color = { -1, -1, -1, 0.0f }
		}
	);

	// Give it fade efect
	coordinator.AddComponent<MenuAnimation>(bg,
		MenuAnimation {
			.speed = 5
		}
	);


	// Create level map
	Skaia::Entity levelMap = coordinator.CreateEntity();

	coordinator.AddComponent<Components::Map>(levelMap,
		Components::Map {
			
		}
	);

	coordinator.AddComponent<Components::Hierarchy>(levelMap,
		Components::Hierarchy {

		}
	);

	game->Start();
	return 0;
}