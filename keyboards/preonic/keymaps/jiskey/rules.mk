
MOUSEKEY_ENABLE  = yes
AUDIO_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
TAP_DANCE_ENABLE = yes
RGBLIGHT_ENABLE = no
NKRO_ENABLE = no
KEY_OVERRIDE_ENABLE = yes

CONSOLE_ENABLE = no         # Console for debug(+400)

ifneq ($(strip $(KEY_OVERRIDE_ENABLE)), yes)
  SRC +=  twpair_on_jis.c
endif

