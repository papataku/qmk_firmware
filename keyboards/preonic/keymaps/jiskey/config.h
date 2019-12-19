#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

//#define BACKLIGHT_BREATHING
#define TAPPING_TERM 200

#define SWAP_LCTR_LGUI


#pragma once

#ifdef AUDIO_ENABLE

    #define LAYER_LOCK_ON_SOUND \
    E__NOTE(_C4),         \
    E__NOTE(_G4),
    #define LAYER_LOCK_OFF_SOUND \
    E__NOTE(_G4),         \
    E__NOTE(_C4),
    #define PUSH_SOUND \
    E__NOTE(_G4),
    #define ADJUST_ON_SOUND \
    E__NOTE(_C4 ),
    #define ADJUST_OFF_SOUND \
    E__NOTE(_A4 ),

    #define STARTUP_SONG SONG(PREONIC_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(ONE_UP_SOUND) \
                                }
#endif

#define MUSIC_MASK (keycode != KC_NO)

/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

#endif
