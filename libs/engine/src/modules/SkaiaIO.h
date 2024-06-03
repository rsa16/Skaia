/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include "Types.h"
#include <tuple>
#include <unordered_map>

#ifdef _DEBUG
    #undef main
#endif

namespace Skaia
{
    namespace Imaging { class Texture; }
    namespace UI {class Font;}

    namespace IO {
        using FileTypes = std::tuple<Imaging::Texture, UI::Font>;

        // File type enumeratopm
        enum class FileType {
            Texture,
            Font
        };

        /// @brief Filesystem API
        class ENGINE_API Filesystem
        {
            private:
                std::unordered_map<std::string, std::string> resourceMap;
                std::string prefix;

            public:
                /// @brief Construct empty file system, initialize with functions later
                Filesystem() {}

                /// @brief Construct from a file
                /// @param resourceFile The name of the file, usually a `.rc` file
                Filesystem(std::string resourceFile);


                /// @brief Initialize from file
                /// @param resourceFile The name of a file, usually a `.rc` file
                void Initialize(std::string resourceFile);

                /// @brief Initialize with a map containing the resources the XML would
                /// @param resourceMap An unordered_map that the file system will use
                void Initialize(std::unordered_map<std::string, std::string> resourceMap);

                /// @brief Initialize file system from a packed virtual file storage map
                /// @param folderPath The folder containing the packed files
                void InitializePacked(std::string folderPath);

                
                /// @brief Load different virtual files into engine objects
                /// @tparam FT The filetype you are trying to load
                /// @param file The path to the file in the virtual filesystem
                /// @param extraData A void pointer to any extra data, might need to provide renderer in some cases for texture
                /// @return The engine object corresponding to the templated file type
                template <FileType FT>
                std::tuple_element_t<static_cast<size_t>(FT), FileTypes> Load(std::string file, void* extraData);

                /// @brief Export and pack all files stored in the virtual storage map to 3 files: `resources.rc`, `resources.assets`, `fs.info`
                /// @note Should only be used by the build tool, not the user
                /// @warning Will result in loading of every file in the file system and serialization, memory intensive function
                /// @param folderPath A string that refers to the path of the folder that should be exported too
                void ExportFilesystem(std::string folderPath);
        };
    };
}