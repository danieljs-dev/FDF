#cc main.c read_file.c libft/libft.a

-include colors.mk

BLACK       = \033[0;30m
RED         = \033[0;31m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
MAGENTA     = \033[0;35m
CYAN        = \033[0;36m
WHITE       = \033[0;37m

BLACK_BRIGHT    = \033[0;90m
RED_BRIGHT      = \033[0;91m
GREEN_BRIGHT    = \033[0;92m
YELLOW_BRIGHT   = \033[0;93m
BLUE_BRIGHT     = \033[0;94m
MAGENTA_BRIGHT  = \033[0;95m
CYAN_BRIGHT     = \033[0;96m
WHITE_BRIGHT    = \033[0;97m

BG_BLACK       = \033[0;40m
BG_RED         = \033[0;41m
BG_GREEN       = \033[0;42m
BG_YELLOW      = \033[0;43m
BG_BLUE        = \033[0;44m
BG_MAGENTA     = \033[0;45m
BG_CYAN        = \033[0;46m
BG_WHITE       = \033[0;47m

BOLD        = \033[1m
UNDERLINE   = \033[4m
REVERSE     = \033[7m

RESET   	= \033[0m

define HEADER
███████╗██████╗░███████╗
██╔════╝██╔══██╗██╔════╝
█████╗░░██║░░██║█████╗░░
██╔══╝░░██║░░██║██╔══╝░░
██║░░░░░██████╔╝██║░░░░░
╚═╝░░░░░╚═════╝░╚═╝░░░░░

$(GREEN)(dajesus- "https://github.com/danieljs-dev")$(RESET)

endef
export HEADER

SRCS		=	main.c read_file.c draw.c bresenham.c global_utils.c handle_map.c handle_file.c
HEADERS		= 	fdf.h
NAME		=	fdf
OBJ_DIR		=	build/obj
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
CC			=	cc -Wall -Wextra -Werror -g3
FLAGS	=	MLX42/build/libmlx42.a \
			MLX42/build/_deps/glfw-build/src/libglfw3.a \
			-ldl -pthread -lm -lX11 -lXrandr -lXi -lXcursor \
			-Llibft -lft
# Include paths for MLX42 and libft
INCLUDES	=	-IMLX42/include -Ilibft

MINILIBX_DIR = minilibx-linux
LIBFT_DIR    = libft
PRINTF_DIR   = $(LIBFT_DIR)/ft_printf

# Build object files with includes, ensure MLX42 is built before linking
$(OBJ_DIR)/%.o: %.c ${HEADERS} $(LIBFT_DIR)/libft.a
	@mkdir -p $(OBJ_DIR)
	@${CC} $(INCLUDES) $< -c -o $@

# all: libft MLX42 ${NAME}
all: libft MLX42 print_banner check_modifications ${NAME}

${NAME}: $(OBJS) ${HEADERS} MLX42
	@${CC} $(OBJS) -o ${NAME} ${FLAGS}
	@clear
	@echo "$(RED_BRIGHT)$$HEADER$(RESET)"
	@echo "\r\033[K$(CYAN)FDF $(RED_BRIGHT)is ready!$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR) --no-print-directory

fclean: clean
	@make fclean -C $(LIBFT_DIR) --no-print-directory
	@rm -rf ${NAME}
	@rm -rf build
	@clear
	@echo "$(RED_BRIGHT)$$HEADER$(RESET)"

re: fclean all

libft:
	@make -C $(LIBFT_DIR) --no-print-directory

MLX42:
	@if [ ! -f MLX42/build/libmlx42.a ]; then \
		echo "\r\033[K$(CYAN)Building $(RED)MLX42$(RESET)"; \
		cmake -S MLX42 -B MLX42/build > /dev/null 2>&1 && cmake --build MLX42/build -j4 > /dev/null 2>&1; \
	fi

print_banner:
	@clear
	@echo "$(RED_BRIGHT)$$HEADER$(RESET)"

check_modifications:
	@MODIFIED=0; \
	for src in $(SRCS); do \
		if [ $$src -nt $(NAME) ]; then \
			echo "$(CYAN)File $(YELLOW)$$src$(RESET) has been modified!"; \
			MODIFIED=1; \
		fi; \
	done; \
	if [ $$MODIFIED -eq 0 ]; then \
		echo "make: $(GREEN)'$(NAME)' $(WHITE)is up to $(YELLOW)date.$(RESET)"; \
	fi

 .PHONY: all clean fclean re libft MLX42 print_banner check_modifications