/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <ruida-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:20:36 by gribeiro          #+#    #+#             */
/*   Updated: 2025/04/21 17:45:58 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getpid(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_printf_fd(2, "Failed fork");
	if (pid == 0)
		exit(0);
	wait(0);
	return (pid - 1);
}
