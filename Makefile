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
███████╗██████╗ ███████╗
██╔════╝██╔══██╗██╔════╝
█████╗  ██║  ██║█████╗  
██╔══╝  ██║  ██║██╔══╝  
██║     ██████╔╝██║     
╚═╝     ╚═════╝ ╚═╝     
                        
$(GREEN)(dajesus- "https://github.com/danieljs-dev")$(RESET)

endef
export HEADER

SRCS		=	main.c read_file.c draw.c bresenham.c global_utils.c
HEADERS		= 	fdf.h
NAME		=	fdf
CC			=	cc -Wall -Wextra -Werror
FLAGS	=	-lm -Lminilibx-linux -lmlx -Llibft -lft -lXext -lX11
#FLAGS       = -lm -Llibft -lft -LMLX42/build -lmlx42 -lX11 -lXext

MINILIBX_DIR = minilibx-linux
LIBFT_DIR    = libft
PRINTF_DIR   = $(LIBFT_DIR)/ft_printf

#%.o: %.c ${HEADERS} libft/libft.a MLX42/build/libmlx42.a
%.o: %.c ${HEADERS} $(LIBFT_DIR)/libft.a $(MINILIBX_DIR)/libmlx.a
	@${CC} $< -c -o $@

# all: libft MLX42 ${NAME}
all: libft minilibx-linux print_banner check_modifications ${NAME}

${NAME}: ${SRCS:.c=.o} ${HEADERS}
	@${CC} ${SRCS:.c=.o} -o ${NAME} ${FLAGS}
	@clear
	@echo "$(RED_BRIGHT)$$HEADER$(RESET)"
	@echo "\r\033[K$(CYAN)FDF $(RED_BRIGHT)is ready!$(RESET)"

clean:
	@rm -rf ${SRCS:.c=.o}
	@make clean -C $(LIBFT_DIR) --no-print-directory
	@if [ -d "$(MINILIBX_DIR)" ]; then \
		make clean -C $(MINILIBX_DIR) --no-print-directory > /dev/null 2>&1; \
	fi
#	make clean -C MLX42

fclean: clean
	@make fclean -C $(LIBFT_DIR) --no-print-directory
	@rm -rf libmlx.a
#	rm -rf MLX42/build/libmlx42.a
	@rm -rf ${NAME}
	@rm -rf $(MINILIBX_DIR)
	@clear
	@echo "$(RED_BRIGHT)$$HEADER$(RESET)"

re: fclean all

libft:
	@make -C $(LIBFT_DIR) --no-print-directory

minilibx-linux:
	@if [ ! -d "$(MINILIBX_DIR)" ]; then \
		echo "\r\033[K$(CYAN)Cloning $(RED)minilibx-linux...$(RESET)"; \
		git clone --quiet https://github.com/42Paris/minilibx-linux.git > /dev/null 2>&1; \
	fi
	@make -C $(MINILIBX_DIR) > /dev/null 2>&1
	@sleep 0.5

MLX42:
	@make -C MLX42/build

print_banner:
	@clear
	@echo "$(RED_BRIGHT)$$HEADER$(RESET)"

check_modifications:
	@MODIFIED=0; \
	for src in $(SRCS); do \
		if [ $$src -nt $(NAME) ]; then \
			echo "$(CYAN)File $(YELLOW)$$src$(RESET) has been modified!"; \
			sleep 2; \
			MODIFIED=1; \
		fi; \
	done; \
	if [ $$MODIFIED -eq 0 ]; then \
		echo "make: $(GREEN)'$(NAME)' $(WHITE)is up to $(YELLOW)date.$(RESET)"; \
	fi

 .PHONY: all clean fclean re libft minilibx-linux print_banner check_modifications
#.PHONY: all clean fclean re libft MLX42