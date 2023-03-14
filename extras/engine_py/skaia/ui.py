import cppyy
from functools import lru_cache

from .utils import skaia_bootstrap as __skaia_bootstrap

@lru_cache(maxsize=1024)
def __skaia_include():
    cppyy.include("behaviors/SkaiaUI.h")

__skaia_bootstrap()
__skaia_include()

from cppyy.gbl import UI as __ui

FontStyle = __ui.FontStyle
Font = __ui.Font
FontDatabase = __ui.FontDatabase
Text = __ui.Text