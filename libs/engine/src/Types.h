/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once
#include <bitset>
#include <cstdint>

#ifdef _DEBUG
	#undef main
#endif

#if defined(_MSC_VER)
    //  Microsoft 
    #define ENGINE_API_EXPORT __declspec(dllexport)
    #define ENGINE_API_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define ENGINE_API_EXPORT  __attribute__((visibility("default")))
    #define ENGINE_API_IMPORT
#else
    //  do nothing and hope for the best?
    #define ENGINE_API_EXPORT
    #define ENGINE_API_IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#ifdef ENGINE_EXPORTS
#	define ENGINE_API ENGINE_API_EXPORT
#else
#	define ENGINE_API ENGINE_API_IMPORT
#endif

namespace Skaia
{
    struct DataStructure
    {
        void* data;
        void* data1 = nullptr;
        void* data2 = nullptr;
    };

    // ECSs
    using Entity = std::uint32_t;
    const Entity NullEntity = -1;
    const Entity MAX_ENTITIES = 5000;
    using ComponentType = std::uint8_t;
    const ComponentType MAX_COMPONENTS = 32;
    using Signature = std::bitset<MAX_COMPONENTS>;
}