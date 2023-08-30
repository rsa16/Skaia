/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <SDL.h>
#include "MapSystem.h"
#include <iostream>

#ifdef _DEBUG
#undef main
#endif

namespace Skaia
{
	namespace Systems
	{
		MapSystem::MapSystem(Skaia::Core::Coordinator *c)
		{
			coordinator = c;

			Signature signature;
			signature.set(coordinator->GetComponentType<Skaia::Components::Map>());
			signature.set(coordinator->GetComponentType<Skaia::Components::Hierarchy>());
			coordinator->SetSystemSignature<Skaia::Systems::MapSystem>(signature);
		}

		void MapSystem::Initialize(void *data)
		{
			std::cout << "Map System Initalized"
					<< "\n";
		}

		void MapSystem::Render()
		{
			// nothing to implement here
		}

		void MapSystem::Update()
		{
			// for (auto const &entity : mEntities)
			// {
				
			// }
		}

		void MapSystem::Cleanup()
		{
			// nothing to implement here
		}
	}
}
