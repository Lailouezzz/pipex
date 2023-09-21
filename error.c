/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:01:03 by ale-boud          #+#    #+#             */
/*   Updated: 2023/09/21 14:58:50 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

noreturn void	help(char *pn)
{
	ft_printf("Usage: %s file1 cmd1 cmd[n]... file2\n\
    OR %s here_doc LIMITER cmd1 cmd2 file\n", pn, pn);
	exit(EXIT_FAILURE);
}

noreturn void	ioerror(t_pipexctx *ctx, char *fn)
{
	destroy(ctx);
	ft_putstr_fd(ctx->pn, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(fn, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

noreturn void	errorerrno(t_pipexctx *ctx)
{
	destroy(ctx);
	ft_putstr_fd(ctx->pn, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

noreturn void	error(t_pipexctx *ctx, char *str)
{
	destroy(ctx);
	ft_putstr_fd(ctx->pn, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
