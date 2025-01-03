NAME = pipex

CC = cc
CFLAGS = -g -w -Wall -Wextra -Werror
RM = rm -f

OBJ_DIR = ./obj

SRC_SPECIFIC = sources/main.c \

COMMOM_SRC = sources/parsing.c sources/utils.c sources/utils2.c \
			 sources/ft_split.c sources/process.c sources/path.c \
			 sources/error.c \

SRC = $(SRC_SPECIFIC) $(COMMOM_SRC)

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

