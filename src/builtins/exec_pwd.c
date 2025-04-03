/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:34:42 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/03 17:42:11 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pwd(t_token *token)
{
	char	*current_path;
	char	buffer[BUFFER_SIZE];

	(void)token;
	current_path = getcwd(buffer, BUFFER_SIZE);
	if (!current_path)
	{
		perror("pwd");
		return ;
	}
	printf("%s\n", current_path);
}
