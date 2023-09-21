/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:54:13 by ale-boud          #+#    #+#             */
/*   Updated: 2023/09/21 14:24:10 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "gnl.h"

static noreturn void	_here_doc_child(t_pipexctx *ctx)
{
	char	*l;

	write(ctx->outfd, "pipe heredoc> ", 15);
	l = gnl(STDIN_FILENO);
	while (l != NULL
		&& (ft_strncmp(l, ctx->limiter, ft_strlen(ctx->limiter)) != 0
			|| (ft_strlen(l) - 1) != ft_strlen(ctx->limiter)))
	{
		if (write(STDOUT_FILENO, l, ft_strlen(l)) == -1)
		{
			free(l);
			close(STDOUT_FILENO);
			destroy(ctx);
			exit(EXIT_FAILURE);
		}
		free(l);
		write(ctx->outfd, "pipe heredoc> ", 15);
		l = gnl(STDIN_FILENO);
	}
	free(l);
	close(STDOUT_FILENO);
	destroy(ctx);
	exit(EXIT_SUCCESS);
}

static int	_here_doc(t_pipexctx *ctx)
{
	pid_t	pid;
	t_pipe	p;

	if (pipe((int *)&p) == -1)
		errorerrno(ctx);
	pid = fork();
	if (pid < 0)
		errorerrno(ctx);
	if (pid == 0)
	{
		if (dup2(p.write, STDOUT_FILENO) == -1)
			errorerrno(ctx);
		close(p.write);
		if (dup2(ctx->infd, STDIN_FILENO) == -1)
			errorerrno(ctx);
		_here_doc_child(ctx);
	}
	close(p.write);
	return (p.read);
}

int	open_f1(t_pipexctx *ctx)
{
	int	fd;

	if (ctx->here_doc)
		return (_here_doc(ctx));
	fd = open(ctx->f1, O_RDONLY);
	if (fd == -1)
		errorerrno(ctx);
	return (fd);
}

int	open_f2(t_pipexctx *ctx)
{
	int	fd;

	fd = open(ctx->f2, O_CREAT
			| O_WRONLY
			| (O_APPEND * (ctx->here_doc)), 0777);
	if (fd == -1)
		errorerrno(ctx);
	return (fd);
}
