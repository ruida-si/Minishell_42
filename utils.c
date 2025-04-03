/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:20:19 by ruida-si          #+#    #+#             */
/*   Updated: 2025/03/26 17:24:21 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// MINISHELL
int	check_closed_quotes(char *input);
int	char_quotes(char c);
void	free_mem(char **av);
int	ft_strcmp(char *s1, char *s2);

int	check_closed_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			update_i(input, &i, input[i]);
			if (!input[i])
			{
				printf("Not closed quotes\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	char_quotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	free_mem(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
	{
		printf("Error strcmp: NULL string");
		return (1);
	}
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
