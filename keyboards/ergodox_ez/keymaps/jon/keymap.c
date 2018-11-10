// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
#include QMK_KEYBOARD_H
#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0
#define RAISE 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_ergodox(
      // Left
      HYPR(KC_M),KC_1,KC_2,KC_3,KC_4,KC_5,KC_TRNS,
      KC_TRNS,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_TRNS,
      KC_ESCAPE,CTL_T(KC_A),KC_S,KC_D,KC_F,KC_G,
      KC_LSHIFT,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_BSPACE,
      KC_LALT,KC_LGUI,KC_TRNS,KC_TRNS,TT(RAISE),

      // Left thumb cluster
      LCTL(KC_A),KC_TRNS,
      KC_TRNS,
      SFT_T(KC_SPACE),GUI_T(KC_BSPACE),KC_MEDIA_PLAY_PAUSE,

      // Right
      KC_TRNS,KC_6,KC_7,KC_8,KC_9,KC_0,RGB_TOG,
      KC_TRNS,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_TRNS,
      KC_H,KC_J,KC_K,KC_L,RCTL_T(KC_SCOLON),KC_QUOTE,
      KC_TAB,KC_N,KC_M,KC_COMMA,KC_DOT,KC_SLASH,KC_RSHIFT,
      TT(RAISE),KC_TRNS,KC_TRNS,KC_RGUI,KC_RALT,

      // Right thumb cluster
      KC_TRNS,KC_TRNS,
      KC_AUDIO_VOL_UP,
      KC_AUDIO_VOL_DOWN,GUI_T(KC_TAB),SFT_T(KC_ENTER)
  ),

  [RAISE] = LAYOUT_ergodox(
      // Left
      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
      KC_TRNS,KC_AT,KC_EXLM,KC_LBRC,KC_RBRC,KC_PIPE,KC_TRNS,
      KC_TRNS,LCTL_T(KC_MINUS),KC_UNDERSCORE,KC_LPRN,KC_RPRN,KC_EQUAL,
      KC_TRNS,KC_PLUS,KC_HASH,KC_LCBR,KC_RCBR,KC_BSLASH,KC_TRNS,
      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,

      // Left thumb cluster
      KC_TRNS,KC_TRNS,
      KC_DEL,
      KC_TRNS,KC_TRNS,KC_TRNS,

      // Right
      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
      KC_TRNS,KC_CIRC,KC_DOLLAR,KC_ASTERISK,KC_AMPR,KC_TRNS,KC_TRNS,
      KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,KC_TRNS,KC_TRNS,
      KC_TRNS,KC_GRAVE,KC_TILDE,KC_QUOT,KC_DQUO,KC_TRNS,KC_TRNS,
      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,

      // Right thumb cluster
      KC_TRNS, KC_TRNS,
      KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS
  ),
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    // TODO: Make this relevant to the ErgoDox EZ.
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    case 3:
      ergodox_right_led_1_on();
      break;
    case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    default:
      // none
      break;
  }

};

// Respond to changes in LED states from the connected

// state changes such as mic mute.
void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
    rgblight_sethsv_red_at(14);
  } else {
    rgblight_setrgb_at(0, 0, 0, 14);
  }
};
