import cppyy
from functools import lru_cache

from .utils import skaia_bootstrap as __skaia_bootstrap

@lru_cache(maxsize=1024)
def __skaia_include():
    cppyy.include("SkaiaCore.h")

__skaia_bootstrap()
__skaia_include()

from cppyy.gbl import Core as __core

System = __core.System
IComponentArray = __core.IComponentArray
ComponentArray = __core.ComponentArray
EntityManager = __core.EntityManager
Coordinator = __core.Coordinator
SystemManager = __core.SystemManager