/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmendes- <tmendes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 13:22:26 by tmendes-          #+#    #+#             */
/*   Updated: 2020/05/17 10:12:03 by tmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
** This is an auxiliary function that presents some return conditions.
** This function also pads the static buffer with 'ones' in the bytes
** that are no longer of interest.
*/

static int	return_function(char **line, char *tmp, int k, int bytesread)
{
	char	*aux;

	if (bytesread == 0 && ft_strlen(*line) == 0)
		return (0);
	if (bytesread == 0 && ft_strlen(*line) > 0)
		return (1);
	if (!(aux = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	*(tmp + k) = 0;
	*line = join_ptr(*line, tmp);
	if (*line == NULL)
		return (-1);
	ft_bzero(aux, BUFFER_SIZE + 1);
	ft_memcpy(aux, (tmp + k + 1), ft_strlen(tmp + k + 1));
	ft_bzero(tmp, BUFFER_SIZE + 1);
	ft_memcpy(tmp, aux, ft_strlen(aux));
	free(aux);
	return (1);
}

/*
** This is the principal function of the program. It allocates
** the static buffer, *buffer, initializes it and if no '\n'
** is found inside the buffer, it concatenates the results.
*/

int			get_next_line(int fd, char **line)
{
	static char	*buffer[MAX_FD];
	int			k;
	int			bytesread;

	if (fd > MAX_FD)
		return (-1);
	bytesread = 1;
	if (buffer[fd] == 0)
	{
		if (!(buffer[fd] = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
			return (-1);
		ft_bzero(buffer[fd], (BUFFER_SIZE + 1));
		bytesread = read(fd, buffer[fd], BUFFER_SIZE);
	}
	*line = ft_strdup("");
	k = detect_nl(buffer[fd]);
	while (k == -1 && bytesread > 0)
	{
		*line = join_ptr(*line, buffer[fd]);
		ft_bzero(buffer[fd], BUFFER_SIZE + 1);
		bytesread = read(fd, buffer[fd], BUFFER_SIZE);
		k = detect_nl(buffer[fd]);
	}
	return (return_function(line, buffer[fd], k, bytesread));
}
