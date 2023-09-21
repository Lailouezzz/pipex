/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:33:55 by ale-boud          #+#    #+#             */
/*   Updated: 2023/09/21 14:37:43 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_arg(int argc, char **argv, char **envp, t_pipexctx *ctx)
{
	if (argc <= 4
		|| (ft_strcmp(argv[1], "here_doc") == 0 && argc != 6))
		help(argv[0]);
	ctx->envp = envp;
	ctx->cmdlines = NULL;
	ctx->f2 = argv[argc - 1];
	ctx->here_doc = ft_strcmp(argv[1], "here_doc") == 0;
	if (ctx->here_doc)
		ctx->limiter = argv[2];
	else
		ctx->limiter = NULL;
	ctx->cmds = argv + (2 + ctx->here_doc);
	ctx->nbcmd = argc - (3 + ctx->here_doc);
	ctx->f1 = argv[1];
	ctx->pn = argv[0];
	ctx->infd = -1;
	ctx->outfd = -1;
	ctx->path = searchpath(envp);
}

static void	_init_execs(t_pipexctx *ctx)
{
	size_t	k;

	k = 0;
	while (k < ctx->nbcmd)
	{
		ctx->cmdlines[k] = ft_split(ctx->cmds[k], ' ');
		if (*ctx->cmdlines[k] == NULL)
			error(ctx, "invalid command");
		++k;
	}
}

void	init(t_pipexctx *ctx)
{
	ctx->cmdlines = ft_calloc(ctx->nbcmd, sizeof(*ctx->cmdlines));
	if (ctx->cmdlines == NULL)
		error(ctx, "malloc error");
	_init_execs(ctx);
	ctx->infd = dup(STDIN_FILENO);
	if (ctx->infd == -1)
		errorerrno(ctx);
	ctx->outfd = dup(STDOUT_FILENO);
	if (ctx->outfd == -1)
		errorerrno(ctx);
}
