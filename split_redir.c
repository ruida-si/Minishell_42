/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:05:22 by ruida-si          #+#    #+#             */
/*   Updated: 2025/03/24 17:43:24 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// MINISHELL.H
char **ft_split_redir(char *s, char c, int option, t_mini *mini);
void	update_i(char *s, int *i, char c);
char	*get_str(char *s, int start, int end, int option);

int	errors_redir(char *s, int i, int start, t_mini *mini);

/* int main()
{
	char **av = ft_split_quotes("cat |", ' ', 0);
	int i = 0;
	while (av[i])
	{
		printf(".%s.\n", av[i]);
		i++;		
	}		
} */

// count strings - ft_split with quotes
int	count_strings_redir(char *s, char c)
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
		while (s[i] && s[i] != c && !char_redir(s[i]))
		{
			if (s[i] == '\'' || s[i] == '\"')
				update_i(s, &i, s[i]);
			i++;
		}
		if (char_redir(s[i]))
		{
			j++;
			while (char_redir(s[i]))
				i++;
		}
	}
	return (j);
}

// split with quotes
// option 1 removes quotes 0 not
char **ft_split_redir(char *s, char c, int option, t_mini *mini)
{
	t_iter a;
	(void)mini;
	
	a.i = 0;
	a.j = 0;
	a.av = malloc(sizeof(char *) * (count_strings_redir(s, c) + 1));
	if (!a.av)
		return (NULL);
	while (s[a.i])
	{
		while (s[a.i] == c)
			a.i++;
		if (!s[a.i])
			break;
		a.start = a.i;
		while (s[a.i] && s[a.i] != c && !char_redir(s[a.i]))
		{
			if (s[a.i] == '\'' || s[a.i] == '\"')
				update_i(s, &a.i, s[a.i]);
			a.i++;
		}
		if (a.i != a.start)
			a.av[a.j++] = get_str(s, a.start, a.i, option);
		if (char_redir(s[a.i]))
		{
			a.start = a.i;
			while (s[a.i] == s[a.start])
				a.i++;			
			a.av[a.j++] = get_str(s, a.start, a.i, option);
		}
	}
	a.av[a.j] = NULL;
	return (a.av);
}
