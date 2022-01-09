// Copyright 2021 ◤◢◤◢◤◢◤◢ (@yynmt)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
  #include "audio.h"
  float my_song[][2] = SONG(E__NOTE(_E6), E__NOTE(_A6), ED_NOTE(_E7));
#endif

#include "action_layer.h"
#include "keymap_jp.h"
#include "twpair_on_jis.h"

typedef union {
  uint32_t raw;
  struct {
    uint8_t     jis_key_trans :2;
  };
} user_config_t;

user_config_t user_config;

// レイヤー
enum jiskey_layers {
  _QWERTY,        // デフォルトレイヤー(JIS配列で認識)
  _LOWER,
  _RAISE,
  _FUNC1,
  _FUNC2,
  _ADJUST
};

// 特殊な動作のキーコード
enum jiskey_keycodes {
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
  JIS_TOG,          // JIS transrate toggle
  EXT_10K,          // exit 10 key
};

// 特殊な動作のマクロ設定
enum user_macro {
  UM_EMHL,
  UM_KHKF,
  UM_SPRA,
  UM_ECAJ
};

#define M_EMHL MACROTAP(UM_EMHL)      // タップでMacの「英数」とWindowsの「無変換」  ホールドでLowerレイヤー
#define M_KHKF MACROTAP(UM_KHKF)      // タップでMacの「かな」とWindowsの「変換」    ホールドでF1レイヤー
#define M_SPRA MACROTAP(UM_SPRA)      // タップでMacの「かな」とWindowsの「変換」    ホールドでF1レイヤー
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
#ifdef KEY_OVERRIDE_ENABLE
#define JIS_TOG KEY_OVERRIDE_TOGGLE
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

	MAKE_KO(KC_BSLS, JP_BSLS),          /* \ */
	MAKE_KO(KC_SCLN, JP_SCLN),          // ;
	MAKE_KO(KC_QUOT, JP_QUOT),          // '
	MAKE_KO(KC_GRV,  JP_GRV),           // `
	MAKE_KO(KC_COLN, JP_COLN),          // :

    NULL
};
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_QWERTY] = LAYOUT(
                                                                            KC_NO, KC_NO,
        FN2_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_PGUP,
        M_ECAJ,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT, KC_PGDN,
        KC_LSFT,  KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_UP, CK_TOGG,
        KC_LCTL, KC_LGUI, KC_LALT, M_EMHL, M_SPRA, M_KHKF, FUNC2, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_LOWER] = LAYOUT(
                                                                            KC_NO, KC_NO,
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  KC_BSLS, KC_NO,
        KC_NO, KC_NO, AL_PSCR, KC_NO, C(KC_T), KC_NO, KC_NO, KC_4,  KC_5, KC_6, KC_NO, KC_QUOT, KC_NO,
        _______, KC_NO, KC_DEL, KC_BSPC, KC_ENT, KC_NO, KC_NO, KC_1,  KC_2,  KC_3, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_APP, KC_NO, KC_0, KC_DOT, KC_COMM, MA_0X, KC_NO, KC_NO
    ),
    [_RAISE] = LAYOUT(
                                                                            KC_NO, KC_NO,
        KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS, KC_NO,
        KC_TILD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_EQL,  KC_MINS, KC_LCBR, KC_RCBR, KC_QUOT, KC_PIPE, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PLUS, KC_UNDS, KC_LBRC, KC_RBRC, KC_DQT, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_APP, KC_NO, KC_NO, KC_NO
    ),
    [_FUNC1] = LAYOUT(
                                                                            KC_NO, KC_NO,
        KC_NO, KC_F13,  KC_F14,  KC_F15,  KC_NO, KC_NO, KC_NO, KC_NO, AL_PSCR, KC_NO, KC_NO, KC_DEL, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_PGDN, KC_NO, KC_NO, KC_NO,
        _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, KC_END, C(KC_UP), KC_BTN2, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, C(KC_LEFT), C(KC_DOWN), C(KC_RGHT)
    ),
    [_FUNC2] = LAYOUT(
                                                                            KC_NO, KC_NO,
        KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_F11,KC_F12,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
    [_ADJUST] = LAYOUT(
                                                                            KC_NO, KC_NO,
        KC_NO, MA_COL1, MA_COL2, MA_COL3, MA_COL4, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, JIS_TOG, KC_NO, RESET, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    )
};

// サウンド設定
#ifdef AUDIO_ENABLE
  float adjust_on_song[][2]      = SONG(ADJUST_ON_SOUND);       // Adjustキーon
  float adjust_off_song[][2]     = SONG(ADJUST_OFF_SOUND);      // Adjustキーoff
//  float jiskey_on_song[][2]      = SONG(ONE_UP_SOUND);
//  float jiskey_off_song[][2]     = SONG(MARIO_GAMEOVER);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {

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
    case JIS_TOG:
      if (record->event.pressed) {
        user_config.jis_key_trans += 1; // Toggles the status
#ifdef KEY_OVERRIDE_ENABLE
        if (3 == user_config.jis_key_trans)
            user_config.jis_key_trans = 0;
#ifdef AUDIO_ENABLE
        if (0 == user_config.jis_key_trans)
            key_override_on();
        else
            key_override_off();
#endif
#else
        if (2 == user_config.jis_key_trans)
            user_config.jis_key_trans = 0;
#if 0
        if (1 == user_config.jis_key_trans)
            PLAY_SONG(jiskey_on_song);
        else
            PLAY_SONG(jiskey_off_song);
#endif
#endif
        eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM

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

// Macro actions for each corresponding ID.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        case UM_EMHL: // タップで「英数」と「無変換」、ホールドで「Lower」
        return MACRO_TAP_HOLD_LAYER( record, MACRO(T(MHEN), T(LANG2), END), _LOWER );
        case UM_SPRA: // タップで「SPACE」、ホールドで「Raise」
        return MACRO_TAP_HOLD_LAYER( record, MACRO(TYPE(KC_SPC), END), _RAISE );
        case UM_KHKF: // タップで「かな」と「変換」、ホールドで「FUNC1」
        return MACRO_TAP_HOLD_LAYER( record, MACRO(T(HENK), T(LANG1), END), _FUNC1 );
        case UM_ECAJ: // タップで「ESC」,ホールドで「Adjust」
        return MACRO_TAP_HOLD_LAYER( record, MACRO(TYPE(KC_ESC), END), _ADJUST );
        };
        return MACRO_NONE;
}



#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(50); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}
//
// void music_on_user(void)
// {
//     music_scale_user();
// }
//
// void music_scale_user(void)
// {
//     PLAY_SONG(music_scale);
// }

#endif

void keyboard_post_init_user(void) {
#ifdef AUDIO_ENABLE
    audio_on();
#endif
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();

#ifdef KEY_OVERRIDE_ENABLE
    if (2 == user_config.jis_key_trans)
        key_override_on();
    else
        key_override_off();
#endif
}
