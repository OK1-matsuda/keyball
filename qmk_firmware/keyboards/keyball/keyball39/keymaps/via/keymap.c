/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    LCTL_T(KC_A), LSFT_T(KC_S), KC_D, KC_F, LALT_T(KC_G),                          RALT_T(KC_H),LGUI_T(KC_J),KC_K, RSFT_T(KC_L), RCTL_T(KC_SCLN),
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LCTL  , KC_LGUI  , KC_LALT  ,KC_BSPC,LT(1,KC_ENT),LT(3,KC_ESC)   ,LT(3,KC_TAB),LT(2,KC_SPC),LSFT_T(KC_LNG2),KC_RALT,KC_RGUI, KC_DEL
  ),

  [1] = LAYOUT_universal(
    KC_EXLM  , S(KC_2)  , S(KC_3)  , KC_DLR   , S(KC_5)  ,                            S(KC_6)  , S(KC_7)  , S(KC_8)  , S(KC_9)  , S(KC_0)  ,
    _______  ,LSFT_T(KC_NUHS), KC_LBRC  , KC_RBRC  , KC_LALT  ,                  RALT_T(KC_EQL), KC_MINS  , _______  ,RSFT_T(S(KC_QUOT)),RCTL_T(KC_QUOT),
    _______  ,S(KC_NUHS),S(KC_LBRC),S(KC_RBRC), _______  ,                           S(KC_EQL),S(KC_MINS) , _______  , _______  , _______   ,
    _______  , _______   , _______  , _______  , _______  , _______  ,      _______    , _______    , _______  , _______  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  , KC_7     , KC_8     , KC_9     , _______  ,                            S(KC_6)  , S(KC_7)  , S(KC_8)  , S(KC_9)  , S(KC_0)   ,
    KC_LCTL  ,LSFT_T(KC_4), KC_5    , KC_6     ,KC_LALT   ,                        RALT_T(KC_EQL), KC_MINS  , _______  ,RSFT_T(S(KC_QUOT)),RCTL_T(KC_QUOT),
    KC_0     , KC_1     , KC_2     , KC_3     ,KC_0      ,                           S(KC_EQL)  ,S(KC_MINS), _______  , _______  , _______  ,
    _______  , _______  , _______  , _______   , _______   , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),
    
  [3] = LAYOUT_universal(
  _______   , KC_F7      , KC_F8    , KC_F9   , KC_F12   ,                            LGUI_T(KC_LEFT), LGUI_T(KC_DOWN), LGUI_T(KC_UP), LGUI_T(KC_RGHT), _______ ,
  _______   , KC_F4      , KC_F5    , KC_F6   , KC_F11   ,                            KC_LEFT  , KC_DOWN  , KC_UP   , KC_RGHT  , _______  ,
  _______   , KC_F1      , KC_F2    , KC_F3   , KC_F10   ,                            _______  , KC_PGDN , KC_PGUP , _______  , _______ ,
  _______   , _______    , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),
  
  [4] = LAYOUT_universal(
  _______  , _______   , _______  , _______  , _______  ,                            _______  , _______  , _______ , _______ , _______ ,
  _______  , _______  , _______  , _______  , _______ ,                            _______  , KC_BTN1  , KC_BTN2    , _______  , _______  ,
  _______ , _______  , _______  , _______  , _______ ,                            _______  , _______ , _______ , _______  , _______ ,
  _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [5] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , KBC_RST  , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
  
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
  keyball_handle_auto_mouse_layer_change(state);
#endif
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
