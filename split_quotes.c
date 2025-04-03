/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:05:22 by ruida-si          #+#    #+#             */
/*   Updated: 2025/03/24 20:07:49 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// MINISHELL.H
int		find_quotes(char *s);
char	**ft_split_quotes(char *s, char c, int option);
int		count_strings(char *s, char c);

void	update_i(char *s, int *i, char c);
char	*get_str(char *s, int start, int end, int option);

// count strings - ft_split with quotes
int	count_strings(char *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		j++;
		while (s[i] && s[i] != c)
		{
			if (s[i] == '\'' || s[i] == '\"')
				update_i(s, &i, s[i]);
			i++;
		}
	}
	return (j);
}

// split with quotes
// option 1 removes quotes 0 not
char	**ft_split_quotes(char *s, char c, int option)
{
	int		i;
	int		j;
	int		start;
	char	**av;

	i = 0;
	j = 0;
	av = malloc(sizeof(char *) * (count_strings(s, c) + 1));
	if (!av)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;		
		if (!s[i])
			break ;
		start = i;
		while (s[i] && s[i] != c)
		{
			if (s[i] == '\'' || s[i] == '\"')
				update_i(s, &i, s[i]);
			i++;
		}
		av[j++] = get_str(s, start, i, option);
	}
	av[j] = NULL;
	return (av);
}

// get string between 2 ends
// 1 removes quotes 0 not
char	*get_str(char *s, int start, int end, int option)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(end - start + 1);
	if (!str)
		return (NULL);
	while (start < end)
	{
		if (option && (s[start] == '\'' || s[start] == '\"'))
		{
			start++;
		}
		else
		{
			str[i++] = s[start++];
		}
	}
	str[i] = '\0';
	return (str);
}

// increment i till found char c
void	update_i(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
}
