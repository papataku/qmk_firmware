EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE  = yes
DYNAMIC_MACRO_ENABLE = yes
TAP_DANCE_ENABLE = yes
NKRO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes

CONSOLE_ENABLE = no         # Console for debug(+400)

ifneq ($(strip $(KEY_OVERRIDE_ENABLE)), yes)
  SRC +=  twpair_on_jis.c
endif

