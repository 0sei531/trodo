CC = gcc
CFLAGS = -Werror -Wall -Wextra -Ofast -g3 -flto -march=native -O3 -ffast-math -msse4.2 -mtune=intel -fno-common
INCLUDES = -I Headers -I/usr/include/SDL2
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lm
DEFINES = -D_REENTRANT -fno-strict-aliasing

# Utility source files organized by category
UTILS_SRCS = utils/string.c \
             utils/conversion.c \
             utils/memory.c \
             utils/file.c \
             utils/error.c \
             utils/game.c \
             utils/list.c \
             utils/event_handlers.c \
             utils/key_handlers.c \
             utils/input.c \
             utils/init.c \
             utils/cleanup.c \
             utils/render.c

# Main source files - explicitly include render_game.c
MAIN_SRCS = trodo.c \
            src/parsing.c \
            src/set_minimap.c \
            src/move.c \
            src/rendring.c \
            src/render_game.c \
            src/3DCast.c \
            src/mouse_press.c \
            src/key_press_control.c \
            src/mouse_move.c \
            src/mouse_release.c \
            src/map_animation.c \
            src/design_env.c \
            src/init_multi_imgs.c

SRCS = $(MAIN_SRCS) $(UTILS_SRCS)
OBJS = $(SRCS:.c=.o)
TARGET = trodo

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all
