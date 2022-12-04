set(PROJECT_NAME Engine)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "src/SkaiaCore.h"
    "src/GameApplication.h"
    "src/Types.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Core_Behaviors
    "src/Debug.h"
    "src/Input.h"
    "src/Window.h"
)
source_group("Header Files\\Core Behaviors" FILES ${Header_Files__Core_Behaviors})

set(Resource_Files__Source_Files
    "src/GameApplication.cpp"
)
source_group("Resource Files\\Source Files" FILES ${Resource_Files__Source_Files})

set(Resource_Files__Source_Files__Core_Behaviors
    "src/Debug.cpp"
    "src/Input.cpp"
    "src/Window.cpp"
)
source_group("Resource Files\\Source Files\\Core Behaviors" FILES ${Resource_Files__Source_Files__Core_Behaviors})

set(ALL_FILES
    ${Header_Files}
    ${Header_Files__Core_Behaviors}
    ${Resource_Files__Source_Files}
    ${Resource_Files__Source_Files__Core_Behaviors}
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
            /std:c++20;
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
            /std:c++20;
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
            /std:c++20;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /std:c++20;
            /SUBSYSTEM:CONSOLE
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
        COMMAND   $<CONFIG:Debug> cp $<SHELL_PATH:${CMAKE_CURRENT_SOURCE_DIR}/>bin\\Engine.dll $<SHELL_PATH:${CMAKE_SOURCE_DIR}/>bin\\Engine.dll
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

