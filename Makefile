NAME = pipex

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
RM = rm -f

OBJ_DIR = ./obj

SRC_SPECIFIC = sources/main.c sources/parsing.c sources/process.c sources/children.c

BONUS_SPECIFIC = sources/bonus/main/main_bonus.c sources/bonus/main/process_bonus.c \
				 sources/bonus/main/parsing_bonus.c sources/bonus/childrens/first_child_bonus.c \
				 sources/bonus/childrens/last_child_bonus.c sources/bonus/childrens/middle_child_bonus.c \
				 sources/bonus/childrens/here_doc_bonus.c sources/bonus/utils/get_next_line_bonus.c \
				 sources/bonus/utils/get_next_line_utils_bonus.c sources/bonus/utils/close_free_bonus.c

COMMOM_SRC = sources/utils.c sources/ft_split.c sources/path.c \
			 sources/error.c sources/arg_split.c

SRC = $(SRC_SPECIFIC) $(COMMOM_SRC)
BONUS = $(BONUS_SPECIFIC) $(COMMOM_SRC)

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJ = $(BONUS:%.c=$(OBJ_DIR)/%.o)

MODE := normal

all: $(NAME)

bonus:
	@$(MAKE) MODE=bonus all

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(if $(filter bonus, $(MODE)), $(BONUS_OBJ), $(OBJ))
	$(CC) $(CFLAGS) $^ -o $(NAME)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
