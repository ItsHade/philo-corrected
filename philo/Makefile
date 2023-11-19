SRC_DIR := src
OBJ_DIR := obj
SRC = 	ft_put.c \
	philo.c \
	thread.c \
	utils.c \
	verif.c \
	mutex.c \
	init.c

SRC        := $(SRC:%=$(SRC_DIR)/%)
OBJ        := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

RM = rm -f


MAKEFLAGS   += --no-print-directory

DIR_DUP = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
	$(info CREATED $(NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
		$(RM) -r $(OBJ_DIR)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
.SILENT:
