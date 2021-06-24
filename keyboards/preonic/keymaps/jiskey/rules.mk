#BACKLIGHT_ENABLE = yes
MOUSEKEY_ENABLE  = yes
AUDIO_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
COMBO_ENABLE = yes
#TAP_DANCE_ENABLE = yes

CONSOLE_ENABLE = no         # Console for debug(+400)

SRC +=  twpair_on_jis.c

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif

