import os
import sys
import cppyy
from functools import lru_cache

__all__ = [ "skaia_bootstrap" ]

ALL_SDL = ["sdl_image", "sdl", "sdl_mixer", "sdl_ttf"]

@lru_cache(maxsize=1024)
def __get_skaia_library() -> str:
    if sys.platform in ["win32", "cygwin"]:
        return "SkaiaEngine.dll"

    elif sys.platform in ["darwin"]:
        return "libSkaiaEngine.dylib"

    return "libSkaiaEngine.so"

@lru_cache(maxsize=1024)
def __get_skaia_library_path(root_path: str):
    library_path = os.path.join(root_path, "data", __get_skaia_library())
    if os.path.exists(library_path):
        return library_path
    
    library_path = os.path.join(root_path, "..", "..", "..", "bin", __get_skaia_library())
    if os.path.exists(library_path):
        return library_path
    
    raise ImportError("Unable to locate Skaia library path")

@lru_cache(maxsize=1024)
def __get_skaia_include_path(root_path: str):
    include_path = os.path.abspath(os.path.join(root_path, "data"))
    if os.path.isdir(include_path):
        return include_path
    
    include_path = os.path.abspath(os.path.join(root_path, "..", "..", "..", "libs", "engine", "src"))
    print(include_path)

    if os.path.isdir(include_path):
        return include_path

    raise ImportError("Unable to locate Skaia include path")

@lru_cache(maxsize=1024)
def __get_sdl_include_paths(root_path: str):
    include_paths = []
    for lib in ALL_SDL:
        include_path = os.path.abspath(os.path.join(root_path, "data", lib))
        if os.path.isdir(include_path) and include_path not in include_paths:
            include_paths.append(include_path)
        
        include_path = os.path.abspath(os.path.join(root_path, "..", "..", "..", "external", lib))
        if lib == "sdl" or lib == "sdl_mixer":
            include_path = os.path.join(include_path, "include")

        if os.path.isdir(include_path) and include_path not in include_paths:
            include_paths.append(include_path)
    return include_paths

@lru_cache(maxsize=1024)
def __get_box2d_include_path(root_path: str):
    include_path = os.path.abspath(os.path.join(root_path, "data", "box2d"))
    if os.path.isdir(include_path):
        return include_path
    
    include_path = os.path.abspath(os.path.join(root_path, "..", "..", "..", "external", "box2d", "include"))
    if os.path.isdir(include_path):
        return include_path
    
    raise ImportError("Unable to locate Box2D include path")


@lru_cache(maxsize=1024)
def skaia_bootstrap():
    root_path = os.path.abspath(os.path.join(os.path.dirname(__file__)))

    all_includes = []

    all_includes += [__get_skaia_include_path(root_path)]
    all_includes += __get_sdl_include_paths(root_path)
    all_includes += [__get_box2d_include_path(root_path)]

    skaia_library_path = __get_skaia_library_path(root_path)

    print(all_includes)
    for include in all_includes:
        cppyy.add_include_path(include)

    cppyy.load_library(skaia_library_path)
