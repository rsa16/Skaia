#pragma once
#include <bitset>
#include <cstdint>
#undef main

using std::string;

// ECSs
using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;



// Input
enum class InputButtons
{
	W,
	A,
	S,
	D,
	Q,
	E
};