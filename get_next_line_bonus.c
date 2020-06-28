/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmendes- <tmendes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 13:22:26 by tmendes-          #+#    #+#             */
/*   Updated: 2020/06/28 06:23:22 by tmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
** This function returns the position of the '\n' given a pointer.
*/

static int	detect_nl(char *ptr)
{
	int	k;

	k = 0;
	while (*(ptr + k) != '\n' && *(ptr + k) != 0)
		k++;
	if (*(ptr + k) == '\n')
		return (k);
	else
		return (-1);
}

/*
** This function allocates the buffer if it was not done previously
** and if no new line has been reached, it reads another chunk
** of the text associated with the specified fd.
*/

static char	*buf_read(int fd, char *buffer, int nl)
{
	int	bytes;

	if (buffer == 0)
	{
		if (!(buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))) ||
		(BUFFER_SIZE == 0))
			return (NULL);
		*buffer = 0;
	}
	if (nl == -1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		*(buffer + bytes) = 0;
	}
	return (buffer);
}

/*
** This function concatenates two pointers *dst and *src and
** maintaining the result in the pointer *dst.
*/

static char	*join_ptr(char *dst, char *src)
{
	char	*join;

	join = dst;
	if (!(dst = (char *)ft_strjoin(join, src)))
		return (NULL);
	free(join);
	join = NULL;
	return (dst);
}

/*
** This function returns a line read from a file descriptor,
** without the newline.
*/

int			get_next_line(int fd, char **line)
{
	static char	*buf[MAX_FD];
	int			nl;

	if (fd > MAX_FD || fd < 0 || !(buf[fd] = buf_read(fd, buf[fd], 0)) ||
	line == NULL || !(*line = ft_strdup("")))
		return (-1);
	while (detect_nl(buf[fd]) == -1)
	{
		if (!(*line = join_ptr(*line, buf[fd])) ||
		!(buf[fd] = buf_read(fd, buf[fd], -1)))
			return (-1);
		if (ft_strlen(buf[fd]) == 0)
		{
			free(buf[fd]);
			buf[fd] = NULL;
			return (0);
		}
	}
	nl = detect_nl(buf[fd]);
	*(buf[fd] + nl) = 0;
	if (!(*line = join_ptr(*line, buf[fd])) ||
	!(buf[fd] = ft_memmove(buf[fd], (buf[fd] + nl + 1),
	ft_strlen(buf[fd] + nl + 1) + 1)))
		return (-1);
	return (1);
}
