/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once
#include "Core.h"
#include "Input.h"
#undef main

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

struct ENGINE_API Debug {};

class ENGINE_API DebugSystem : public SkaiaCore::System 
{
private:
	SkaiaCore::Coordinator* coordinator;
public:
	DebugSystem(SkaiaCore::Coordinator* coordinator);
	void Update() override;
	void Render() override;
	void Cleanup() override;
	void Initialize() override;
};