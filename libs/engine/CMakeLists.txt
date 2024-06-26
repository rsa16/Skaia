set(PROJECT_NAME SkaiaEngine)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "src/SkaiaCore.h"
    "src/GameApplication.h"
    "src/Types.h"
    "src/modules/SkaiaImaging.h"
    "src/modules/SkaiaTimer.h"
    "src/modules/SkaiaEvents.h"
    "src/modules/SkaiaUI.h"
    "src/modules/SkaiaAudio.h"
    "src/modules/SkaiaIO.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Components
    "src/components/Debug.h"
    "src/components/Input.h"
    "src/components/Window.h"
    "src/components/Transform.h"
    "src/components/Sprite.h"
    "src/components/Rigidbody.h"
    "src/components/AudioSource.h"
    "src/components/Map.h"
    "src/components/Hierarchy.h"
)
source_group("Header Files\\Core Modules" FILES ${Header_Files__Components})

set(Header_Files__Systems
    "src/systems/DebugSystem.h"
    "src/systems/InputSystem.h"
    "src/systems/RenderSystem.h"
    "src/systems/WindowSystem.h"
    "src/systems/PhysicsSystem.h"
    "src/systems/AudioSystem.h"
    "src/systems/MapSystem.h"
    "src/systems/CollisionSystem.h"
)

set(Resource_Files__Source_Files__Systems
    "src/systems/DebugSystem.cpp"
    "src/systems/InputSystem.cpp"
    "src/systems/RenderSystem.cpp"
    "src/systems/WindowSystem.cpp"
    "src/systems/PhysicsSystem.cpp"
    "src/systems/AudioSystem.cpp"
    "src/systems/MapSystem.cpp"
    "src/systems/CollisionSystem.cpp"
)
source_group("Resource Files\\Source Files\\Systems" FILES ${Resource_Files__Source_Files__Systems})

set(Resource_Files__Source_Files
    "src/GameApplication.cpp"
    "src/modules/SkaiaImaging.cpp"
    "src/modules/SkaiaTimer.cpp"
    "src/modules/SkaiaEvents.cpp"
    "src/modules/SkaiaUI.cpp"
    "src/modules/SkaiaAudio.cpp"
    "src/modules/SkaiaIO.cpp"
)
source_group("Resource Files\\Source Files" FILES ${Resource_Files__Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__Components}
    ${Header_Files__Systems}
    ${Resource_Files__Source_Files__Systems}
    ${Resource_Files__Source_Files}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE SkaiaEngine)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/bin/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_SOURCE_DIR}/external/sdl_image"
    "${CMAKE_SOURCE_DIR}/external/sdl_mixer/include"
    "${CMAKE_SOURCE_DIR}/external/sdl/include"
    "${CMAKE_SOURCE_DIR}/external/sdl_ttf"
    "${CMAKE_SOURCE_DIR}/external/box2d/include"
    "${CMAKE_SOURCE_DIR}/external/yaml-cpp/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "ENGINE_EXPORTS;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /Oi;
            /Gy
        >
        /permissive-;
        /sdl;
        /W3;
        /std:c++latest;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
        >
        /DEBUG;
        /std:c++latest;
        /SUBSYSTEM:WINDOWS
    )
endif()

################################################################################
# Post build events
################################################################################
# if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
#     add_custom_command_if(
#         TARGET ${PROJECT_NAME}
#         POST_BUILD
#         COMMANDS
#         COMMAND $<CONFIG:Debug> cp $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/>bin\\Engine.dll $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>bin\\Engine.dll
#         COMMAND $<CONFIG:Release> cp $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/>bin\\Engine.dll $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>bin\\Engine.dll
#     )
# elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
#     add_custom_command_if(
#         TARGET ${PROJECT_NAME}
#         POST_BUILD
#         COMMANDS
#         COMMAND   $<CONFIG:Debug> cp $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/>bin\\Engine.dll $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>bin\\Engine.dll
#         COMMAND $<CONFIG:Release> cp $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/>bin\\Engine.dll $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>bin\\Engine.dll
#     )
# endif()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "SDL2-static"
    "SDL2main"
    "SDL2_image-static"
    "SDL2_ttf"
    "box2d"
    "SDL2_mixer-static"
    "yaml-cpp"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

IF(CMAKE_BUILD_TYPE MATCHES Release)
    set(CONFIGURATION_TYPE Release)
ENDIF()

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CONFIGURATION_TYPE Debug)
ENDIF()

target_link_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/build/external/sdl/${CONFIGURATION_TYPE}"
    "${CMAKE_SOURCE_DIR}/build/external/sdl_image/${CONFIGURATION_TYPE}"
    "${CMAKE_SOURCE_DIR}/build/external/sdl_ttf/${CONFIGURATION_TYPE}"
    "${CMAKE_SOURCE_DIR}/build/external/box2d/bin/${CONFIGURATION_TYPE}"
    "${CMAKE_SOURCE_DIR}/build/external/sdl_mixer/${CONFIGURATION_TYPE}"
)

