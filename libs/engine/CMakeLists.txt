set(PROJECT_NAME Engine)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "src/SkaiaCore.h"
    "src/GameApplication.h"
    "src/Types.h"
    "src/behaviors/SkaiaImaging.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Components
    "src/components/Debug.h"
    "src/components/Input.h"
    "src/components/Window.h"
    "src/components/Transform.h"
    "src/components/Sprite.h"
)
source_group("Header Files\\Core Behaviors" FILES ${Header_Files__Components})

set(Header_Files__Systems
    "src/systems/DebugSystem.h"
    "src/systems/InputSystem.h"
    "src/systems/RenderSystem.h"
    "src/systems/WindowSystem.h"
)

set(Resource_Files__Source_Files__Systems
    "src/systems/DebugSystem.cpp"
    "src/systems/InputSystem.cpp"
    "src/systems/RenderSystem.cpp"
    "src/systems/WindowSystem.cpp"
)
source_group("Resource Files\\Source Files\\Systems" FILES ${Resource_Files__Source_Files__Systems})

set(Resource_Files__Source_Files
    "src/GameApplication.cpp"
    "src/behaviors/SkaiaImaging.cpp"
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
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
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
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../../external/sdl_image/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../external/sdl/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "ENGINE_EXPORTS;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "ENGINE_EXPORTS;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
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
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
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
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /std:c++latest;
            /SUBSYSTEM:WINDOWS
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
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
endif()

################################################################################
# Post build events
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    add_custom_command_if(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMANDS
        COMMAND $<CONFIG:Debug> cp $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/>bin\\Engine.dll $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>bin\\Engine.dll
        COMMAND $<CONFIG:Release> cp $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/>bin\\Engine.dll $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>bin\\Engine.dll
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    add_custom_command_if(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMANDS
        COMMAND   $<CONFIG:Debug> cp $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/>bin\\Engine.dll $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>bin\\Engine.dll
        COMMAND $<CONFIG:Release> cp $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/>bin\\Engine.dll $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>bin\\Engine.dll
    )
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "SDL2;"
        "SDL2main;"
        "SDL2_image"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../../build/external/sdl/Release"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../build/external/sdl_image/Release"
    )
endif()

