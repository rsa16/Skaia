import cppyy
from functools import lru_cache

from .utils import skaia_bootstrap as __skaia_bootstrap

@lru_cache(maxsize=1024)
def __skaia_include():
    cppyy.include("behaviors/SkaiaEvents.h")

__skaia_bootstrap()
__skaia_include()

from cppyy.gbl import Events as __ev

KeyboardEventType = __ev.KeyboardEventType
PhysicsEventType = __ev.PhysicsEventType
AudioEventType = __ev.AudioEventType

EventNames = __ev.EventNames

Event = __ev.Event
KeyboardEvent = __ev.KeyboardEvent
PhysicsEvent = __ev.PhysicsEvent
AudioEvent = __ev.AudioEvent
QuitEvent = __ev.QuitEvent
UserEvent = __ev.UserEvent

DispatchEvent = __ev.DispatchEvent