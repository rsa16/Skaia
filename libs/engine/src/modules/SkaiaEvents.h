/*
  Copyright (c) 2022, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#pragma once

#include "SDL.h"
#include <queue>
#include "box2d/box2d.h"
#include "Types.h"

#undef main

namespace Skaia
{
    namespace Events
    {
        //////////////////////////////////////////////////
        // EVENT TYPES
        //////////////////////////////////////////////////

        enum KeyboardEventType 
        {
            KEYDOWN,
            KEYUP
        };

        enum PhysicsEventType
        {
            APPLY_FORCE
        };

        /// @brief The event type for an AudioEvent
        enum AudioEventType
        {
            START_AUDIO,
            PAUSE_AUDIO,
            STOP_AUDIO,
            CHANGE_VOLUME
        };

        //////////////////////////////////////////////////
        // EVENT NAMES
        //////////////////////////////////////////////////

        enum EventNames
        {
            KEYBOARD_EVENT,
            PHYSICS_EVENT,
            AUDIO_EVENT,
            USER_EVENT,
            QUIT_EVENT
        };

        //////////////////////////////////////////////////
        // EVENTS
        //////////////////////////////////////////////////

        /// @brief Base event all other events are derived from
        struct Event {
            Uint32 timestamp;
            Uint32 type;
            EventNames name;
            virtual ~Event() = default;
        };

        /// @brief Tansmitted on any key press or release
        struct KeyboardEvent : Event {
            KeyboardEventType type;
            Uint8 state;
            Uint8 repeat;
            SDL_Keycode sym;
        };

        struct PhysicsEvent : Event {
            PhysicsEventType type;
            b2Vec2 velocity;
            Entity entity;
        };

        /// @brief Audio event
        /// @param entity The entity the event is being transmitted on, must have an AudioSource component to work
        /// @param type The type of event you are trying to convey (i.e. if you want to stop the playing audio or start it)
        /// @param volume Iff a change_volume event is sent with -1, you will mute the sound. Defaults to -1.
        struct AudioEvent : Event
        {
            AudioEventType type;
            Skaia::Entity entity; 
            float volume = -1;
        };

        struct QuitEvent : Event {};

        /// @brief Custom events for users to create
        struct UserEvent : Event {
            Sint32 code;
            void* data1;
            void* data2;
        };
        typedef std::queue<Event*> EventQueue;

        void ENGINE_API DispatchEvent(Event* ev);
        int CheckEvent(Event** ev);
    }
}