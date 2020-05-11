/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmendes- <tmendes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 13:22:26 by tmendes-          #+#    #+#             */
/*   Updated: 2020/05/08 20:05:06 by tmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	detect_nl(char *ptr)
{
	int	k;

	k = 0;
	while(*(ptr + k) != '\n' && *(ptr + k) != 0)
		k++;
	if(*(ptr + k) == '\n')
		return (k);
	else
		return (-1);
}

static char	*join_ptr(char *dst, char *src)
{
	char	*aux;

	if (!(aux =(char *)malloc((ft_strlen(dst) + 1)*sizeof(char))))
		return (NULL);
	ft_bzero(aux, ft_strlen(dst) + 1);
	ft_memcpy(aux, dst, ft_strlen(dst));
	free(dst);
	if (!(dst = (char *)ft_strjoin(aux, src)))
		return (NULL);
	free(aux);
	return (dst);
}

static int	return_function(char **line, char *tmp, int k, int bytesRead)
{
	char	*buf;

	if (bytesRead == 0)
		return (0);
	if (!(buf =(char *)malloc((BUFFER_SIZE + 1)*sizeof(char))))
		return (-1);
	ft_bzero(buf, BUFFER_SIZE + 1);
	*(tmp + k) = 0;
	ft_memcpy(buf, tmp, (k) * sizeof(char));
	*line = join_ptr(*line, buf);
	if (*line == NULL)
		return (-1);
	ft_bzero(buf, BUFFER_SIZE + 1);
	ft_memcpy(buf, (tmp + k + 1), ft_strlen(tmp + k + 1));
	ft_bzero(tmp, BUFFER_SIZE + 1);
	ft_memcpy(tmp, buf, ft_strlen(buf));
	free(buf);
	return (1);
}

int 		get_next_line(int fd, char **line)
{
	static char	*tmp;
	int k;
	int	bytesRead;

	bytesRead = 1;
	if(tmp == 0)
	{
		if (!(tmp =(char *)malloc((BUFFER_SIZE + 1)*sizeof(char))))
			return (-1);
		ft_bzero(tmp, BUFFER_SIZE + 1);
		bytesRead = read(fd, tmp, BUFFER_SIZE);
	}
	*line = ft_strdup("");
	k = detect_nl(tmp);
	while (k == -1 && bytesRead > 0)
	{
		*line = join_ptr(*line, tmp);
		ft_bzero(tmp, BUFFER_SIZE + 1);
		bytesRead = read(fd, tmp, BUFFER_SIZE);
		k = detect_nl(tmp);
	}
	return ( return_function(line, tmp, k, bytesRead) );
}