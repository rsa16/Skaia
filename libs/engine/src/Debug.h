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