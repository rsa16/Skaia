import cppyy
from functools import lru_cache

from .utils import skaia_bootstrap as __skaia_bootstrap

@lru_cache(maxsize=1024)
def __skaia_include():
    cppyy.include("systems/AudioSystem.h")
    cppyy.include("systems/DebugSystem.h")
    cppyy.include("systems/InputSystem.h")
    cppyy.include("systems/PhysicsSystem.h")
    cppyy.include("systems/RenderSystem.h")
    cppyy.include("systems/WindowSystem.h")

__skaia_bootstrap()
__skaia_include()

from cppyy.gbl import Systems as __sys

AudioSystem = __sys.AudioSystem
DebugSystem = __sys.DebugSystem
InputSystem = __sys.InputSystem
PhysicsSystem = __sys.PhysicsSystem
RenderSystem = __sys.RenderSystem
WindowSystem = __sys.WindowSystem