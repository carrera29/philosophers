NAME  	= philo

INC_DIR	= ./include
SRC_DIR	= ./src
OBJ_DIR	= ./obj

SRC		= 	ending_program.c \
			initialization.c \
			main.c \
			utils.c

OBJ		= 	$(SRC:%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := $(CPPFLAGS)
CFLAGS 	= 	-Wall -Wextra -Werror -I $(INC_DIR)

all : $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	gcc -c $(CFLAGS) $< -o $@

$(NAME): $(OBJ)
	@gcc $(OBJ) -lm -o $@

debug: CFLAGS += -g
debug: re

clean :
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_DIR)
	
fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re