/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:49:36 by ale-boud          #+#    #+#             */
/*   Updated: 2023/09/21 02:33:45 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipexctx	ctx;
	int			s;

	parse_arg(argc, argv, envp, &ctx);
	init(&ctx);
	s = execpipex(&ctx);
	destroy(&ctx);
	return (s);
}
