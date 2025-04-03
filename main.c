#include "minishell.h"

int main(int argc, char *argv[], char **envp)
{
	t_mini	ms;

	(void)(argc);
	(void)(argv);
	ms = init(envp);
	while(1)
	{
		ms.input = get_input(&ms, ms.prompt);
		if (check_closed_quotes(ms.input))
		{
			ms.input = expand(ms.input);
			ms.av = ft_split_quotes(ms.input, ' ', 0);		
			ms.ap = ft_split_quotes(ms.input, '|', 0);
			if (parsing(&ms))
				print_echo(ms.av);
			free_mem(ms.av);
			free_mem(ms.ap);
		}
		free(ms.input);		
	}
}
