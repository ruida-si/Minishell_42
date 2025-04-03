/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:09:42 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/03 17:40:27 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_3(char *path, char *cmd, char c);
char	*find_path(char *cmd);
void	child_process(t_mini *mini, int	*fd, int i, int j);
void	ft_close_pipes(int *fd, int j);
int	count_arrays(char **av);

void	exec_pipes(t_mini *mini)
{
	int	*pid;
	int	*fd;
	int	j;
	int	i;
	
	i = 0;
	j = count_strings(mini->input, '|') - 1;
	fd = malloc(j * 2 * sizeof(int));
	pid = malloc(j + 2 * sizeof(int));
	mini->pid = pid;
	while (i < j)
	{
		if (pipe(fd + i * 2) == -1)
		{
			perror("Could not create pipe");
			exit(4);
		}
		i++;
	}
	i = 0;
	while (i < j + 1)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("could not fork");
			exit(5);
		}
		if (pid[i] == 0)
			child_process(mini, fd, i, j);
		i++;
	}
	pid[i] = 0;
	ft_close_pipes(fd, j);
	i = 0;
	while (i < j + 1)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

// close j pipes
void	ft_close_pipes(int *fd, int j)
{
	int	i;

	i = 0;
	while (i < j * 2)
	{
		close(fd[i]);
		i++;
	}
}

void	child_process(t_mini *mini, int	*fd, int i, int j)
{
	char	**cmd;
	char	*path;

	if (i > 0)
	{
		if (dup2(fd[(i -1) * 2], STDIN_FILENO) == -1)
			perror("Error dup2 child");
	}
	if (i < j)
	{
		if (dup2(fd[i * 2 + 1], STDOUT_FILENO) == -1)
			perror("Error dup2 child");
	}
	ft_close_pipes(fd, j);
	cmd = ft_split_redir(mini->ap[i], ' ', 1, mini);
	if (!cmd[0])
		ft_printf("minishell: syntax error near unexpected token `|'\n");
	/* cmd = extract_redir(cmd, mini);
	if (!cmd || !cmd[0])
		exit(2); */
	if (access(cmd[0], X_OK) == 0)
		path = cmd[0];
	else
		path = find_path(cmd[0]);
	if (!path)
		exit(127);
	execve(path, cmd, mini->envp);
	printf("Failed execve\n");
	exit(1);
}



char	*find_path(char *cmd)
{
	char	*home;
	char	**path;
	char	*temp;
	int		i;

	i = 0;
	home = getenv("PATH");
	if (!home)
	{
		ft_printf("Not set PATH\n");
		return (NULL);
	}
	path = ft_split(home, ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		temp = ft_strjoin_3(path[i], cmd, '/');
		if (access(temp, X_OK) == 0)
			return (free_mem(path), temp);
		free(temp);
		i++;
	}
	ft_printf("Command '%s' not found\n", cmd);
	return (free_mem(path), NULL);
}

// ft_strjoin char c in between
char	*ft_strjoin_3(char *path, char *cmd, char c)
{
	char	*s;
	int		i;
	int		len;

	if (!path || !cmd)
		return (NULL);
	len = ft_strlen(path) + ft_strlen(cmd);
	s = malloc(len + 2);
	if (!s)
		return (NULL);
	i = 0;
	while (path[i])
	{
		s[i] = path[i];
		i++;
	}
	s[i++] = c;
	while (*cmd)
	{
		s[i] = *cmd++;
		i++;
	}
	s[i] = '\0';
	return (s);
}
