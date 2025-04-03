/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:06:57 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/03 17:42:43 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_child(int j, t_mini *mini);
void	child_process(t_mini *mini, int i, int j);

// MINISHELL
void	close_pipes(t_mini *mini);
void	create_pipes(int j, t_mini *mini);

void	execute(t_mini *mini)
{
	int j;

	j = count_arrays(mini->ap);
	create_pipes(j -1, mini);
	create_child(j, mini);
	close_pipes(mini);
}

void	create_child(int j, t_mini *mini)
{
	int	i;
	int	*pid;

	pid = malloc(sizeof(int) * j);
	i = 0;
	while (i < j)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			ft_printf("Could not fork\n");
			exit(127);
		}
		if (pid[i] == 0)
			child_process(mini, i, j);
		i++;
	}
	i = 0;
	while (i < j)
	{
		waitpid(pid[i], NULL, 0);
		i++;	
	}
}

void	redir_child(int i, int j, t_mini *mini)
{
	int	*pipes;

	pipes = mini->pipes;	
	if (i > 0)
	{
		close(STDIN_FILENO);
		if (dup(pipes[(i -1) * 2]) == -1)
			perror("Error dup failure");		
	}
	if (i < j -1)
	{		
		close(STDOUT_FILENO);
		if (dup(pipes[i * 2 + 1]) == -1)
			perror("Error dup failure");
	}	
}

void	child_process(t_mini *mini, int i, int j)
{
	char	**cmd;
	char	*path;

	(void)j;
		
	redir_child(i, j, mini);
	close_pipes(mini);
	cmd = ft_split_redir(mini->ap[i], ' ', 1, mini);
	if (!cmd)
		ft_printf("Error split child\n");	
	path = find_path(cmd[0]);
	if (!path)
		exit(127);
	execve(path, cmd, mini->envp);
	printf("Failed execve\n");
	exit(1);
}

