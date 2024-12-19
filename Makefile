#cc main.c read_file.c libft/libft.a

SRCS		=	main.c read_file.c draw.c
HEADERS		= 	fdf.h
NAME		=	fdf
CC			=	cc -Wall -Wextra -Werror
FLAGS	=	-lm -Lminilibx_linux -lmlx -Llibft -lft -lXext -lX11 # minilibx-linux
#FLAGS       = -lm -Llibft -lft -LMLX42/build -lmlx42 -lX11 -lXext

#%.o: %.c ${HEADERS} libft/libft.a MLX42/build/libmlx42.a
%.o: %.c ${HEADERS} libft/libft.a minilibx-linux/libmlx.a # minilibx-linux
	${CC} $< -c -o $@

# all: libft MLX42 ${NAME}
all: libft minilibx-linux ${NAME} # minilibx-linux

${NAME}: ${SRCS:.c=.o} ${HEADERS}
	${CC} ${SRCS:.c=.o} -o ${NAME} ${FLAGS}

clean:
	rm -rf ${SRCS:.c=.o}
	make clean -C libft
	make clean -C minilibx-linux # minilibx-linux
#	make clean -C MLX42

fclean: clean
	make fclean -C libft
	rm -rf libmlx.a # minilibx-linux
#	rm -rf MLX42/build/libmlx42.a
	rm -rf ${NAME}

re: fclean all

libft:
	@make -C libft

 minilibx-linux:
	@make -C minilibx-linux

MLX42:
	@make -C MLX42/build

 .PHONY: all clean fclean re libft minilibx-linux
#.PHONY: all clean fclean re libft MLX42