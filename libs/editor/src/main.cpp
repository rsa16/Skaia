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
#include <iomanip>
#undef main

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
	Skaia::GameApplication* game = new Skaia::GameApplication(&coordinator, "Farming Sim", 1920, 1080, true);
	SDL_Renderer* pr = game->GetRenderer();

	coordinator.RegisterComponent<MenuAnimation>();

	// pre game init
	game->TrackSystem<CustomSystem>();
	game->TrackSystem<MenuSystem>();
	game->SetCounterOn();

	Skaia::Entity bg = coordinator.CreateEntity();
	coordinator.AddComponent<Components::Transform>(bg,
		Components::Transform {
			.x = 0,
			.y = 0,
			.width = 1920,
			.height = 1080
		});

	Skaia::Imaging::Texture tx(pr);
	tx.LoadFile("data/images/background.png");

	coordinator.AddComponent<Components::Sprite>(bg,
		Components::Sprite {
			.tex = &tx,
			.color = { -1, -1, -1, 0.0f }
		});

	coordinator.AddComponent<MenuAnimation>(bg,
		MenuAnimation {
			.speed = 5
		});

	// make our player
	Skaia::Entity rect = coordinator.CreateEntity();
	coordinator.AddComponent<Components::Transform>(rect, // give our player position
		Components::Transform {
			.x = (1920 / 2) - (100 / 2),
			.y = (1080 / 2) - (100 / 2),
			.width = 100,
			.height = 100
		});
		
	coordinator.AddComponent<Components::Sprite>(rect, // give our player shape
		Components::Sprite {
			.color = { 0, 255, 255, 0.0f}
		});

	coordinator.AddComponent<Components::Input>(rect, Components::Input{}); // and let us figure out its input
	coordinator.AddComponent<MenuAnimation>(rect,
		MenuAnimation {
			.speed = 5
		});

	game->Start();
	return 0;
}