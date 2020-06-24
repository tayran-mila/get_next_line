/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmendes- <tmendes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 13:22:26 by tmendes-          #+#    #+#             */
/*   Updated: 2020/06/24 14:09:20 by tmendes-         ###   ########.fr       */
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
		if (!(buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
			return (NULL);
		ft_bzero(buffer, (BUFFER_SIZE + 1));
		return (buffer);
	}
	if (nl == -1)
	{
		ft_bzero(buffer, (BUFFER_SIZE + 1));
		read(fd, buffer, BUFFER_SIZE);
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
	static char	*buf;
	char		*aux;
	int			nl;

	if (!(*line = ft_strdup("")) || !(buf = buf_read(fd, buf, 0)) || fd > MX_FD)
		return (-1);
	while (detect_nl(buf) == -1)
	{
		if (!(*line = join_ptr(*line, buf)) || !(buf = buf_read(fd, buf, -1)))
			return (-1);
		if(ft_strlen(buf) == 0)
			return (0);			
	}
	nl = detect_nl(buf);
	*(buf + nl) = 0;
	aux = NULL;
	if (!(*line = join_ptr(*line, buf)) || !(aux = buf_read(fd, aux, 0)))
		return (-1);
	ft_memcpy(aux, (buf + nl + 1), ft_strlen(buf + nl + 1));
	ft_bzero(buf, BUFFER_SIZE + 1);
	ft_memcpy(buf, aux, ft_strlen(aux));
	free(aux);
	return (1);
}
