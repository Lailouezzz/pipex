/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:32:50 by ale-boud          #+#    #+#             */
/*   Updated: 2023/09/20 18:11:39 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	_destroy_execs(t_pipexctx *ctx)
{
	size_t	k;

	k = 0;
	while (k < ctx->nbcmd)
	{
		ft_split_free(ctx->cmdlines[k]);
		++k;
	}
	free(ctx->cmdlines);
}
