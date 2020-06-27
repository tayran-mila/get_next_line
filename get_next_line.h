/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmendes- <tmendes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 13:22:31 by tmendes-          #+#    #+#             */
/*   Updated: 2020/06/27 15:46:32 by tmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# define MAX_FD 1024

unsigned long	ft_strlen(const char *s);
char			*ft_strjoin(const char *s1, const char *s2);
void			*ft_memmove(void *dst, const void *src, size_t len);
char			*ft_strdup(const char *s);
int				get_next_line(int fd, char **line);

#endif
