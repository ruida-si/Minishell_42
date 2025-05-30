/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:46:06 by ruida-si          #+#    #+#             */
/*   Updated: 2025/05/15 11:00:51 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset(char *s, t_mini *ms);
static void	delete_node(t_env *prev, t_env *next);
static void	free_node(t_env *temp);

int	exec_unset(t_mini *ms, int n)
{
	int		i;
	char	**av;

	if (cnt_strings(ms->ap) > 1)
		return (0);
	av = ms->cmd[n].cmd;
	i = 1;
	while (av[i])
	{
		unset(av[i], ms);
		i++;
	}
	return (0);
}

static void	unset(char *s, t_mini *ms)
{
	t_env	*ev;

	s = get_new_str(s);
	ev = ms->export;
	while (ev)
	{
		if (ft_strcmp(s, ev->var) == 0)
		{
			if (ev == ms->export)
				ms->export = ev->next;
			delete_node(ev->prev, ev->next);
			free_node(ev);
			break ;
		}
		ev = ev->next;
	}
	free(s);
}

static void	delete_node(t_env *prev, t_env *next)
{
	if (!prev && !next)
		return ;
	if (prev && next)
	{
		prev->next = next;
		next->prev = prev;
	}
	else if (!prev)
		next->prev = NULL;
	else if (!next)
		prev->next = NULL;
}

static void	free_node(t_env *temp)
{
	if (temp->var)
	{
		free(temp->var);
		temp->var = NULL;
	}
	if (temp->content)
	{
		free(temp->content);
		temp->content = NULL;
	}
	if (temp->content_qts)
	{
		free(temp->content_qts);
		temp->content_qts = NULL;
	}
	free(temp);
}
