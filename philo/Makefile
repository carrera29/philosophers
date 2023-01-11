NAME  	= philo

SRC_DIR	= ./src
INC_DIR	= ./include

SRC		= 	$(SRC_DIR)/control_errors.c \
			$(SRC_DIR)/philo.c \
			$(SRC_DIR)/utils.c		

OBJ 	= 	$(SRC:.c=.o)

CFLAGS 	= 	-Wall -Wextra -Werror -I$(INC_DIR)

$(NAME) : $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(NAME)

%.o : /%.c
	@gcc -c $(CFLAGS) $< -o $@

all : $(NAME)

clean : 
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re