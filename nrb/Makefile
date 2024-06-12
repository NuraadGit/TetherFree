TARGET=iphone:clang:11.2:8.0
ARCHS=arm64 arm64e
include $(THEOS)/makefiles/common.mk

TWEAK_NAME = TetherFreeNRB
TetherFreeNRB_FILES = Tweak.c
TetherFreeNRB_CFLAGS = -I.
TetherFreeNRB_PRIVATE_FRAMEWORKS = Netrb

include $(THEOS_MAKE_PATH)/tweak.mk

after-install::
	install.exec "killall -9 UserEventAgent"
