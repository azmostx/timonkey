# ----------------------------
# Makefile Options
# ----------------------------

NAME = TIMONKEY
ICON = icon.png
DESCRIPTION = "Typing game for TI-84 Plus CE."
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
