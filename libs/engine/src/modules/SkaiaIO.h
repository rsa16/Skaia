/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include "Types.h"
#include <tuple>

#ifdef _DEBUG
    #undef main
#endif

namespace Skaia
{
    class UI::Font;
    class Imaging::Image;

    namespace IO {
        using FileTypes = std::tuple<Imaging::Image, UI::Font>;
        enum class FileType {
            Image,
            Font
        }

        class ENGINE_API Filesystem
        {
            private:
                std::unordered_map<std::string, std::string> resourceMap;

            public:
                Filesystem() {}
                Filesystem(std::string resourceFile);

                /// @brief Initialize from file
                /// @param resourceFile The name of a file, usually a `.rc` file
                void Initialize(std::string resourceFile);

                /// @brief Initialize with a map containing the resources the XML would
                /// @param resourceMap An unordered_map that the file system will use
                void Initialize(std::unordered_map<std::string, std::string> resourceMap);

                template <FileType FT>
                using File = std::tuple_element_t<FT, FileTypes>;
                
                File Load(std::string file);
        }
    }
}