#include QMK_KEYBOARD_H
#include "muse.h"


enum planck_layers {
  _THUMB,
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _NAV,
  _MOUSE,
  _MEDIA,
  _NUM,
  _SYM,
  _FUN,
  _PLOVER,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  BACKLIT,
  EXT_PLV
};

#define NAV MO(_NAV)
#define MOUSE MO(_MOUSE)
#define MEDIA MO(_MEDIA)
#define NUM MO(_NUM)
#define SYM MO(_SYM)
#define FUN MO(_FUN)

// Tap Dance declarations
enum {
  TD_BRC,
  TD_CBR,
  TD_PRN,
  TD_NUM_BSPC,
  TD_FUN_DEL,
  TD_SCLN,
  TD_QUOT
};

// Tap Dance states
typedef enum {
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_DOUBLE_TAP,
    TD_SINGLE_HOLD
} td_state_t;

// Global instance of the tapdance state type
static td_state_t td_state;

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void td_bspc_finished(qk_tap_dance_state_t *state, void *user_data);
void td_bspc_reset   (qk_tap_dance_state_t *state, void *user_data);
void td_del_finished (qk_tap_dance_state_t *state, void *user_data);
void td_del_reset    (qk_tap_dance_state_t *state, void *user_data);
void td_scln_finished(qk_tap_dance_state_t *state, void *user_data);
void td_quot_finished(qk_tap_dance_state_t *state, void *user_data);

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_BRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  [TD_CBR] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
  [TD_PRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
  [TD_NUM_BSPC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_bspc_finished, td_bspc_reset),
  [TD_FUN_DEL]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_del_finished,  td_del_reset),
  [TD_SCLN]  = ACTION_TAP_DANCE_FN(td_scln_finished),
  [TD_QUOT]  = ACTION_TAP_DANCE_FN(td_quot_finished)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Thumb
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  | Esc  |Space | Tab  |Enter | Bksp | Del  |Rewind| Play |Forwrd|
 * `-----------------------------------------------------------------------------------'
 */
[_THUMB] = LAYOUT_ortho_4x12(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX,         XXXXXXX,           XXXXXXX,         XXXXXXX,         XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX,         XXXXXXX,           XXXXXXX,         XXXXXXX,         XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX,         XXXXXXX,           XXXXXXX,         XXXXXXX,         XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX,
    KC_LCTL, KC_LALT, KC_LGUI, LT(_MEDIA,KC_ESC), LT(_NAV,KC_SPC), LT(_MOUSE,KC_TAB), LT(_SYM,KC_ENT), TD(TD_NUM_BSPC), TD(TD_FUN_DEL), KC_MRWD, KC_MPLY, KC_MFFD
),

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |SftEnt|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |      |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   A  |   R  |   S  |   T  |   G  |   M  |   N  |   E  |   I  |   O  | Vol+ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |   /  | Vol- |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_ortho_4x12(
    XXXXXXX, KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,    KC_J,    KC_L,         TD(TD_SCLN),  TD(TD_QUOT),    XXXXXXX,      XXXXXXX,
    XXXXXXX, LCTL_T(KC_A), LALT_T(KC_R), LGUI_T(KC_S), LSFT_T(KC_T), KC_G,    KC_M,    RSFT_T(KC_N), RGUI_T(KC_E), LALT_T(KC_I),   RCTL_T(KC_O), KC_VOLU,
    XXXXXXX, KC_Z,         RALT_T(KC_X), KC_C,         KC_D,         KC_V,    KC_K,    KC_H,         KC_COMM,      RALT_T(KC_DOT), KC_SLSH,      KC_VOLD,
    _______, _______,      _______,      _______,      _______,      _______, _______, _______,      _______,      _______,        _______,      _______
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   P  |   L  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   E  |   O  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_P,    KC_L,    KC_BSPC,
    KC_ESC,  KC_A,    KC_E,    KC_O,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Navigation
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      | Redo |Paste | Copy | Cut  | Undo |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  | GUI  |Shift |      | Caps | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | RAlt |      |      |      |Insert| Home |PgDown| PgUp | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |MO(11)|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAV] = LAYOUT_ortho_4x12(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, KC_AGIN, KC_PSTE, KC_COPY, KC_CUT,  KC_UNDO, XXXXXXX,
    XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,      XXXXXXX, KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX,      XXXXXXX, KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LT(4,KC_SPC), XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Mouse
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  | GUI  |Shift |      |      |MsLeft|MsDown| MsUp |MsRght|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | RAlt |      |      |      |      |WhLeft|WhDown| WhUp |WhRgth|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      | Btn1 | Btn2 | Btn3 |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_ortho_4x12(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,      XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LT(5,KC_TAB), KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Media
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      | Prvs | Play | Next |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  | GUI  |Shift |      |      |Rewind| Play |Forwrd|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | RAlt |      |      |      |      | Mute | Vol- | Vol+ |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MEDIA] = LAYOUT_ortho_4x12(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI,      KC_LSFT, XXXXXXX, XXXXXXX, KC_MRWD, KC_MPLY, KC_MFFD, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, LT(6,KC_ESC), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Number
 * ,-----------------------------------------------------------------------------------.
 * |      |   7  |   8  |   9  |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   4  |   5  |   6  |      |      |      |Shift | GUI  | Alt  | Ctrl |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |      |      |      |      |      | RAlt |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |   0  |MO(11)|      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = LAYOUT_ortho_4x12(
    XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_4,    KC_5,    KC_6,    XXXXXXX, XXXXXXX, KC_LSFT,       KC_LGUI, KC_LALT, KC_LCTL, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_1,    KC_2,    KC_3,    XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_0,    _______, XXXXXXX, XXXXXXX, LT(7,KC_BSPC), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Symbol
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   _  |   [  |   {  |   (  |   =  |   /  |Shift | GUI  | Alt  | Ctrl |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   ~  |   *  |   -  |   +  |   &  |   \  |      |      | RAlt |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYM] = LAYOUT_ortho_4x12(
    XXXXXXX, KC_EXLM, KC_AT,      KC_HASH,    KC_DLR,     KC_PERC, KC_CIRC,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_UNDS, TD(TD_BRC), TD(TD_CBR), TD(TD_PRN), KC_EQL,  KC_SLSH,      KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, XXXXXXX,
    XXXXXXX, KC_TILD, KC_ASTR,    KC_MINS,    KC_PLUS,    KC_AMPR, KC_BSLS,      XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, LT(8,KC_ENT), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Function
 * ,-----------------------------------------------------------------------------------.
 * |      |  F12 |  F7  |  F8  |  F9  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F11 |  F4  |  F5  |  F6  |      |      |Shift | GUI  | Alt  | Ctrl |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F10 |  F1  |  F2  |  F3  |      |      |      |      | RAlt |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | Menu |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUN] = LAYOUT_ortho_4x12(
    XXXXXXX, KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK, XXXXXXX, KC_LSFT, KC_LGUI,      KC_LALT, KC_LCTL, XXXXXXX,
    XXXXXXX, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, XXXXXXX, XXXXXXX, XXXXXXX,      KC_RALT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_APP,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LT(9,KC_DEL), XXXXXXX, XXXXXXX, XXXXXXX
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_ortho_4x12(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    XXXXXXX, KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    TO(0),   XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |EEPRST| Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Brite |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
    EEP_RST, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL,
    _______, BACKLIT, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK,  DVORAK,  PLOVER,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
  float adjust_song[][2]     = SONG(TERMINAL_SOUND);
#endif

// Activate ADJUST layer and play sound
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _NAV, _NUM, _ADJUST);
  switch (get_highest_layer(state)) {
    case _ADJUST: PLAY_SONG(adjust_song);
    default: break;
  }
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_NAV);
        layer_off(_MOUSE);
        layer_off(_MEDIA);
        layer_off(_NUM);
        layer_off(_SYM);
        layer_off(_FUN);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case NAV:
    case MOUSE:
    case MEDIA:
    case NUM:
    case SYM:
    case FUN:
      return false;
    default:
      return true;
  }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        // Homerow Shifts
        case LSFT_T(KC_T):
        case RSFT_T(KC_N):
            return 250;

        // Thumb keys
        case LT(_MEDIA,KC_ESC):
        case LT(_NAV,KC_SPC):
        case LT(_MOUSE,KC_TAB):
        case LT(_SYM,KC_ENT):
        case TD(TD_NUM_BSPC):
        case TD(TD_FUN_DEL):
            return 200;

        // Lower Tapping Term for ; and ' on u and y key
        case TD(TD_SCLN):
        case TD(TD_QUOT):
            return 250;

        default:
            return TAPPING_TERM;  // 300
    }
}

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }
    if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

// don't interrupt on other keypress
td_state_t cur_dance_hold(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }
    if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

void td_bspc_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance_hold(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_BSPC);
            break;
        case TD_DOUBLE_TAP:
            if (keymap_config.swap_lctl_lgui) {  // Windows/Linux
                tap_code16(LCTL(KC_BSPC));
            } else {  // macOS
                tap_code16(LALT(KC_BSPC));
            }
            break;
        case TD_SINGLE_HOLD:
            layer_on(_NUM);
            break;
        case TD_UNKNOWN:
            break;
    }
}

void td_bspc_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_HOLD:
            layer_off(_NUM);
            break;
        default:
            break;
    }
}

void td_del_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance_hold(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_DEL);
            break;
        case TD_DOUBLE_TAP:
            if (keymap_config.swap_lctl_lgui) {  // Windows/Linux
                tap_code16(LCTL(KC_DEL));
            } else {  // macOS
                tap_code16(LALT(KC_DEL));
            }
            break;
        case TD_SINGLE_HOLD:
            layer_on(_FUN);
            break;
        case TD_UNKNOWN:
            break;
    }
}

void td_del_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_HOLD:
            layer_off(_FUN);
            break;
        default:
            break;
    }
}

void td_scln_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_U);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_U);
            tap_code(KC_U);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_SCLN);
            break;
        case TD_UNKNOWN:
            break;
    }
}

void td_quot_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_Y);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_Y);
            tap_code(KC_Y);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_QUOT);
            break;
        case TD_UNKNOWN:
            break;
    }
}
