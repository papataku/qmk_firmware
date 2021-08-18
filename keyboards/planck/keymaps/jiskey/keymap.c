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
#include "twpair_on_jis.h"

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
  TGL_RIS,          // トグルでRaiseレイヤーに切り替え
  TGL_LOW,          // トグルでLowerレイヤーに切り替え
  MA_0X,            // 0x 代入
  MA_COL1,          // 1 column
  MA_COL2,          // 2 column
  MA_COL3,          // 3 column
  MA_COL4,          // 4 column
};

// 特殊な動作のマクロ設定
enum user_macro {
  UM_EMHL,
  UM_KHKR,
  UM_ECAJ
};

#define M_EMHL MACROTAP(UM_EMHL)      // タップでMacの「英数」とWindowsの「無変換」  ホールドでLowerレイヤー
#define M_KHKR MACROTAP(UM_KHKR)      // タップでMacの「かな」とWindowsの「変換」    ホールドでRaiseレイヤー
#define M_ECAJ MACROTAP(UM_ECAJ)      // タップで「ESC」    ホールドでADJUSTレイヤー
#define ADJ_ESC LT(_ADJUST,KC_ESC)    // タップでESC                 ホールドでADJUSTレイヤーon
#define FN2_TAB LT(_FUNC2,KC_TAB)     // タップでTab                 ホールドでFunction_2レイヤーon
#define FN1_SLS LT(_FUNC1,KC_SLSH)    // タップで/                   ホールドでFunction_1レイヤーon
#define ADJUST  MO(_ADJUST)           // ホールドでAdjustレイヤーをon
#define FUNC1   MO(_FUNC1)            // ホールドでFunction1レイヤーをon
#define FUNC2   MO(_FUNC2)            // ホールドでFunction2レイヤーをon
#define AL_PSCR LALT(KC_PSCR)         // ALT + PrintScreen
#define AL_C    LALT(KC_C)            // ALT + C
#define AL_V    LALT(KC_V)            // ALT + V
#define WS_S    SGUI(KC_S)            // WIN + Shift + S

// Tap Danceの設定
#ifdef TAP_DANCE_ENABLE
  enum {
   X_TAP_DANCE_1 = 0,
  };
  #define TAP_L TD(X_TAP_DANCE_1)     // タップで「英数」「無変換」 ホールドでLower  ダブルタップでLowerレイヤーのトグル
#else
  #define TAP_L M_EMHL                // Tap Danceが有効でなければM_EMHLに設定
#endif

// LED用の各レイヤーで使用するLEDの番号と数と色を指定する。
const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(   {0, 9, 0, 0, 0}    );
const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(  {0, 9, HSV_RED}  );
const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(  {0, 9, HSV_YELLOW}  );
const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 9, HSV_WHITE}  );


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |ADJUST|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  | /    |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | Fn2  |Eng/Lo|    Space    |Jpn/Ra| Fn1  | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid( \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,  \
  M_ECAJ,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_SLSH,  \
  KC_LCTL, KC_LGUI, KC_LALT, FUNC2,   TAP_L,   KC_SPC,  KC_SPC,  M_KHKR,  FUNC1,   KC_LEFT, KC_DOWN, KC_RGHT  \
),



/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | `/~  |  1 ! |  2 @ |  3 # |  4 $ |  5 % |  6 ^ |  7 & |  8 * |  9 ( |  0 ) | \ |  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |PrintS|      |      |  *   |   /  |  4   |  5   |  6   |      | ' "  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      | DEL  | Bksp | Enter|  +   |   -  |  1   |  2   |  3   |  =   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | XXXX |      0      |  .   |  ,   |      | "0x" |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
  _______, _______, AL_PSCR, _______, _______, KC_PAST, KC_PSLS, KC_4,    KC_5,    KC_6,    _______, KC_QUOT, \
  _______, _______, KC_DEL,  KC_BSPC, KC_ENT,  KC_PPLS, KC_PMNS, KC_1,    KC_2,    KC_3,    KC_PEQL, _______, \
  _______, _______, _______, _______, XXXXXXX, KC_0,    KC_0,    KC_DOT,  KC_COMM, _______, MA_0X,   _______  \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |      |      |   =  |PrintS|   {  |   }  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |   +  |   -  |      |   [  |   ]  | ' "  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |   *  |   _  | HOME | END  | PGUP | PGDN |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             | XXXX | App  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, KC_EQL,  AL_PSCR, KC_LCBR, KC_RCBR, KC_DEL, \
  _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, KC_PLUS, KC_MINS, _______, KC_LBRC, KC_RBRC, KC_QUOT, \
  _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_PAST, KC_UNDS, KC_HOME, KC_END,  KC_PGUP, KC_PGDN, \
  _______, _______, _______, _______, _______, _______, XXXXXXX, _______, KC_APP,  _______, _______, _______  \
),

/* Function 1
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |      |      |      |      |      |      |      |PrintS|      |WHE_U | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |WHE_L |WHE_D |WHE_R |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | PGUP | PGDN |      |MU_BT2|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | XXXX |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC1] = LAYOUT_planck_grid( \
  KC_ESC,  _______, _______, _______, _______, _______, _______, _______, AL_PSCR, _______, KC_WH_U, KC_DEL, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_WH_L, KC_WH_D, KC_WH_R, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN, _______, KC_BTN2, \
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______, _______, _______  \
),

/* Function 2
 * ,-----------------------------------------------------------------------------------.
 * | ESC  | F1   | F2   | F3   | F4   |      |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | F5   | F6   | F7   | F8   |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | F9   | F10  | F11  | F12  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | XXXX |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC2] = LAYOUT_planck_grid( \
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______, _______, _______, _______, KC_BSPC, \
  _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_F9,   KC_F10,  KC_F11 , KC_F12,  _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | COL1 | COL2 | COL3 | COL4 |Aud on|AudOff|AGnorm|AGswap|      |      |RESET |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | XXXX | PLY1 | PLY2 |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | SAVE1| SAVE2|ALT C |ALT V |      |      |      |      |MU_BT2| MUS_U|MU_BT2|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | SAEND| SAEND|      |      |             |      |      | MUS_L| MUS_D| MUS_R|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid( \
  _______, MA_COL1, MA_COL2, MA_COL3, MA_COL4, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, RESET,   \
  XXXXXXX, DM_PLY1, DM_PLY2, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, DM_REC1, DM_REC2, AL_C,    AL_V,    _______, _______, _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, \
  _______, DM_RSTP, DM_RSTP, _______, TGL_LOW, _______, _______, TGL_RIS, _______, KC_MS_L, KC_MS_D, KC_MS_R  \
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
  float dmacro_start_song[][2]   = SONG(PLOVER_SOUND);
  float dmacro_key_song[][2]     = SONG(UNICODE_LINUX);
  float dmacro_end_song[][2]     = SONG(PLOVER_GOODBYE_SOUND);
  float dmacro_exec_song[][2]    = SONG(WORKMAN_SOUND);
#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint8_t l_r_layer;
  
  switch (keycode) {
    case TGL_LOW:                           // Lower/Raiseにトグル
    case TGL_RIS:
      if (record->event.pressed) {
        if (keycode == TGL_LOW){
            l_r_layer = _LOWER;
        } else if (keycode == TGL_RIS){
            l_r_layer = _RAISE;
        }
        if (IS_LAYER_ON(l_r_layer)){
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
    case MA_0X:
      if (record->event.pressed) {
        SEND_STRING("0x");
      }
      return false;
      break;
    case MA_COL1:
      if (record->event.pressed) {
        SEND_STRING("1qaz");
      }
      return false;
      break;
    case MA_COL2:
      if (record->event.pressed) {
        SEND_STRING("2wsx");
      }
      return false;
      break;
    case MA_COL3:
      if (record->event.pressed) {
        SEND_STRING("3edc");
      }
      return false;
      break;
    case MA_COL4:
      if (record->event.pressed) {
        SEND_STRING("4rfv");
      }
      return false;
      break;
  }

  // type writer pairing on jis keyboard
  if (!twpair_on_jis(keycode, record))
    return false;

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
        case UM_ECAJ: // タップで「ESC」,ホールドで「Adjust」
        return MACRO_TAP_HOLD_LAYER( record, MACRO(TYPE(KC_ESC), END), _ADJUST );
        };
        return MACRO_NONE;
}

void dynamic_macro_record_start_user(void)
{
#ifdef AUDIO_ENABLE
	PLAY_SONG(dmacro_start_song);
#endif
}

void dynamic_macro_record_end_user(int8_t direction)
{
#ifdef AUDIO_ENABLE
	PLAY_SONG(dmacro_end_song);
#endif
}

void dynamic_macro_play_user(int8_t direction)
{
#ifdef AUDIO_ENABLE
	PLAY_SONG(dmacro_exec_song);
#endif
}


const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_base_layer,
    my_lower_layer,
    my_raise_layer,
    my_adjust_layer
);
void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
    rgblight_set_layer_state(0, true);
}

// LEDのレイヤーとキーマップで指定したレイヤーを対応させる
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, get_highest_layer(state) == _LOWER);
    rgblight_set_layer_state(2, get_highest_layer(state) == _RAISE);
    rgblight_set_layer_state(3, get_highest_layer(state) == _ADJUST);

    if (get_highest_layer(state) == _ADJUST) {
        PLAY_SONG(adjust_on_song);
    }

    return state;
}

// Tap danceの設定
#ifdef TAP_DANCE_ENABLE
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    return DOUBLE_TAP;
  }
  else return 6; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void x_finished_1 (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP:                     // 単押しで「英数」と「無変換」  Lowerレイヤーがトグルされている場合はレイヤーをオフにする
        if (IS_LAYER_ON(_LOWER)){
            #ifdef AUDIO_ENABLE
              PLAY_SONG(layer_lock_off_song);
            #endif
            layer_off(_LOWER);
        } else {
        register_code(KC_MHEN);
        register_code(KC_LANG2);
        }
        break;
    case SINGLE_HOLD:                  // 長押しでLowerレイヤーをオンにする
        layer_on(_LOWER);
        break;
    case DOUBLE_TAP:                   // ダブルタップでLowerレイヤーをトグル
        layer_invert(_LOWER);
        if (IS_LAYER_ON(_LOWER)){
            #ifdef AUDIO_ENABLE
              PLAY_SONG(layer_lock_on_song);
            #endif
        } else {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(layer_lock_off_song);
            #endif
        }
        break;
  }
}

void x_reset_1 (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_LANG2);
        unregister_code(KC_MHEN);
        break;
    case SINGLE_HOLD:
        layer_off(_LOWER);
        break;
    case DOUBLE_TAP:  break;
  }
  xtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
 [X_TAP_DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_1, x_reset_1),
};
#endif
