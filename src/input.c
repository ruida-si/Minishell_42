#include "minishell.h"

char *get_input(t_mini *ms, char *prompt)
{
	char *input;
	(void)ms;
	(void)prompt;
	/* char *cwd = getcwd(NULL, 0);
	char *user = getenv("USER");
	char *temp = ft_strjoin_3(user, cwd, '@');
	prompt = ft_strjoin(temp, "$ "); */
//	free_2strings(cwd, temp);
	input = readline(prompt);
	if (!input)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(0);
	}
	if (input && *input)
		add_history(input);
	return input;
}
