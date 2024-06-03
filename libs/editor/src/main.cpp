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
#include "components/Collider.h"
#include "modules/SkaiaImaging.h"

namespace Components = Skaia::Components;

Skaia::Core::Coordinator coordinator;

struct MenuAnimation {
	int speed;
};

struct Player {
	float moveSpeed;
};

struct Rigidbody2D {
	float momentumY = 0.0f;
	float airTimer = 0.0f;
	int posBeforeCollision = 0;
	bool isJumping = false;
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


class PhysicsSystem2D : public Skaia::Core::System {
private:
	Skaia::Core::Coordinator* coordinator;
	float GRAVITY_CONSTANT = 1.5f;
	float originalHeight;

public:
	PhysicsSystem2D(Skaia::Core::Coordinator* c)
	{
		coordinator = c;

		Skaia::Signature signature;

		signature.set(coordinator->GetComponentType<Rigidbody2D>());
		signature.set(coordinator->GetComponentType<Components::Transform>());
		signature.set(coordinator->GetComponentType<Components::Collider>());
		coordinator->SetSystemSignature<PhysicsSystem2D>(signature);
	}
	
	void Initialize(void* data = nullptr) override {
		for (auto& entity : mEntities)
		{
			auto& entityTransform = coordinator->GetComponent<Components::Transform>(entity);
			auto& entityRigid = coordinator->GetComponent<Rigidbody2D>(entity);

			entityRigid.posBeforeCollision = entityTransform.y;
		}

		std::cout << "movement system" << "\n";
	};
	void Render() override {};
	void Cleanup() override {};
	void HandleUserEvent(void* data = nullptr) override {};

	void Update() override {
		for (auto& entity : mEntities)
		{
			auto& entityRigid = coordinator->GetComponent<Rigidbody2D>(entity);
			auto& entityCollider = coordinator->GetComponent<Components::Collider>(entity);
			auto& entityTransform = coordinator->GetComponent<Components::Transform>(entity);

			// vertical displacement equation
			// d = v0t + 1/2(gravity * t^2)
			// momentumY is v0
			// gravity constant is 4 for pixel speed
			// time is the amount of time it takes for him to reach the ground

			auto checkCollision = [&](Skaia::Collision::State state) { 
				bool hasState = (entityCollider.collisions.find(state) != entityCollider.collisions.end());
				if (hasState) return entityCollider.collisions[state]->collisionTag == "ground";
				else return hasState;
			};

			// if (entityRigid.isJumping && (entityRigid.airTimer < 4)) {
			// 	entityRigid.airTimer += 0.06f;
			// } else {
			// 	entityRigid.airTimer = 0;
			// 	entityRigid.isJumping = false;
			// }

			float timeRel = entityRigid.airTimer  * entityRigid.airTimer;
			float currentHeight = (0.5f * GRAVITY_CONSTANT * timeRel) + (entityRigid.momentumY * entityRigid.airTimer) + entityRigid.posBeforeCollision;

			entityTransform.y = currentHeight;
			std::cout << currentHeight << "\n";

			if (!checkCollision(Skaia::Collision::State::ON_TOP) && !checkCollision(Skaia::Collision::State::ON_BOTTOM))
			{
				entityRigid.airTimer += 0.1f;
				std::cout << "nocollsion" << "\n";
			} else {
				entityRigid.airTimer = 0;
				//entityRigid.isJumping = false;
				entityRigid.posBeforeCollision = entityTransform.y;
			}
		}
	};
};

class MovementSystem : public Skaia::Core::System {
private:
	Skaia::Core::Coordinator* coordinator;
	int airTimer;
	bool isJumping = false;


public:
	MovementSystem(Skaia::Core::Coordinator* c)
	{
		coordinator = c;

		Skaia::Signature signature;

		signature.set(coordinator->GetComponentType<Components::Input>());
		signature.set(coordinator->GetComponentType<Components::Transform>());
		signature.set(coordinator->GetComponentType<Components::Collider>());
		signature.set(coordinator->GetComponentType<Player>());
		coordinator->SetSystemSignature<MovementSystem>(signature);
	};

	void Initialize(void* data = nullptr) override {
		std::cout << "movement system" << "\n";
	};
	void Render() override {};
	void Cleanup() override {};
	void HandleUserEvent(void* data = nullptr) override {};

	void Update() override {
		for (auto& entity : mEntities)
		{
			auto& entityTransform = coordinator->GetComponent<Components::Transform>(entity);
			auto& entityInputComp = coordinator->GetComponent<Components::Input>(entity);
			auto& entityRigid = coordinator->GetComponent<Rigidbody2D>(entity);
			auto& entityCollider = coordinator->GetComponent<Components::Collider>(entity);
			auto& player = coordinator->GetComponent<Player>(entity);

			auto checkCollision = [&](Skaia::Collision::State state) { 
				// check if our collider has the state we are checking for
				bool hasState = (entityCollider.collisions.find(state) != entityCollider.collisions.end());
				if (hasState) return entityCollider.collisions[state]->collisionTag == "ground"; // check if it has collided with a ground platform
				else return hasState; // return false
			};
			
			if (entityInputComp.UP_PRESSED) {
				entityRigid.momentumY = -3.0f;
				entityRigid.isJumping = true;

				std::cout << "jump" << "\n";
			}
			
			if (entityInputComp.LEFT_PRESSED) {
				if (!checkCollision(Skaia::Collision::State::ON_LEFT)) {
					entityTransform.x -= player.moveSpeed;
				} 
			}
			
			if (entityInputComp.RIGHT_PRESSED) {
				if (!checkCollision(Skaia::Collision::State::ON_RIGHT)) {
					entityTransform.x += player.moveSpeed;
				}
			}
			
		}
	};
};

Skaia::Entity createPlayer() {
	Skaia::Entity player = coordinator.CreateEntity();

	coordinator.AddComponent<Components::Transform>(player,
		Components::Transform {
			.x = 400,
			.y = 100,

			.width = 32,
			.height = 32
		}
	);

	coordinator.AddComponent<Components::Sprite>(player,
		Components::Sprite {
			.color = { 255 }
		}
	);

	coordinator.AddComponent<Player>(player,
		Player {
			.moveSpeed = 10.0f
		}
	);

	coordinator.AddComponent<Rigidbody2D>(player,
		Rigidbody2D {}
	);

	coordinator.AddComponent<Components::Collider>(player,
		Components::Collider {
			.boundingBox = { -1, -1, -1, -1 }
		}
	);

	coordinator.AddComponent<Components::Input>(player,
		Components::Input {}
	);

	return player;
};

void createPlatforms()
{
	Skaia::Entity platform = coordinator.CreateEntity();

	coordinator.AddComponent<Components::Transform>(platform,
		Components::Transform {
			.x = 300,
			.y = 400,

			.width = 200,
			.height = 30
		}
	);

	coordinator.AddComponent<Components::Sprite>(platform,
		Components::Sprite {
			.color = { 255 }
		}
	);

	coordinator.AddComponent<Components::Collider>(platform,
		Components::Collider {
			.boundingBox = { -1, -1, -1, -1 },
			.collisionTag = "ground"
		}
	);


	Skaia::Entity platform2 = coordinator.CreateEntity();

	coordinator.AddComponent<Components::Transform>(platform2,
		Components::Transform {
			.x = 500,
			.y = 300,

			.width = 30,
			.height = 100
		}
	);

	coordinator.AddComponent<Components::Sprite>(platform2,
		Components::Sprite {
			.color = { 255 }
		}
	);

	coordinator.AddComponent<Components::Collider>(platform2,
		Components::Collider {
			.boundingBox = { -1, -1, -1, -1 },
			.collisionTag = "ground"
		}
	);
};

int main(int argc, char* argv[])
{	
	// Initialize Game Application
	Skaia::GameApplication* game = new Skaia::GameApplication(&coordinator, "MicroMayhem", 800, 550, 1, false);
	SDL_Renderer* pr = game->GetRenderer();

	// Register components
	coordinator.RegisterComponent<MenuAnimation>();
	coordinator.RegisterComponent<Player>();
	coordinator.RegisterComponent<Rigidbody2D>();

	// Register System, turn FPS Counter on
	game->TrackSystem<MenuSystem>();
	game->TrackSystem<MovementSystem>();
	game->TrackSystem<PhysicsSystem2D>();
	game->SetFPSCounterOn();

	// Create Texture and Load Image
	Skaia::Imaging::Texture tx(pr);
	tx.LoadFile("data/images/background.jpg");

	// Set dimensions
	tx.SetWidth(800);
	tx.SetHeight(550);

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

	Skaia::Entity player = createPlayer();

	createPlatforms();

	// // Create level map
	// Skaia::Entity levelMap = coordinator.CreateEntity();

	// coordinator.AddComponent<Components::Map>(levelMap,
	// 	Components::Map {
			
	// 	}
	// );

	// coordinator.AddComponent<Components::Hierarchy>(levelMap,
	// 	Components::Hierarchy {

	// 	}
	// );

	game->Start();
	return 0;
}