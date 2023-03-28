NAME  	= philo

LIB_DIR	= ./libft
INC_DIR	= ./include
SRC_DIR	= ./src
OBJ_DIR	= ./obj

SRC		= 	ending_program.c \
			initialization.c \
			main.c \
			utils.c

OBJ		= 	$(SRC:%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := $(CPPFLAGS)
CFLAGS 	= 	-Wall -Wextra -Werror -I$(LIB_DIR) -I$(INC_DIR) 

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C $(LIB_DIR)
	@gcc $^ $(CFLAGS) $(LIB_DIR)/libft.a -o $@

$(OBJ) : $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p obj
	gcc -g -c $(CFLAGS) $< -o $@

clean :
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR)
	
fclean : clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB_DIR)

re : fclean all

.PHONY : all clean fclean re