/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 09:58:54 by ale-boud          #+#    #+#             */
/*   Updated: 2023/09/21 02:44:01 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <stdnoreturn.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <libft.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <ft_printf/ft_printf.h>

typedef struct __attribute__((packed)) s_pipe
{
	int	read;
	int	write;
}	t_pipe;

typedef struct s_pipexctx
{
	char		*pn;
	int			here_doc;
	char		*f1;
	char		*f2;
	size_t		nbcmd;
	char		**cmds;
	char		***cmdlines;
	char		*path;
	char		**envp;
}	t_pipexctx;

/* help:
 *	print help message and exit success
 */
noreturn void	help(char *pn);

/* parse_arg:
 *	parse pn f1 f2 nbcmd
 *	no alloc
 *	if invalid argc execute help()
 */
void			parse_arg(int argc, char **argv, char **envp, t_pipexctx *ctx);

/* init:
 *	called after parsing
 *	open f1 f2
 *	alloc pipes, initialise exec list with cmds
 *	TODO error description
 */
void			init(t_pipexctx *ctx);

/* destroy:
 *	free all alloc (pipes, execs)
 */
void			destroy(t_pipexctx *ctx);

/* execpipex
 *	execute the execs list
 *	return the status
 */
int				execpipex(t_pipexctx *ctx);

/* execpipexchlid
 *	child
 */
noreturn void	execpipex_child(t_pipexctx *ctx);

/*
 *	HERROR HANDLING
 */

noreturn void	ioerror(t_pipexctx *ctx, char *fn);
noreturn void	errorerrno(t_pipexctx *ctx);
noreturn void	error(t_pipexctx *ctx, char *str);

/*
 *	UTILS
 */

char			*searchpath(char **env);
char			*pathexpension(char *path, char *fn);
void			ft_split_free(char **t);
int				ft_strcmp(const char *s1, const char *s2);

#endif
