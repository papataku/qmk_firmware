/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "keymap_jp.h"

// レイヤー
enum preonic_layers {
  _QWERTY,        // デフォルトレイヤー(JIS配列で認識)
  _LOWER,
  _RAISE,
  _FUNC1,
  _FUNC2,
  _ADJUST
};

// 特殊な動作のキーコード
enum preonic_keycodes {
  QWERTY = SAFE_RANGE,  // デフォルトレイヤーをJIS(QWERTY配列)に切り替え
  LOWER,
  RAISE,
  SF_GRV,             // tap : shift = ` : ~
  SF_2,               // tap : shift = 2 : @
  SF_6,               // tap : shift = 6 : ^
  SF_7,               // tap : shift = 7 : &
  SF_8,               // tap : shift = 8 : *
  SF_9,               // tap : shift = 9 : (
  SF_0,               // tap : shift = 0 : )
  SF_SCLN,            // tap : shift = ; : :
  SF_QUOT,            // tap : shift = ' : "
  TGL_RIS,          // トグルでRaiseレイヤーに切り替え
  TGL_LOW,          // トグルでLowerレイヤーに切り替え
};

// 特殊な動作のマクロ設定
enum user_macro {
  UM_EMHL,
  UM_KHKR
};

#define M_EMHL MACROTAP(UM_EMHL)      // タップでMacの「英数」とWindowsの「無変換」  ホールドでLowerレイヤー
#define M_KHKR MACROTAP(UM_KHKR)      // タップでMacの「かな」とWindowsの「変換」    ホールドでRaiseレイヤー
#define FN1_ESC LT(_FUNC1,KC_ESC)     // タップでESC                 ホールドでFunction_1レイヤーon
#define FN2_TAB LT(_FUNC2,KC_TAB)     // タップでTab                 ホールドでFunction_2レイヤーon
#define ADJUST  MO(_ADJUST)           // ホールドでAdjustレイヤーをon


#define IS_LSFT(kc) ((QK_LSFT & (kc)) == QK_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |Esc/F1|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Tab/F2|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   `  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |ADJUST|Eng/Lo|    Space    |Jpn/Ra|  /   | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 * Shift pattern
 * ,-----------------------------------------------------------------------------------.
 * |  ~   |      |  @   |      |      |      |  ^   |   &  |   *  |  (   |   )  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |   :  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  FN1_ESC, KC_1,    SF_2,    KC_3,    KC_4,    KC_5,    SF_6,    SF_7,    SF_8,    SF_9,    SF_0,    KC_DEL, \
  FN2_TAB, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,  \
  SF_GRV,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    SF_SCLN, KC_ENT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   SF_QUOT,  \
  KC_LCTL, KC_LGUI, KC_LALT, ADJUST,  M_EMHL,  KC_SPC,  KC_SPC,  M_KHKR,  KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT  \
),



/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |Esc/F1|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F11 |  F12 |      |      |      |      |   7  |   8  |   9  |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |PrintS|      |      |   .  |   -  |   4  |   5  |   6  |   *  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |   ,  |   +  |   1  |   2  |   3  |   /  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |      |      |             |   0  |   .  |   ,  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
  FN1_ESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6  , KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL, \
  _______, KC_F11,  KC_F12,  _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    _______, KC_BSPC,  \
  _______, _______, KC_PSCR, _______, _______, KC_DOT,  KC_PMNS, KC_4,    KC_5,    KC_6,    KC_PAST, _______, \
  _______, _______, _______, _______, _______, KC_COMM, KC_PPLS, KC_1,    KC_2,    KC_3,    KC_PSLS, KC_PEQL, \
  KC_LCTL, KC_LGUI, KC_LALT, _______, _______, _______, _______, _______, KC_DOT,  KC_COMM, _______, _______ \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |Esc/F1|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F11 |  F12 |      |      |      |      |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |PrintS|      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | HOME |  END | PGUP | PGDN |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  FN1_ESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6  , KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL, \
  _______, KC_F11,  KC_F12,  _______, _______, _______, _______, JP_UNDS, JP_PLUS, JP_LCBR, JP_RCBR, JP_PIPE, \
  KC_DEL,  _______, KC_PSCR, _______, _______, _______, _______, JP_MINS, JP_EQL,  JP_LBRC, JP_RBRC, JP_BSLS, \
  _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END,  KC_PGUP, KC_PGDN, _______, \
  KC_LCTL, KC_LGUI, KC_LALT, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Function 1
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC1] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, TGL_LOW, _______, _______, TGL_RIS, _______, _______, _______, _______  \
),

/* Function 2
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC2] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,  \
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______,  _______, _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______, \
  KC_LCTL, KC_LGUI, KC_LALT, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
)
};


// サウンド設定
#ifdef AUDIO_ENABLE
  float layer_lock_on_song[][2]  = SONG(LAYER_LOCK_ON_SOUND);   // Layerロック
  float layer_lock_off_song[][2] = SONG(LAYER_LOCK_OFF_SOUND);  // Layerロック解除
  float caps_lock_song[][2]      = SONG(CAPS_LOCK_ON_SOUND);    // Caps Lockキー
  float adjust_on_song[][2]      = SONG(ADJUST_ON_SOUND);       // Adjustキーon
  float adjust_off_song[][2]     = SONG(ADJUST_OFF_SOUND);      // Adjustキーoff
  float push_song[][2]           = SONG(PUSH_SOUND);            // 汎用
#endif

const uint16_t PROGMEM keymap_us2jis[][4] = {
  [SF_GRV ]  = { JP_GRV ,  JP_TILD},            // tap : shift = ` : ~
  [SF_2   ]  = { KC_2   ,  JP_AT  },            // tap : shift = 2 : @
  [SF_6   ]  = { KC_6   ,  JP_CIRC},            // tap : shift = 6 : ^
  [SF_7   ]  = { KC_7   ,  JP_AMPR},            // tap : shift = 7 : &
  [SF_8   ]  = { KC_8   ,  JP_ASTR},            // tap : shift = 8 : *
  [SF_9   ]  = { KC_9   ,  JP_LPRN},            // tap : shift = 9 : (
  [SF_0   ]  = { KC_0   ,  JP_RPRN},            // tap : shift = 0 : )
  [SF_SCLN]  = { JP_SCLN,  JP_COLN},            // tap : shift = ; : :
  [SF_QUOT]  = { JP_QUOT,  JP_DQT },            // tap : shift = ' : "
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool lshift = false;
  static bool rshift = false;
  static uint8_t l_r_layer;
  
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case SF_GRV:
    case SF_2:
    case SF_6:
    case SF_7:
    case SF_8:
    case SF_9:
    case SF_0:
    case SF_SCLN:
    case SF_QUOT:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (!IS_LSFT(keymap_us2jis[keycode][1])) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
          }
          register_code(keymap_us2jis[keycode][1]);
          unregister_code(keymap_us2jis[keycode][1]);
          if (!IS_LSFT(keymap_us2jis[keycode][1])) {
            if (lshift) register_code(KC_LSFT);
            if (rshift) register_code(KC_RSFT);
          }
        } else {
          if (IS_LSFT(keymap_us2jis[keycode][0]))
            register_code(KC_LSFT);
          register_code(keymap_us2jis[keycode][0]);
          unregister_code(keymap_us2jis[keycode][0]);
          if (IS_LSFT(keymap_us2jis[keycode][0]))
            unregister_code(KC_LSFT);
        }
      }
      return false;
      break;
    case TGL_LOW:                           // Lower/Raiseにトグル
    case TGL_RIS:
      if (record->event.pressed) {
        if (keycode == TGL_LOW){
            l_r_layer = _LOWER;
        } else if (keycode == TGL_RIS){
            l_r_layer = _RAISE;
        }
        if IS_LAYER_ON(l_r_layer){
            layer_off(l_r_layer);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(layer_lock_off_song);
            #endif
        } else {
            layer_on(l_r_layer);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(layer_lock_on_song);
            #endif
        }
      }
      return false;
      break;
    case M_EMHL:                           // Lower/RaiseキーのサウンドとLED
    case M_KHKR:
        if (record->event.pressed) {       // レイヤーがトグルされていれば、そのレイヤーをオフにしてサウンドを鳴らす
          if (IS_LAYER_ON(_LOWER) || IS_LAYER_ON(_RAISE)) {
            if (keycode == M_EMHL){
                l_r_layer = _LOWER;
            } else /* if (keycode == M_KHKR) */ {
                l_r_layer = _RAISE;
            }
            layer_off(l_r_layer);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(layer_lock_off_song);
            #endif
            return false;
            break;
          }
        }
      return true;
      break;
    case ADJUST:                           // Adjustキー用の音
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(adjust_on_song);
        #endif
      } else {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(adjust_off_song);
        #endif
      }
      return true;
      break;
  }
  return true;
};

// Macro actions for each corresponding ID.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        case UM_EMHL: // タップで「英数」と「無変換」、ホールドで「Lower」
        return MACRO_TAP_HOLD_LAYER( record, MACRO(T(MHEN), T(LANG2), END), _LOWER );
        case UM_KHKR: // タップで「かな」と「変換」、ホールドで「Raise」
        return MACRO_TAP_HOLD_LAYER( record, MACRO(T(HENK), T(LANG1), END), _RAISE );
        };
        return MACRO_NONE;
}