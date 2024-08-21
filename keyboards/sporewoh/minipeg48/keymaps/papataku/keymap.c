// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "keymap_japanese.h"
#include "twpair_on_jis.h"


typedef union {
  uint32_t raw;
  struct {
    uint8_t     jis_key_trans :2;
  };
} user_config_t;

user_config_t user_config;

enum planck_layers {
  _QWERTY,        // デフォルトレイヤー(JIS配列で認識)
  _LOWER,
  _RAISE,
  _FUNC1,
  _FUNC2,
  _10KEY,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,  // デフォルトレイヤーをJIS(QWERTY配列)に切り替え
  LOWER,
  RAISE,
  MA_0X,            // 0x 代入
  MA_COL1,          // 1 column
  MA_COL2,          // 2 column
  MA_COL3,          // 3 column
  MA_COL4,          // 4 column
  MA_PW0,
  JIS_TOG,          // JIS transrate toggle
  JIS_TOJ,
  JIS_TOU,
};

#define LOW_SP LT(_LOWER,JP_MHEN)
//#define RAI_SP LT(_RAISE,KC_SPC)
#define RAI_SP LT(_RAISE,JP_HENK)

#define ADJ_ESC LT(_ADJUST,KC_ESC)    // タップでESC                 ホールドでADJUSTレイヤーon
#define FN2_TAB LT(_FUNC2,KC_TAB)     // タップでTab                 ホールドでFunction_2レイヤーon
#define FN1_SLS LT(_FUNC1,KC_SLSH)    // タップで/                   ホールドでFunction_1レイヤーon
#define ADJUST  MO(_ADJUST)           // ホールドでAdjustレイヤーをon
#if 1
#define FUNC1   MO(_FUNC1)            // ホールドでFunction1レイヤーをon
#define FUNC2   MO(_FUNC2)            // ホールドでFunction2レイヤーをon
#else
#define FUNC1   LT(_FUNC1, JP_HENK)
#define FUNC2   LT(_FUNC2, JP_MHEN)
#endif
#define AL_PSCR LALT(KC_PSCR)         // ALT + PrintScreen
#define AL_C    LALT(KC_C)            // ALT + C
#define AL_V    LALT(KC_V)            // ALT + V
#define WS_S    SGUI(KC_S)            // WIN + Shift + S
#ifdef KEY_OVERRIDE_ENABLE
#define JIS_OVV QK_KEY_OVERRIDE_TOGGLE
#else
#define JIS_OVV _______
#endif



#ifdef KEY_OVERRIDE_ENABLE
#define KO_LAYER ~0
#define MAKE_KO(from, to) (QK_LSFT & (from)) \
                           ? (&ko_make_basic(MOD_MASK_SHIFT, (QK_LSFT ^ (from)), (to))) \
                           : (&ko_make_with_layers_and_negmods(0, (from), (to), KO_LAYER, (uint8_t) MOD_MASK_SHIFT))
#define MAKE_KO_DIR(from, to, layer) (&ko_make_with_layers_negmods_and_options(0, (from), (to), (layer), MOD_MASK_CSA, ko_option_activation_trigger_down))
#define MAKE_KO_RAI(from, to) MAKE_KO_DIR(from, to, 1<<_RAISE)
const key_override_t **key_overrides = (const key_override_t *[]){

	MAKE_KO_RAI(KC_LCBR, JP_LCBR),      // {
	MAKE_KO_RAI(KC_RCBR, JP_RCBR),      // }
	MAKE_KO_RAI(KC_LBRC, JP_LBRC),      // [
	MAKE_KO_RAI(KC_RBRC, JP_RBRC),      // ]
	MAKE_KO_RAI(KC_EQL,  JP_EQL),       // =
	MAKE_KO_RAI(KC_PLUS, JP_PLUS),      // +
	MAKE_KO_RAI(KC_MINS, JP_MINS),      // -
	MAKE_KO_RAI(KC_ASTR, JP_ASTR),      // *
	MAKE_KO_RAI(KC_UNDS, JP_UNDS),      // _

	MAKE_KO_RAI(KC_TILD, JP_TILD),      // ~
	MAKE_KO_RAI(KC_AT,   JP_AT),        // @
    MAKE_KO_RAI(KC_CIRC, JP_CIRC),      // ^
	MAKE_KO_RAI(KC_AMPR, JP_AMPR),      // &
	MAKE_KO_RAI(KC_ASTR, JP_ASTR),      // *
	MAKE_KO_RAI(KC_LPRN, JP_LPRN),      // (
	MAKE_KO_RAI(KC_RPRN, JP_RPRN),      // )
	MAKE_KO_RAI(KC_PIPE, JP_PIPE),      // |
	MAKE_KO_RAI(KC_DQT,  JP_DQUO),      // "
	MAKE_KO_RAI(KC_LCBR, JP_LCBR),      // {
	MAKE_KO_RAI(KC_RCBR, JP_RCBR),      // }
	MAKE_KO_RAI(KC_LBRC, JP_LBRC),      // [
	MAKE_KO_RAI(KC_RBRC, JP_RBRC),      // ]

	MAKE_KO_RAI(KC_BSLS, JP_BSLS),          /* \ */
	MAKE_KO(KC_SCLN, JP_SCLN),          // ;
	MAKE_KO_RAI(KC_QUOT, JP_QUOT),          // '
	MAKE_KO_RAI(KC_GRV,  JP_GRV),           // `
	MAKE_KO(KC_COLN, JP_COLN),          // :

    NULL
};
#endif

#ifdef COMBO_ENABLE

enum combo_events {
  CMB_HENKA,
  CMB_MUHEN,
};

const uint16_t PROGMEM HEN_combo[] = {KC_LSFT, RAI_SP, COMBO_END};
const uint16_t PROGMEM MUHEN_combo[] = {KC_LSFT, LOW_SP, COMBO_END};
combo_t key_combos[] = {
    [CMB_HENKA] = COMBO_ACTION(HEN_combo),
    [CMB_MUHEN] = COMBO_ACTION(MUHEN_combo),
};
#endif


/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |ADJUST|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ; : | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  , < |  . > |  Up  | /  ? |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | Fn2  |Low   |    Space    |Raise | Fn1  | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,  \
  ADJ_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_SLSH,  \
  KC_LCTL, KC_LGUI, KC_LALT, FUNC2,   LOW_SP,  KC_SPC,  KC_SPC,  RAI_SP,  FUNC1,   KC_LEFT, KC_DOWN, KC_RGHT  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |  7   |  8   |  9   |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |PrintS|      |Ctrl+T|      |      |  4   |  5   |  6   |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      | DEL  | Bksp | Enter|      |      |  1   |  2   |  3   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | App  | XXXX |             |  0   |  .   |  ,   | "0x" |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
  _______, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    _______, _______, \
  _______, _______, AL_PSCR, _______, C(KC_T), _______, _______, KC_4,    KC_5,    KC_6,    _______, _______, \
  _______, _______, KC_DEL,  KC_BSPC, KC_ENT,  _______, _______, KC_1,    KC_2,    KC_3,    _______, _______, \
  _______, _______, _______, KC_APP,  XXXXXXX, _______, _______, KC_0,    KC_DOT,  KC_COMM, MA_0X,   _______ \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  `   |  !   |  @   |  #   |  $   |  %   |  ^   |  &   |  *   |  (   |  )   |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  ~   |      |      |      |      |      |  =   |  -   |  {   |  }   |  '   |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |  +   |  _   |  [   |  ]   |  "   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             | XXXX | App  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
  KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS, \
  KC_TILD, _______, _______, _______, _______, _______, KC_EQL,  KC_MINS, KC_LCBR, KC_RCBR, KC_QUOT, KC_PIPE, \
  _______, _______, _______, _______, _______, _______, KC_PLUS, KC_UNDS, KC_LBRC, KC_RBRC, KC_DQT,  _______, \
  _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_APP,  _______, _______, _______ \
),

/* Function 1
 * ,-----------------------------------------------------------------------------------.
 * |      | F13  | F14  | F15  |      |      |      |      |PrintS|      |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | PGUP | PGDN |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | HOME | END  |      |MU_BT2|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | XXXX |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC1] = LAYOUT_ortho_4x12(
  _______, KC_F13,  KC_F14,  KC_F15,  _______, _______, _______, _______, AL_PSCR, _______, _______, KC_DEL, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END,  _______, KC_BTN2, \
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______, _______, _______ \
),

/* Function 2
 * ,-----------------------------------------------------------------------------------.
 * |      | F1   | F2   | F3   | F4   | F5   |      |   7  |   8  |   9  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | F6   | F7   | F8   | F9   | F10  |      |   4  |   5  |   6  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | F11  | F12  |      |      |      |      |   1  |   2  |   3  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | XXXX |      |             |   0  |   .  |   ,  | "0x" |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC2] = LAYOUT_ortho_4x12(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, KC_7,    KC_8,    KC_9,    _______, _______, \
  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, KC_4,    KC_5,    KC_6,    _______, _______, \
  _______, KC_F11,  KC_F12,  _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    _______, _______, \
  _______, _______, _______, XXXXXXX, _______, _______, _______, KC_0,    KC_DOT,  KC_COMM, MA_0X,   _______ \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | COL1 | COL2 | COL3 | COL4 |      |      | ToJIS|      |JIS_TG|      |RESET |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | XXXX |      |      |      |      |      |      | ToUS |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
  _______, MA_COL1, MA_COL2, MA_COL3, MA_COL4, MA_PW0 , _______, JIS_TOJ, _______, JIS_TOG, _______, QK_BOOT, \
  XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, JIS_TOU, _______, _______, _______, _______, \
  _______, XXXXXXX, XXXXXXX, AL_C,    AL_V,    _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, \
  _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, _______, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX \
)

};
/* clang-format on */





bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
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
    case MA_PW0:
      if (record->event.pressed) {
        register_code(KC_LSFT);
        tap_code(JP_2);
        unregister_code(KC_LSFT);
        SEND_STRING("wsx3edc");
      }
      return false;
      break;
    case JIS_TOG:
      if (record->event.pressed) {
        user_config.jis_key_trans += 1; // Toggles the status
#ifdef KEY_OVERRIDE_ENABLE
        if (3 == user_config.jis_key_trans) {
            user_config.jis_key_trans = 0;
            key_override_off();
        }
        if (2 == user_config.jis_key_trans)
            key_override_on();
        else
            key_override_off();
#else
        if (2 == user_config.jis_key_trans)
            user_config.jis_key_trans = 0;
#endif
      }
      return false;
      break;
    case JIS_TOJ:
      if (record->event.pressed) {
        if (user_config.jis_key_trans == 0) {
            user_config.jis_key_trans = 1;
        } else if (user_config.jis_key_trans == 1) {
            user_config.jis_key_trans = 2;
#ifdef KEY_OVERRIDE_ENABLE
            key_override_on();
#endif
        } else {
            user_config.jis_key_trans = 1;
#ifdef KEY_OVERRIDE_ENABLE
            key_override_off();
#endif
        }
      }
      return false;
      break;
    case JIS_TOU:
      if (record->event.pressed) {
#ifdef KEY_OVERRIDE_ENABLE
        if (user_config.jis_key_trans == 2)
          key_override_off();
#endif
        user_config.jis_key_trans = 0;
      }
      return false;
      break;
  }

  if (1 == user_config.jis_key_trans) {
    // type writer pairing on jis keyboard
    if (!twpair_on_jis(keycode, record))
      return false;
  }

  return true;
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        //case LOW_SP:
        //case RAI_SP:
        case ADJ_ESC:
        case FUNC1:
        case FUNC2:
            return 10;
        default:
            return TAPPING_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        //case LOW_SP:
        //case RAI_SP:
        case ADJ_ESC:
        case FUNC1:
        case FUNC2:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOW_SP:
        //case RAI_SP:
        case ADJ_ESC:
        case FUNC1:
        case FUNC2:
            return true;
        default:
            return false;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOW_SP:
        case RAI_SP:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}


#ifdef COMBO_ENABLE
void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case CMB_HENKA:
      if (pressed) {
        tap_code16(JP_HENK);
        tap_code16(KC_LNG1);
      }
      break;
    case CMB_MUHEN:
      if (pressed) {
        tap_code16(JP_MHEN);
        tap_code16(KC_LNG2);
      }
      break;
  }
}
#endif



void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable=true;
    debug_matrix=true;
#endif

    user_config.jis_key_trans = 1;

#ifdef KEY_OVERRIDE_ENABLE
    if (2 == user_config.jis_key_trans)
        key_override_on();
    else
        key_override_off();
#endif
}

#if 0
void matrix_init_kb(void) {
  debug_enable = true;
  debug_matrix = true;
  debug_mouse  = true;
}
#endif
