/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <SDL.h>
#include "CollisionSystem.h"
#include <iostream>

#ifdef _DEBUG
    #undef main
#endif

namespace Skaia
{
	namespace Systems
	{
		CollisionSystem::CollisionSystem(Skaia::Core::Coordinator *c)
		{
			coordinator = c;

			Signature signature;
            signature.set(coordinator->GetComponentType<Skaia::Components::Transform>());
			signature.set(coordinator->GetComponentType<Skaia::Components::Collider>());
			coordinator->SetSystemSignature<Skaia::Systems::CollisionSystem>(signature);
		}

		void CollisionSystem::Initialize(void *data)
		{
			std::cout << "Collision System Initalized"
					<< "\n";

            for (auto const &entity : mEntities)
			{  
                auto& entityCollider = coordinator->GetComponent<Components::Collider>(entity);
                entityCollider.owner = entity;
            }
		}

		void CollisionSystem::Render()
		{
			// nothing to implement here
		}

		void CollisionSystem::Update()
		{
			for (auto const &entity : mEntities)
			{
                auto& entityCollider = coordinator->GetComponent<Components::Collider>(entity);
                auto& entityTransform = coordinator->GetComponent<Components::Transform>(entity);

                // compare collision box
                Collision::Box previousBox = entityCollider.boundingBox;

                // ugly af code, check if user set a specific point, otherwise calculate it
                entityCollider.boundingBox.left = entityTransform.x;
                entityCollider.boundingBox.top = entityTransform.y;
                entityCollider.boundingBox.right = entityTransform.x + entityTransform.width;
                entityCollider.boundingBox.bottom = entityTransform.y + entityTransform.height;

                // TODO: fix collision for better efficiency
                for (auto const &otherEntity : mEntities)
                {
                    if (entity == otherEntity) { continue; }

                    auto& otherCollider = coordinator->GetComponent<Components::Collider>(otherEntity);
                    auto& otherTransform = coordinator->GetComponent<Components::Transform>(otherEntity);

                    bool colliding = true;

                    // BOUNDING COLLISON LOGIC
                    if (entityCollider.boundingBox.bottom <= otherCollider.boundingBox.top) colliding = false;
                    if (entityCollider.boundingBox.top >= otherCollider.boundingBox.bottom) colliding = false;
                    if (entityCollider.boundingBox.right <= otherCollider.boundingBox.left) colliding = false;
                    if (entityCollider.boundingBox.left >= otherCollider.boundingBox.right) colliding = false;

                    // iterator to make sure there isn't a duplicate collision
                    // checks if there is already a collision equivalent to the collider of this entity
                    auto it = std::find_if(entityCollider.collisions.begin(), entityCollider.collisions.end(), 
                        [&](const std::pair<Collision::State, Components::Collider*> &pair) { 
                            return (Components::Collider*)pair.second == &otherCollider; 
                        }
                    );

                    auto AddCollision = [&] (Collision::State state) {
                        // if the collision is already there, don't emplace it to the map
                        if (it == entityCollider.collisions.end()) {
                            entityCollider.collisions.emplace(state, &otherCollider);
                            std::cout << "State " << static_cast<int>(state) << ", ";
                            std::cout << "Entity " << otherCollider.owner << ", ";
                            std::cout << "\n";
                        };
                    };

                    // if (entityCollider.boundingBox.right > otherCollider.boundingBox.left && entityCollider.boundingBox.left < otherCollider.boundingBox.right)
                    // {
                    //     std::cout << "this should work according to my brain" << "\n";
                    // }

                    if (colliding) {
                        collidedEntities.push_back(otherEntity);
                        entityCollider.isCurrentlyColliding = true;

                        if (entityCollider.boundingBox.right - 10 > otherCollider.boundingBox.left && entityCollider.boundingBox.left + 10 < otherCollider.boundingBox.right)
                        {
                            if (otherTransform.y > entityTransform.y)
                            {
                                AddCollision(Collision::State::ON_BOTTOM);
                                std::cout << "breakpoint" << "\n";
                                continue;

                            } else if (otherTransform.y < entityTransform.y) {
                                AddCollision(Collision::State::ON_TOP);
                                continue;
                            }
                        } 

                        if (entityCollider.boundingBox.top - 10 < otherCollider.boundingBox.bottom && entityCollider.boundingBox.bottom + 10 > otherCollider.boundingBox.top)
                        {
                            if (otherTransform.x > entityTransform.x) {
                                AddCollision(Collision::State::ON_RIGHT);
                                continue;

                            } else if (otherTransform.x < entityTransform.x) {
                                AddCollision(Collision::State::ON_LEFT);
                                continue;
                            }
                        }

                    } else {
                        auto it2 = std::find_if(entityCollider.collisions.begin(), entityCollider.collisions.end(), 
                            [&](const std::pair<Collision::State, Components::Collider*> &pair) { 
                                return (Components::Collider*)pair.second == &otherCollider; 
                            }
                        );

                        // std::cout << "collision is gae" << "\n";

                        if (it2 != entityCollider.collisions.end()) {
                            entityCollider.collisions.erase(it2);
                            std::cout << "erase collision" << "\n";
                        }

                        if (entityCollider.collisions.size() == 0)
                        {
                            entityCollider.isCurrentlyColliding = false;
                        }
                    }   
                } 
			}
		}

		void CollisionSystem::Cleanup()
		{
			// nothing to implement here
		}
	}
}
