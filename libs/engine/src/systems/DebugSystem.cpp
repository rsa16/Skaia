/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <SDL.h>
#include "DebugSystem.h"
#include <iostream>

#ifdef _DEBUG
#undef main
#endif

namespace Skaia
{
	namespace Systems
	{
		DebugSystem::DebugSystem(Skaia::Core::Coordinator *c)
		{
			coordinator = c;

			Signature signature;
			signature.set(coordinator->GetComponentType<Skaia::Components::Debug>());
			signature.set(coordinator->GetComponentType<Skaia::Components::Input>());
			coordinator->SetSystemSignature<Skaia::Systems::DebugSystem>(signature);
		}

		void DebugSystem::Initialize(void *data)
		{
			std::cout << "Debug System Initalized"
					<< "\n";
		}

		void DebugSystem::Render()
		{
			// nothing to implement here
		}

		void DebugSystem::Update()
		{
			for (auto const &entity : mEntities)
			{
				auto &entityInputComponent = coordinator->GetComponent<Skaia::Components::Input>(entity);
				if (entityInputComponent.UP_PRESSED)
				{
				}
			}
		}

		void DebugSystem::Cleanup()
		{
			// nothing to implement here
		}
	}
}
