import cppyy
from functools import lru_cache

from .utils import skaia_bootstrap as __skaia_bootstrap

@lru_cache(maxsize=1024)
def __skaia_include():
    cppyy.include("components/AudioSource.h")
    cppyy.include("components/Debug.h")
    cppyy.include("components/Input.h")
    cppyy.include("components/Rigidbody.h")
    cppyy.include("components/Sprite.h")
    cppyy.include("components/Transform.h")
    cppyy.include("components/Window.h")

__skaia_bootstrap()
__skaia_include()

from cppyy.gbl import Components as __cmp

AudioSource = __cmp.AudioSource
Debug = __cmp.Debug
Input = __cmp.Input
RigidBody = __cmp.RigidBody
Sprite = __cmp.Sprite
Transform = __cmp.Transform
Window = __cmp.Window