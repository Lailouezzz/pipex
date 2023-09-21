/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execchild.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 02:41:20 by ale-boud          #+#    #+#             */
/*   Updated: 2023/09/21 03:19:23 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	_execpipex_open(t_pipexctx *ctx, const char *fn,
		int mode, mode_t flag)
{
	int	fd;

	if (flag != 0)
		fd = open(fn, mode, flag);
	else
		fd = open(fn, mode);
	if (fd == -1)
		errorerrno(ctx);
	return (fd);
}

static void	_execpipex_setinout(t_pipexctx *ctx, size_t k, t_pipe p)
{
	int	fd;

	if (k == ctx->nbcmd -1)
	{
		fd = _execpipex_open(ctx, ctx->f2, O_CREAT | O_WRONLY, 0777);
		if (dup2(fd, STDOUT_FILENO) == -1)
			errorerrno(ctx);
		close(fd);
	}
	if (k != 0 && dup2(p.read, STDIN_FILENO) == -1 && close(p.read) == -1)
		errorerrno(ctx);
	if (k == 0)
	{
		fd = _execpipex_open(ctx, ctx->f1, O_RDONLY, 0);
		if (dup2(fd, STDIN_FILENO) == -1)
			errorerrno(ctx);
		close(fd);
	}
}

static void	__execpipex_execute(t_pipexctx *ctx, char **cmdline)
{
	char	*path;

	path = pathexpension(ctx->path, cmdline[0]);
	if (path == NULL)
	{
		ft_putstr_fd(ctx->pn, STDERR_FILENO);
		ft_putstr_fd(": invalid command: ", STDERR_FILENO);
		ft_putstr_fd(cmdline[0], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		destroy(ctx);
		free(path);
		return ;
	}
	execve(path, cmdline, ctx->envp);
	free(path);
	errorerrno(ctx);
}

static void	_execpipex_execute(t_pipexctx *ctx, char **cmdline,
		t_pipe p, size_t k)
{
	pid_t	pid;
	int		s;

	if (k == 0)
	{
		__execpipex_execute(ctx, cmdline);
		wait(&s);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		errorerrno(ctx);
	if (pid == 0)
		return ;
	close(p.write);
	__execpipex_execute(ctx, cmdline);
	wait(&s);
	exit(EXIT_FAILURE);
}

noreturn void	execpipex_child(t_pipexctx *ctx)
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
			if (dup2(p.write, STDOUT_FILENO) == -1)
				errorerrno(ctx);
			close(p.write);
			p = (t_pipe){-1, -1};
		}
		if (k != 0)
			if (pipe((int *)&p) == -1)
				errorerrno(ctx);
		_execpipex_setinout(ctx, k, p);
		_execpipex_execute(ctx, ctx->cmdlines[k], p, k);
	}
	destroy(ctx);
	exit(EXIT_FAILURE);
}
