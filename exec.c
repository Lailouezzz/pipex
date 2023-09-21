/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:39:11 by ale-boud          #+#    #+#             */
/*   Updated: 2023/09/21 02:42:37 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execpipex(t_pipexctx *ctx)
{
	pid_t	pid;
	int		s;

	pid = fork();
	if (pid == -1)
		errorerrno(ctx);
	if (pid == 0)
		execpipex_child(ctx);
	wait(&s);
	return (s);
}
