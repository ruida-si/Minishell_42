/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:21:37 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/03 18:18:45 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_3(char *first, char *content, char *last);
char	*expand_dollar(char *s, int i, t_mini *mini);
void	free_2strings(char *s, char *s1);
void	expand_quotes(char **s, int *a, t_mini *mini);

// MINISHELL
char	*expand(char *s, t_mini *mini);

void	free_2strings(char *s, char *s1)
{
	if (s)
		free(s);
	if (s1)
		free(s1);
}

char	*expand(char *s, t_mini *mini)
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
					expand_quotes(&s, &i, mini);
					break ;
				}
				i++;			
			}							
		}
		else if (s[i] == '$')
			expand_quotes(&s, &i, mini);
		i++;
	}
	return (s);
}

void	expand_quotes(char **s, int *a, t_mini *mini)
{
	char	*temp;
	
	temp = *s;
	*s = expand_dollar(*s, *a, mini);
	free(temp);
	*a = -1;
}

char	*expand_dollar(char *s, int i, t_mini *mini)
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
	else if (s[i] == '$')
		content = ft_itoa(mini->ppid);
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

