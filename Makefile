
NAME = minishell

# Srcs
SRCS = src/main.c src/input.c src/init.c src/split_quotes.c src/split_redir.c src/ft_printf.c \
		src/expand.c src/parsing.c src/redir.c src/utils.c src/utils_execute.c \
		src/builtins/echo.c src/builtins/execute.c
OBJS = $(SRCS:.c=.o)

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Libs
INCLUDES = -I./libft
LIBS = -lreadline -L./libft -lft

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@make bonus -C ./libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	@make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

valgrind: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes --suppressions=rl.supp -s -q ./minishell

.PHONY: all clean fclean re
