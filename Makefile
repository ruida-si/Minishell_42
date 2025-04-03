CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./42-libft
LIBS = -lreadline -L./42-libft -lft
SRCS = main.c input.c init.c split_quotes.c split_redir.c \
		ft_printf.c expand.c echo.c parsing.c redir.c execute.c \
		utils.c utils_execute.c
OBJS = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./42-libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make clean -C ./42-libft
	rm -f $(OBJS)

fclean: clean
	@make fclean -C ./42-libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
