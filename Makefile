NAME = pipex
BONUS_NAME = multi_pipex

CC = cc
CFLAGS = -g -w -Wall -Wextra -Werror
RM = rm -f

OBJ_DIR = ./obj

SRC_SPECIFIC = sources/main.c sources/parsing.c sources/process.c sources/children.c

BONUS_SPECIFIC = sources/bonus/first_child_bonus.c sources/bonus/last_child_bonus.c \
				 sources/bonus/main_bonus.c sources/bonus/middle_child_bonus.c \
				 sources/bonus/parsing_bonus.c sources/bonus/process_bonus.c

COMMOM_SRC = sources/utils.c sources/ft_split.c sources/path.c \
			 sources/error.c sources/arg_split.c

SRC = $(SRC_SPECIFIC) $(COMMOM_SRC)
BONUS = $(BONUS_SPECIFIC) $(COMMOM_SRC)

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJ = $(BONUS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

bonus: $(BONUS_NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(BONUS_NAME)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re

