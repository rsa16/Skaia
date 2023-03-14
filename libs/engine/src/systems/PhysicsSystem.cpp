/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <SDL.h>
#include <iostream>
#include "PhysicsSystem.h"

#ifdef _DEBUG
  #undef main
#endif

// not really sure why i chose this number, kind of chosen randomly
// when converting pixels, multiply the pixel coordinate by the negative inverse constant of MET2PIX
// to simulate sdl's coordinate system (increasing y goes down)
const float MET2PIX = 80.0f;

// for example:
// pixelsToMeters = pixels * -PIX2MET
// metersToPixels = meters * MET2PIX
const float PIX2MET = (1/MET2PIX); 

const int WIDTH = 500;
const int HEIGHT = 600;

const float SCALED_WIDTH = WIDTH * PIX2MET;
const float SCALED_HEIGHT = HEIGHT * PIX2MET;

const float GRAVITY = -9.81f;
const float TIMESTEP = 1.0f / 60.0f;
const int32 VELOCITY_ITERATIONS = 6;
const int32 POSITION_ITERATIONS = 2;

namespace Skaia
{
    namespace Systems
    {
        PhysicsSystem::PhysicsSystem(Skaia::Core::Coordinator *c)
        {
            coordinator = c;

            Signature signature;
            signature.set(coordinator->GetComponentType<Components::RigidBody>());
            signature.set(coordinator->GetComponentType<Components::Transform>());
            coordinator->SetSystemSignature<PhysicsSystem>(signature);
        }

        void PhysicsSystem::Initialize(void *data)
        {
            // create world
            world = new b2World(b2Vec2(0.0f, GRAVITY));

            for (auto const& entity : mEntities)
            {
                auto& entityRigidBody = coordinator->GetComponent<Components::RigidBody>(entity);
                auto& entityTransform = coordinator->GetComponent<Components::Transform>(entity);

                b2BodyDef entityBodyDef;
                entityBodyDef.type = (entityRigidBody.bodyType == Physics::RigidBodyType::STATIC) ? b2_staticBody : b2_dynamicBody;
                entityBodyDef.angle = 0;
                entityBodyDef.position.Set(entityTransform.x * PIX2MET, ((entityTransform.y-entityTransform.height) * -PIX2MET));
                b2Body* entityBody = world->CreateBody(&entityBodyDef);

                b2PolygonShape entityShape;
                float hw = (entityTransform.height * PIX2MET)/2;
                entityShape.SetAsBox((entityTransform.width * PIX2MET)/2, hw);

                printf("entity: %.6f debug shit: %.6f", entityTransform.y, (entityTransform.y*-PIX2MET));

                b2FixtureDef entityFixtureDef;
                entityFixtureDef.shape = &entityShape;
                entityFixtureDef.density = entityRigidBody.density;
                entityFixtureDef.friction = entityRigidBody.friction;

                entityBody->CreateFixture(&entityFixtureDef);
                entityRigidBody.box2dbody = entityBody;
            }

            std::cout << "Physics System Initializwed"
                    << "\n";
        }

        void PhysicsSystem::Render()
        {
            // nothing to do yet
        }

        void PhysicsSystem::Update()
        {
            world->Step(TIMESTEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

            for (auto const& entity : mEntities)
            {
                auto &entityRigidBody = coordinator->GetComponent<Components::RigidBody>(entity);
                auto &entityTransform = coordinator->GetComponent<Components::Transform>(entity);

                b2Vec2 position = entityRigidBody.box2dbody->GetPosition();
                float angle = entityRigidBody.box2dbody->GetAngle();

                entityTransform.x = position.x * MET2PIX;
                entityTransform.y = (position.y * -MET2PIX)-entityTransform.height;

                if (entity == 1)
                {
                    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
                }
            }
        }

        bool PhysicsSystem::HandleEvent(Events::Event* event)
        {
            Events::PhysicsEvent* ev = dynamic_cast<Events::PhysicsEvent*>(event);

            if (ev->type == Events::PhysicsEventType::APPLY_FORCE)
            {
                auto &entityRigidBody = coordinator->GetComponent<Components::RigidBody>(ev->entity);
                float mass = entityRigidBody.box2dbody->GetMass();
                b2Vec2 worldCenter = entityRigidBody.box2dbody->GetWorldCenter();

                entityRigidBody.box2dbody->ApplyForce(b2Vec2(ev->velocity.x * mass, ev->velocity.y * mass * 2), worldCenter, true);
            }
            // printf("psystem\n");
            return true;
        }

        void PhysicsSystem::Cleanup() 
        {
            // absolutely noting to do here lmao
        }
    }
}