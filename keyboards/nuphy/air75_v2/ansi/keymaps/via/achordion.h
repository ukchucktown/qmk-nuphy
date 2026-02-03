// Copyright 2022-2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file achordion.h
 * @brief Achordion interface
 *
 * For full documentation, see
 * https://getreuer.info/posts/keyboards/achordion
 */

#pragma once

#include "quantum.h"

// Call this function from `process_record_user()` as
//
// bool process_record_user(uint16_t keycode, keyrecord_t* record) {
//   if (!process_achordion(keycode, record)) { return false; }
//
//   // Your macros...
//
//   return true;
// }
bool process_achordion(uint16_t keycode, keyrecord_t* record);

// Call this function from `housekeeping_task_user()` as
//
// void housekeeping_task_user(void) {
//   achordion_task();
// }
void achordion_task(void);

// In your keymap, define the following callback functions to configure
// Achordion behavior. The defaults are described below in the comments.

// A function to decide whether another key should be treated as a chord with
// the tap-hold key.  The tap-hold key is often, but not necessarily, a mod-tap
// or layer-tap key. `tap_hold_keycode` is the keycode of the tap-hold key, and
// `other_keycode` is the keycode of the other key pressed.
//
// For example, for home row mods, you could use this function to define which
// opposite-hand keys the tap-hold keys should be considered chords for, or
// return true for all keys to disable Achordion altogether.
//
// By default, Achordion works as a bilateral filter, where the tap-hold key is
// considered held only when the other key is on the opposite hand. This rule is
// targeted at home row mods, but can be customized as described in the
// Achordion documentation for other kinds of tap-hold keys.
//
// This function is weakly defined, so you can override it in your keymap.
bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                     uint16_t other_keycode, keyrecord_t* other_record);

// Returns true if `tap_hold_record` and `other_record` are on opposite hands.
bool achordion_opposite_hands(const keyrecord_t* tap_hold_record,
                              const keyrecord_t* other_record);

// The timeout in ms before the tap-hold key is considered a hold. The default
// is 1000 ms, but it can be customized for specific keys.
uint16_t achordion_timeout(uint16_t tap_hold_keycode);

// This function controls whether or not "eager mod" is enabled for a given
// modifier.  Eager mods are applied before the tap-hold decision.  This is
// important for some modifiers, such as shift.  The default is to eagerly apply
// shift and control, and not eagerly apply alt or gui.
bool achordion_eager_mod(uint8_t mod);

// Return true to completely bypass Achordion for the given event. This lets
// you exclude specific physical positions or keycodes from Achordion handling.
bool achordion_exclude(uint16_t keycode, keyrecord_t* record);

// Experimental feature: for notes, see Achordion docs.
#if defined(ACHORDION_STREAK)
// Returns true if it is desirable to continue a streak after `keycode`.
bool achordion_streak_continue(uint16_t keycode);

// The timeout in ms for a "streak chord." The default is to call
// `achordion_streak_timeout(tap_hold_keycode)`, which is recommended but can be
// customized if necessary.
uint16_t achordion_streak_chord_timeout(uint16_t tap_hold_keycode, uint16_t next_keycode);

// Timeout in ms for continuing a "streak". Default is 200 ms.
uint16_t achordion_streak_timeout(uint16_t tap_hold_keycode);
#endif
