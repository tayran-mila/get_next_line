/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmendes- <tmendes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 13:22:26 by tmendes-          #+#    #+#             */
/*   Updated: 2020/05/15 09:02:15 by tmendes-         ###   ########.fr       */
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
	int	i;

	if (bytesread == 0)
		return (0);
	*(tmp + k) = 0;
	i = 0;
	while (tmp[i] == 1)
		i++;
	*line = join_ptr(*line, (tmp + i));
	if (*line == NULL)
		return (-1);
	while (i <= k)
	{
		tmp[i] = 1;
		i++;
	}
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
