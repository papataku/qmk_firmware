/* Copyright 2018-2020 eswai <@eswai>
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

/*

  OSで日本語キーボード(logical bit pairing)と設定/認識されているキーボードで、
  USキーキャップの文字、記号(typewriter pairing)を正しく出力する。

  例: Shift + 2 で @ を入力する

  変換された文字はキーリピートが無効です。

*/

#include QMK_KEYBOARD_H
#include "keymap_jp.h"

const uint16_t us2jis[][2] = {
  {KC_LPRN, JP_LPRN},
  {KC_RPRN, JP_RPRN},
  {KC_AT,   JP_AT},
  {KC_LBRC, JP_LBRC},
  {KC_RBRC, JP_RBRC},
  {KC_LCBR, JP_LCBR},
  {KC_RCBR, JP_RCBR},
  {KC_MINS, JP_MINS},
  {KC_EQL,  JP_EQL},
  {KC_BSLS, JP_BSLS},
  {KC_SCLN, JP_SCLN},
  {KC_QUOT, JP_QUOT},
  {KC_GRV,  JP_GRV},
  {KC_PLUS, JP_PLUS},
  {KC_COLN, JP_COLN},
  {KC_UNDS, JP_UNDS},
  {KC_PIPE, JP_PIPE},
  {KC_DQT,  JP_DQT},
  {KC_ASTR, JP_ASTR},
  {KC_TILD, JP_TILD},
  {KC_AMPR, JP_AMPR},
  {KC_CIRC, JP_CIRC},
};

bool twpair_on_jis(uint16_t keycode, keyrecord_t *record) {
  static bool lshift = false;
  static bool rshift = false;
  static bool is_shift_jis_key = false;
  static uint16_t is_shift_jis_last = 0xFFFF;

  uint16_t skeycode; // シフトビットを反映したキーコード
  bool lshifted = keyboard_report->mods & MOD_BIT(KC_LSFT); // シフトキーの状態
  bool rshifted = keyboard_report->mods & MOD_BIT(KC_RSFT);
  bool shifted = lshifted | rshifted;

  if (KC_LSFT == keycode) {
    if (record->event.pressed) {
      if (is_shift_jis_key) {
        if (lshift || rshift) {
          unregister_code(us2jis[is_shift_jis_last][1]);
          if (!((us2jis[is_shift_jis_last][1] & QK_LSFT) == QK_LSFT || (us2jis[is_shift_jis_last][1] & QK_RSFT) == QK_RSFT)) {
            if (rshift) register_code(KC_RSFT);
          }
        } else {
          unregister_code(us2jis[is_shift_jis_last][1]);
          if ((us2jis[is_shift_jis_last][1] & QK_LSFT) == QK_LSFT || (us2jis[is_shift_jis_last][1] & QK_RSFT) == QK_RSFT)
            unregister_code(KC_LSFT);
        }
        is_shift_jis_key = false;
        is_shift_jis_last = 0xFFFF;
      }
      register_code(keycode);
    } else {
      if (is_shift_jis_key) {
        if (lshift || rshift) {
          unregister_code(us2jis[is_shift_jis_last][1]);
          if (!((us2jis[is_shift_jis_last][1] & QK_LSFT) == QK_LSFT || (us2jis[is_shift_jis_last][1] & QK_RSFT) == QK_RSFT))
            if (rshift) register_code(KC_RSFT);
        } else {
          unregister_code(us2jis[is_shift_jis_last][1]);
        }
        is_shift_jis_key = false;
        is_shift_jis_last = 0xFFFF;
      }
      unregister_code(keycode);
    }
    return false;
  }

  if (!is_shift_jis_key) {
    if (shifted) {
      skeycode = QK_LSFT | keycode;
    } else {
      skeycode = keycode;
    }
  } else {
    if (lshift || rshift) {
      skeycode = QK_LSFT | keycode;
    } else {
      skeycode = keycode;
    }
  }

  for (int i = 0; i < sizeof(us2jis) / sizeof(us2jis[0]); i++) {
    if (us2jis[i][0] == skeycode) {
      /* 該当コードがある場合 */

      if (record->event.pressed) {

        if (0xFFFF != is_shift_jis_last) {
          /* すでに他のコンバートキーが入っている場合 */
          if (lshift || rshift) {
            /* 前回のキーを取り下げ */
            unregister_code(us2jis[is_shift_jis_last][1]);
            if (!((us2jis[is_shift_jis_last][1] & QK_LSFT) == QK_LSFT || (us2jis[is_shift_jis_last][1] & QK_RSFT) == QK_RSFT)) {
              if (lshift) register_code(KC_LSFT);
              if (rshift) register_code(KC_RSFT);
            }
          } else {
            unregister_code(us2jis[is_shift_jis_last][1]);
            if ((us2jis[is_shift_jis_last][1] & QK_LSFT) == QK_LSFT || (us2jis[is_shift_jis_last][1] & QK_RSFT) == QK_RSFT)
              unregister_code(KC_LSFT);
          }
        }

        /* 現状のシフト状況を記録 */
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);

        if (lshift || rshift) {
          if (!((us2jis[i][1] & QK_LSFT) == QK_LSFT || (us2jis[i][1] & QK_RSFT) == QK_RSFT)) {
            if (lshift) unregister_code(KC_LSFT);
            if (rshift) unregister_code(KC_RSFT);
          }
          /*
           * @の場合、必ず英数入力にする
           */
          if (us2jis[i][1] == JP_AT) {
            tap_code(KC_MHEN);
            tap_code(KC_LANG2);
          }
          register_code(us2jis[i][1]);
        } else {
          if ((us2jis[i][1] & QK_LSFT) == QK_LSFT || (us2jis[i][1] & QK_RSFT) == QK_RSFT) {
            register_code(KC_LSFT);
          }
          register_code(us2jis[i][1]);
        }
        is_shift_jis_last = i;
        is_shift_jis_key = true;

        return false;

      } else {
        /* unpless */

        if (is_shift_jis_key) {
          if (i == is_shift_jis_last) {
            /* 押し込みと同じ入力 */
            if (lshift || rshift) {
              unregister_code(us2jis[is_shift_jis_last][1]);
              if (!((us2jis[is_shift_jis_last][1] & QK_LSFT) == QK_LSFT || (us2jis[is_shift_jis_last][1] & QK_RSFT) == QK_RSFT)) {
                if (lshift) register_code(KC_LSFT);
                if (rshift) register_code(KC_RSFT);
              }
            } else {
              unregister_code(us2jis[is_shift_jis_last][1]);
              if ((us2jis[i][1] & QK_LSFT) == QK_LSFT || (us2jis[i][1] & QK_RSFT) == QK_RSFT)
                unregister_code(KC_LSFT);
            }
            is_shift_jis_key = false;
            is_shift_jis_last = 0xFFFF;
          }
        }

        return false;
      }
    }

  }

  return true;
}
