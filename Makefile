# Project Name
NAME    = trodo

# Compiler and Flags
CC      = gcc
CFLAGS  = -Werror -Wall -Wextra -Ofast -g3 -flto -march=native -O3 -ffast-math -msse4.2 -mtune=intel -D_REENTRANT -I/usr/include/SDL2

# Directories
SRC_DIR      = src
UTILS_DIR    = utils
HEADERS_DIR  = Headers
IMG_DIR      = img

# Source Files
SRCS = $(NAME).c \
       $(UTILS_DIR)/ft_strlen.c $(UTILS_DIR)/ft_strncmp.c $(UTILS_DIR)/ft_strjoin.c $(UTILS_DIR)/ft_split.c $(UTILS_DIR)/ft_memcpy.c $(UTILS_DIR)/ft_substr.c $(UTILS_DIR)/ft_strchr.c $(UTILS_DIR)/get_next_line.c $(UTILS_DIR)/ft_isdigit.c $(UTILS_DIR)/ft_atoi.c \
       $(UTILS_DIR)/ft_lst_new.c $(UTILS_DIR)/ft_lst.c $(UTILS_DIR)/ft_strnstr.c $(UTILS_DIR)/ft_str_trim.c $(UTILS_DIR)/spaces.c \
       $(SRC_DIR)/parsing.c $(SRC_DIR)/set_minimap.c $(SRC_DIR)/move.c $(SRC_DIR)/key_release.c $(SRC_DIR)/rendring.c $(UTILS_DIR)/error.c $(UTILS_DIR)/close.c \
       $(SRC_DIR)/3DCast.c $(SRC_DIR)/mouse_press.c $(SRC_DIR)/key_press.c $(SRC_DIR)/mouse_move.c $(SRC_DIR)/render_game.c $(SRC_DIR)/mouse_release.c $(SRC_DIR)/map_animation.c $(SRC_DIR)/design_env.c $(SRC_DIR)/init_multi_imgs.c

# Include Headers
INCLUDES = -I $(HEADERS_DIR)

# Libraries
LIBS    = -lSDL2 -lm

# Build Targets
all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) $(LIBS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	rm -rf $(IMG_DIR)/guns $(IMG_DIR)/enemies

re: fclean all

.PHONY: clean fclean all re
