/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:33:55 by ale-boud          #+#    #+#             */
/*   Updated: 2023/09/21 00:40:07 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_arg(int argc, char **argv, char **envp, t_pipexctx *ctx)
{
	if (argc <= 4 || (ft_strcmp(argv[1], "here_doc") == 0 && argc <= 5))
		help(argv[0]);
	ctx->envp = envp;
	ctx->cmdlines = NULL;
	ctx->f2 = argv[argc - 1];
	ctx->here_doc = ft_strcmp(argv[1], "here_doc") == 0;
	ctx->cmds = argv + 2 + ctx->here_doc;
	ctx->f1 = argv[1];
	ctx->nbcmd = argc - 3 - ctx->here_doc;
	ctx->pn = argv[0];
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
}
