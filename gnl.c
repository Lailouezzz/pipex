/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:26:12 by ale-boud          #+#    #+#             */
/*   Updated: 2023/09/21 13:56:28 by ale-boud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "gnl.h"

static int	ft_strline(const char *s)
{
	int	k;

	if (s == NULL)
		return (0);
	k = 0;
	while (s[k] != '\0' && s[k] != '\n')
		++k;
	if (s[k] == '\n')
		++k;
	return (k);
}

static char	*gnl_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*s;

	s1len = ft_strline(s1);
	s2len = ft_strline(s2);
	s = malloc((s1len + s2len + 1) * sizeof(*s1));
	if (s == NULL)
		return (NULL);
	ft_memcpy(s, s1, s1len);
	ft_memcpy(s + s1len, s2, s2len);
	s[s1len + s2len] = '\0';
	return (s);
}

static void	_update_buf(int fd, char *buf, size_t *pos)
{
	ssize_t	readed;

	readed = read(fd, buf, BUFFER_SIZE);
	if (readed >= 0)
		buf[readed] = '\0';
	else
		*buf = '\0';
	*pos = 0;
}

static char	*_gnl(int fd, char *buf, size_t *pos, char *s)
{
	char	*str;

	if (*buf == '\0')
		return (s);
	str = gnl_strjoin(s, buf + *pos);
	free(s);
	*pos += ft_strline(buf + *pos);
	if (str[ft_strlen(str) - 1] == '\n')
		return (str);
	_update_buf(fd, buf, pos);
	return (_gnl(fd, buf, pos, str));
}

char	*gnl(int fd)
{
	static char		buf[BUFFER_SIZE + 1];
	static size_t	pos = BUFFER_SIZE + 1;

	if (pos == BUFFER_SIZE + 1 || buf[pos] == '\0')
		_update_buf(fd, buf, &pos);
	return (_gnl(fd, buf, &pos, NULL));
}
