/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include "Types.h"
#include "SkaiaIO.h"

#include "SkaiaUI.h"
#include "SkaiaImaging.h"

#include <yaml-cpp/yaml.h>
#include <SDL.h>

#ifdef _DEBUG
	#undef main
#endif

namespace Skaia
{
    namespace IO {
        Filesystem::Filesystem(std::string resourceFile) 
        {
            Initialize(resourceFile);
        }

        void Filesystem::Initialize(std::string resourceFile)
        {
            YAML::Node rcFile = YAML::LoadFile(resourceFile);
            
            prefix = rcFile["resource_prefix"].as<std::string>();
            for (YAML::Node file : rcFile["files"])
            {
                std::string alias = file["alias"] ? file["alias"].as<std::string>() : file["path"].as<std::string>();
                resourceMap.insert({alias, file["path"].as<std::string>()});
            }
        }

        void Filesystem::Initialize(std::unordered_map<std::string, std::string> resourceMap)
        {
            prefix = ":";
            resourceMap = resourceMap;
        }

        void Filesystem::InitializePacked(std::string folderPath)
        {

        }
        
        template<>
        Imaging::Texture Filesystem::Load<IO::FileType::Texture>(std::string file, void* extraData)
        {
            SDL_Renderer* pr = (SDL_Renderer*)extraData;
            Imaging::Texture tex(pr);

            tex.LoadFile(resourceMap[file]);
            return tex;
        }

        template<>
        UI::Font Filesystem::Load<IO::FileType::Font>(std::string file, void* extraData)
        {
            UI::Font font;
            font.LoadFont(resourceMap[file]);
            return font;
        }
    }  
} 



