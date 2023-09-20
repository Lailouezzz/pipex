/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:39:11 by ale-boud          #+#    #+#             */
/*   Updated: 2023/09/20 18:39:27 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	_execpipex_open(t_pipexctx *ctx, const char *fn, int mode, int p)
{
	int	fd;

	fd = open(fn, mode, p);
	if (fd == -1)
		errorerrno(ctx);
	return (fd);
}

static noreturn void	_execpipex_child(t_pipexctx *ctx)
{
	size_t	k;
	t_pipe	p;

	p = (t_pipe){-1, -1};
	k = ctx->nbcmd;
	while (k != 0)
	{
		--k;
		if (p.write != -1)
		{
			if (dup2(p.write, STDOUT_FILENO) != 0)
				errorerrno(ctx);
			close(p.write);
			p = (t_pipe){-1, -1};
		}
	}
}

int	execpipex(t_pipexctx *ctx)
{
	pid_t	pid;
	int		s;

	pid = fork();
	if (pid == -1)
		errorerrno(ctx);
	if (pid == 0)
		_execpipex_child(ctx);
	wait(&s);
	return (s);
}
