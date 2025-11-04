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
██╗░░░░░██╗██████╗░███████╗████████╗
██║░░░░░██║██╔══██╗██╔════╝╚══██╔══╝
██║░░░░░██║██████╦╝█████╗░░░░░██║░░░
██║░░░░░██║██╔══██╗██╔══╝░░░░░██║░░░
███████╗██║██████╦╝██║░░░░░░░░██║░░░
╚══════╝╚═╝╚═════╝░╚═╝░░░░░░░░╚═╝░░░
                                    
$(GREEN)(dajesus- "https://github.com/danieljs-dev")$(RESET)

endef
export HEADER

NAME        = libft.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

INCLUDE     = -I.
SRCS        = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
              ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c\
              ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c\
              ft_strlen.c ft_strncmp.c ft_strrchr.c ft_toupper.c\
              ft_tolower.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c\
              ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c\
              ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c\
              ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c\
              ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c\
			  ft_putunsigned_dec_fd.c ft_putunsigned_hex_fd.c\
			  ft_numlen_dec.c ft_numlen_hex.c ft_max.c ft_abs.c ft_count_words.c

BONUS_SRCS  = ft_lstadd_front.c ft_lstnew.c ft_lstsize.c ft_lstlast.c \
              ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

PRINTF_DIR  = ./ft_printf
PRINTF_LIB  = $(PRINTF_DIR)/libftprintf.a

OBJS        = $(SRCS:%.c=%.o)
OBJS_BONUS  = $(BONUS_SRCS:%.c=%.o)

all: print_banner check_modifications $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $?
	@echo "\r\033[K$(CYAN)LIBFT $(GREEN_BRIGHT)is ready!$(RESET)"
	@sleep 1
	@echo
	@$(MAKE) ft_printf
#	@make -C $(PRINTF_DIR) --no-print-directory
#	@cp $(PRINTF_LIB) . && ar -x libftprintf.a && ar rcs $(NAME) *.o
#	@rm -f libftprintf.a

bonus: $(OBJS_BONUS)
	@ar rcs $(NAME) $?
	@echo "\r\033[K$(CYAN)LIBFT BONUS $(GREEN_BRIGHT)is ready!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
#	@clear
#	@echo "$(RED)$$HEADER$(RESET)"
	@printf "\r$(CYAN)Compiling $(GREEN)$< $(RESET)"
	@sleep 0.05

clean:
	@echo "$(RED)Removing all .o $(RESET)"
	@rm -rf $(OBJS) $(OBJS_BONUS) *.o
	@make -C $(PRINTF_DIR) clean --no-print-directory
	@sleep 0.5
	@clear
	@echo "$(GREEN_BRIGHT)$$HEADER$(RESET)"

fclean: clean
	@echo "$(RED)Removing .a$(RESET)"
	@rm -rf $(NAME)
	@make -C $(PRINTF_DIR) fclean --no-print-directory
	@sleep 0.5
	@clear
	@echo "$(GREEN_BRIGHT)$$HEADER$(RESET)"

re: fclean all

ft_printf:
	@make -C $(PRINTF_DIR) --no-print-directory
	@cp $(PRINTF_LIB) . && ar -x libftprintf.a && ar rcs $(NAME) *.o
	@sleep 2
	@rm -f libftprintf.a

print_banner:
	@clear
	@echo "$(GREEN_BRIGHT)$$HEADER$(RESET)"

check_modifications:
	@MODIFIED=0; \
	for src in $(SRCS); do \
		if [ $$src -nt $(NAME) ]; then \
			echo "$(CYAN)File $(YELLOW)$$src$(RESET) has been modified"; \
			sleep 2; \
			MODIFIED=1; \
		fi; \
	done; \
	for src in $(shell find $(PRINTF_DIR) -name "*.c"); do \
		if [ $$src -nt $(PRINTF_LIB) ]; then \
			echo "$(CYAN)File $(YELLOW)$$src$(RESET) has been modified"; \
			sleep 1; \
			$(MAKE) ft_printf; \
			sleep 1; \
			MODIFIED=1; \
		fi; \
	done; \
	if [ $$MODIFIED -eq 0 ] && test -e $(NAME); then \
		echo "make: $(GREEN)'$(NAME)' $(WHITE)is up to $(YELLOW)date.$(RESET)"; \
	fi

.PHONY: all clean fclean re bonus print_banner check_modifications ft_printf
