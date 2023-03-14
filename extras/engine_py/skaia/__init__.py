import cppyy
import sys

from .utils import skaia_bootstrap as __skaia__bootstrap

__skaia__bootstrap()

cppyy.include("Types.h")
cppyy.include("GameApplication.h")
cppyy.cppdef("using namespace Skaia;")

from cppyy.gbl import Entity, ComponentType, Signature, GameApplication
