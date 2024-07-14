# -------------------------------- Colors

CYAN	= \033[0;36m
PURPLE	= \033[0;35m
YELLOW	= \033[33m
GREEN	= \033[0;32m
WHITE	= \033[37m
RED		= \033[31m
RESET	= \033[0m

# -------------------------------- Basic

NAME			= philo
.DEFAULT_GOAL	:= all
.PHONY: all clean fclean re
.SILENT:

# -------------------------------- Sources

INCLUDE		:= -Iinclude/
BUILD_DIR	:= build/
SRC_PATH	= src/
SRC			= $(addprefix $(SRC_PATH), \
			philo.c \
			utils.c \
			init.c)
OBJ			= $(SRC:%.c=$(BUILD_DIR)%.o)

# -------------------------------- 

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -g3
LDLIBS	:= -lpthread
MKDIR	:= mkdir -p

define create_dir
	$(MKDIR) $(dir $@)
endef

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) -o $@

$(BUILD_DIR)%.o: %.c
		$(call create_dir)
		$(CC) $(INCLUDE) -c $< -o $@

clean:
		rm -rf $(BUILD_DIR)

fclean: clean
		rm -rf $(NAME)

re: fclean all