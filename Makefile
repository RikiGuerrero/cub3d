

NAME		= cub3D

CFLAGS		= -g -Wall -Wextra -Werror

MLX42_DIR	= ./MLX42
MLX42_INC	= $(MLX42_DIR)/include
MLX42_LIB	= $(MLX42_DIR)

INC			= -I. -I/usr/local/include -I$(MLX42_INC)

RC_DIR 		= game/
PR_DIR		= parsing/
OBJ_DIR		= obj/
SRC_DIR		= src/

SRC_FILES	= main
PR_FILES	= check_map check parse_cub texture init_struct
RC_FILES	= gameLoop moves rayCasting renderWalls
SRC_FILES 	+= $(addprefix $(RC_DIR), $(RC_FILES))
SRC_FILES 	+= $(addprefix $(PR_DIR), $(PR_FILES))

SRCS 		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJF		=	.cache_exists

LIBFT		= libft/libft.a



NO_COLOR	=\033[0m
BOLD		=\033[1m
RED			=\033[31;1m
GREEN		=\033[32;1m
YELLOW		=\033[33;1m
BLUE		=\033[34;1m

LIBS		= -L/usr/local/lib -L$(MLX42_LIB) -lmlx42 -lglfw -ldl -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)Compiling $(NAME)...$(NO_COLOR)"
	# @gcc $(CFLAGS) $(OBJS) $(MLX) -lglfw -L $(BREW) $(INC) -g -o $(NAME) $(LIBFT)
	@gcc $(CFLAGS) $(INC) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME) -lreadline > /dev/null
	@echo "$(GREEN)Compilation of $(NAME) done!$(NO_COLOR)"

libft/libft.a:
	@echo "$(YELLOW)Compiling libft...$(NO_COLOR)"
	@make -s all -C libft > /dev/null
	@echo "$(GREEN)Compilation of libft done!$(NO_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@echo "$(YELLOW)Compiling $<...$(NO_COLOR)"
	@gcc $(CFLAGS) $(INC) -c $< -o $@ > /dev/null

$(OBJF):
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)$(RC_DIR)
			@mkdir -p $(OBJ_DIR)$(PR_DIR)

clean:
	@echo "$(YELLOW)Cleaning objects...$(NO_COLOR)"
	@rm -f $(OBJS) > /dev/null
	@make clean -C libft > /dev/null
	@echo "$(GREEN)Cleaning done.$(NO_COLOR)"

fclean: clean
	@echo "$(YELLOW)Cleaning executable...$(NO_COLOR)"
	@rm -f $(NAME) > /dev/null
	@make fclean -C libft > /dev/null
	@echo "$(GREEN)Cleaning done.$(NO_COLOR)"

re: fclean all

.PHONY: all clean fclean re