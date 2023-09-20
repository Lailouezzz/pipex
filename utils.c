/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:20:20 by ale-boud          #+#    #+#             */
/*   Updated: 2023/09/21 01:31:13 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*searchpath(char **env)
{
	while (*env != NULL && ft_strncmp("PATH=", *env, 5) != 0)
		++env;
	return (*env);
}

char	*pathexpension(char *path, char *fn)
{
	char	**paths;
	size_t	k;
	char	*cur;

	if (access(fn, X_OK) == 0)
		return (ft_strdup(fn));
	paths = ft_split(path + 5, ':');
	k = 0;
	while (paths[k] != NULL)
	{
		cur = malloc(sizeof(*cur) * (ft_strlen(fn) + ft_strlen(paths[k]) + 2));
		strcat(strcat(strcpy(cur, paths[k]), "/"), fn);
		if (access(cur, X_OK) == 0)
			return (cur);
		free(cur);
		++k;
	}
	ft_split_free(paths);
	return (NULL);
}

void	ft_split_free(char **t)
{
	void	*f;

	if (t == NULL)
		return ;
	f = t;
	while (*t != NULL)
		free(*(t++));
	free(f);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}
