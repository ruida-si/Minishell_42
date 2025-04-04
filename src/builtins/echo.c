/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:55:02 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/03 17:39:48 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_new_line(char *s, int	*a);
void	print_quotes(char *s);
char	*get_new_str(char *s);
int		multiple_nl(char **av, int *a);

// MINISHELL
void	print_echo(char **av);

void	print_echo(char **av)
{
	int	i;
	int	a;

	i = 1;
	a = multiple_nl(av, &i);
	while (av[i])
	{
		print_quotes(av[i]);
		i++;
		if (av[i])
			write(1, " ", 1);
	}
	if (a)
		write(1, "\n", 1);
}

int	multiple_nl(char **av, int *a)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_new_line(av[i], a))
			break ;
		i++;
	}
	if (i == 1)
		return (1);
	else
		return (0);	
}

void	print_quotes(char *s)
{
	int i;
	char c;

	i = 0;
	while (s[i])
	{
		if (char_quotes(s[i]))
		{
			c = s[i++];
			while (s[i] != c)
			{
				write(1, &s[i], 1);
				i++;
			}
		}
		else
			write(1, &s[i], 1);
		i++;
	}
}

int	check_new_line(char *s, int	*a)
{
	int	i;

	s = get_new_str(s);
	if (s)
	{
		i = 1;
		if (ft_strncmp(s, "-n", 2) == 0)
		{
			while (s[i] == 'n')
				i++;
			if (s[i])
			{
				free(s);
				return (1);
			}				
			else
			{
				(*a)++;
				free(s);
				return (0);
			}
		}
		free(s);
	}
	return (1);
}

// extract quotes from string
char	*get_new_str(char *s)
{
	char	*str;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	str = ft_strdup(s);
	while (s[i])
	{
		if (char_quotes(s[i]))
		{
			c = s[i++];
			while (s[i] != c)
			{
				str[j++] = s[i++];				
			}
			i++;
		}
		else
			str[j++] = s[i++];
	}
	str[j] = '\0';
	return (str);
}
