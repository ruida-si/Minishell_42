/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:21:37 by ruida-si          #+#    #+#             */
/*   Updated: 2025/03/24 18:16:38 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_3(char *first, char *content, char *last);
char	*expand_dollar(char *s, int i);
void	free_2strings(char *s, char *s1);
void	expand_quotes(char **s, int *a);

// MINISHELL
char	*expand(char *s);

void	free_2strings(char *s, char *s1)
{
	if (s)
		free(s);
	if (s1)
		free(s1);
}

char	*expand(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			update_i(s, &i, s[i]);
		else if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\"')
			{
				if (s[i] == '$')
				{
					expand_quotes(&s, &i);
					break ;
				}
				i++;			
			}							
		}
		else if (s[i] == '$')
			expand_quotes(&s, &i);
		i++;
	}
	return (s);
}

void	expand_quotes(char **s, int *a)
{
	char	*temp;
	
	temp = *s;
	*s = expand_dollar(*s, *a);
	free(temp);
	*a = -1;
}

char	*expand_dollar(char *s, int i)
{
	char	*first;
	char	*last;
	char	*var;
	int		start;
	char	*content;

	content = NULL;
	first = get_str(s, 0, i, 0);
	if (ft_isdigit(s[++i]))
	{
		if (s[i++] == '0')
			content = "minishell";
	}
	else
	{
		start = i;
		while (ft_isalnum(s[i]))
			i++;
		var = get_str(s, start, i, 0);
		content = getenv(var);
		free(var);
	}
	last = ft_join_3(first, content, s + i);
	return (last);	
}

char	*ft_join_3(char *first, char *content, char *last)
{
	char *final;
	char *temp;

	if (content)
	{
		temp = ft_strjoin(first, content);
		final = ft_strjoin(temp, last);
		free_2strings(temp, first);			
	}
	else
	{
		final = ft_strjoin(first, last);
		free(first);
	}
	return (final);
}

