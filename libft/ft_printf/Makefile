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

RESET				= \033[0m


define HEADER
██████╗░██████╗░██╗███╗░░██╗████████╗███████╗
██╔══██╗██╔══██╗██║████╗░██║╚══██╔══╝██╔════╝
██████╔╝██████╔╝██║██╔██╗██║░░░██║░░░█████╗░░
██╔═══╝░██╔══██╗██║██║╚████║░░░██║░░░██╔══╝░░
██║░░░░░██║░░██║██║██║░╚███║░░░██║░░░██║░░░░░
╚═╝░░░░░╚═╝░░╚═╝╚═╝╚═╝░░╚══╝░░░╚═╝░░░╚═╝░░░░░   
                                              
$(GREEN)(dajesus- "https://github.com/danieljs-dev")$(RESET)

endef
export HEADER

NAME        = libftprintf.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDE     = -I../ -I.

LIBFT_DIR   = ../
LIBFT       = $(LIBFT_DIR)libft.a

SRCS        = ft_printf.c specifiers.c str_wrappers.c\
              num_wrappers.c hex_wrappers.c ptr_wrappers.c\
              errors.c
OBJS        = $(SRCS:%.c=%.o)

all: print_banner check_modifications $(NAME)

$(NAME): $(OBJS)
	@cp $(LIBFT) $(NAME)
	@ar rcs $(NAME) $?
	@echo "\r\033[K$(CYAN)PRINTF $(MAGENTA)is ready!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
#	@clear
#	@echo "$(RED)$$HEADER$(RESET)"
	@printf "\r$(CYAN)Compiling $(GREEN)$< $(RESET)"
	@sleep 0.04

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@sleep 0.05
	@clear
	@echo "$(MAGENTA)$$HEADER$(RESET)"

re: fclean all

print_banner:
	@clear
	@echo "$(MAGENTA)$$HEADER$(RESET)"

check_modifications:
	@MODIFIED=0; \
	for src in $(SRCS); do \
		if [ $$src -nt $(NAME) ]; then \
			echo "$(CYAN)File $(YELLOW)$$src$(RESET) has been modified!"; \
			sleep 2; \
			MODIFIED=1; \
		fi; \
	done; \
	if [ $$MODIFIED -eq 0 ] && test -e $(NAME); then \
		echo "make: $(GREEN)'$(NAME)' $(WHITE)is up to $(YELLOW)date.$(RESET)"; \
	fi

.PHONY: all clean fclean re print_banner check_modifications
