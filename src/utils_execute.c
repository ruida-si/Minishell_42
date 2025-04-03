/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:16:57 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/03 17:41:12 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// MINISHELL
char	*ft_strjoin_3(char *path, char *cmd, char c);
char	*find_path(char *cmd);
void	close_pipes(t_mini *mini);
void	create_pipes(int j, t_mini *mini);

void	create_pipes(int j, t_mini *mini)
{
	int	i;
	int	*pipes;

	pipes = malloc(sizeof(int) * (j * 2 + 1));
	i = 0;	
	while (i < j)
	{
		if (pipe(pipes + i * 2) == -1)
		{
			ft_printf("Could not create a pipe\n");
			exit(127);
		}
		i++;		
	}
	pipes[j * 2] = -1;
	mini->pipes = pipes;
}

void	close_pipes(t_mini *mini)
{
	int	i;
	int	*pipes;

	i = 0;
	pipes = mini->pipes;
	while (pipes[i] != -1)
	{
		close(pipes[i]);
		i++;
	}
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
