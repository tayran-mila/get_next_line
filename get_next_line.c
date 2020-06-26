/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmendes- <tmendes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 13:22:26 by tmendes-          #+#    #+#             */
/*   Updated: 2020/06/26 08:03:23 by tmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	if (buffer == 0)
	{
		if (!(buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))) ||
		(BUFFER_SIZE == 0))
			return (NULL);
		ft_bzero(buffer, (BUFFER_SIZE + 1));
		return (buffer);
	}
	if (nl == -1)
	{
		ft_bzero(buffer, (BUFFER_SIZE + 1));
		if (read(fd, buffer, BUFFER_SIZE) == -1)
			return (NULL);
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
** This function shifts the buffer after a newline is found.
*/

static char	*buffer_shift(char *buffer, int nl)
{
	char	*aux;

	if (!(aux = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (NULL);
	ft_bzero(aux, (BUFFER_SIZE + 1));
	ft_memcpy(aux, (buffer + nl + 1), ft_strlen(buffer + nl + 1));
	ft_bzero(buffer, BUFFER_SIZE + 1);
	ft_memcpy(buffer, aux, ft_strlen(aux));
	free(aux);
	aux = NULL;
	return (buffer);
}

/*
** This function returns a line read from a file descriptor,
** without the newline.
*/

int			get_next_line(int fd, char **line)
{
	static char	*buf;
	int			nl;

	if (fd > MX_FD || fd < 0 || line == NULL || !(*line = ft_strdup("")) ||
	!(buf = buf_read(fd, buf, 0)))
		return (-1);
	while (detect_nl(buf) == -1)
	{
		if (!(*line = join_ptr(*line, buf)) ||
		!(buf = buf_read(fd, buf, -1)))
			return (-1);
		if (ft_strlen(buf) == 0)
		{
			free(buf);
			buf = NULL;
			return (0);
		}
	}
	nl = detect_nl(buf);
	*(buf + nl) = 0;
	if (!(*line = join_ptr(*line, buf)) ||
	!(buf = buffer_shift(buf, nl)))
		return (-1);
	return (1);
}
