/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:35:07 by ruida-si          #+#    #+#             */
/*   Updated: 2025/03/25 15:02:43 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	openfile(char *file, int option, t_mini *mini);
int	execute_redir(char *s, char *file, t_mini *mini);
int	is_redir(char *s);
void	free_mem2(char **av, int i);

// MINISHELL
char	**extract_redir(char **av, t_mini *mini);
int	count_arrays(char **av);

void	free_mem2(char **av, int i)
{
	while (i >= 0)
		free(av[i--]);
	free(av);
}

char	**extract_redir(char **av, t_mini *mini)
{
	char **ap;
	int	i;
	int	j;

	i = count_arrays(av) + 1;
	ap = malloc(sizeof(char *) * i);
	if (!ap)
		return (NULL);
	i = 0;
	j = 0;
	while (av[i])
	{
		if (is_redir(av[i]))
		{
			if (!execute_redir(av[i], av[i + 1], mini))
			{
				free_mem2(av, --i);
				return (NULL);				
			}
			i+= 2;
		}
		else
			ap[j++] = av[i++];
	}
	ap[j] = NULL;
	return (ap);
}

int	is_redir(char *s)
{
	if (ft_strncmp(s, ">>", 2) == 0)
	{
		return (1);
	}
	else if (ft_strncmp(s, "<", 1) == 0)
	{
		return (1);		
	}		
	else if (ft_strncmp(s, ">", 1) == 0)
	{
		return (1);		
	}	
	return (0);
}

// return number of strings
int	count_arrays(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

int	execute_redir(char *s, char *file, t_mini *mini)
{
	int	fd;
	
	if (ft_strncmp(s, "<", 1) == 0)
		fd = openfile(file, 0, mini);
	else if (ft_strncmp(s, ">>", 2) == 0)
		fd = openfile(file, 2, mini);
	else if (ft_strncmp(s, ">", 1) == 0)
		fd = openfile(file, 1, mini);
	return (fd);
}

// OPEN FILE
// 0-RD_ONLY   1-WR_ONLY   2-APPEND
int	openfile(char *file, int option, t_mini *mini)
{
	int fd;
	
	(void)mini;
	if (option == 0)
		fd = open(file, O_RDONLY);
	else if (option == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (option == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_printf("minishell: %s: %s\n", file, strerror(errno));
		return (0);
	}
	else
	{
		if (option == 0)
			close(STDIN_FILENO);
		else
			close(STDOUT_FILENO);
		dup (fd);
		close(fd);
	}
	return (1);
}

