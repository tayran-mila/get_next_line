/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmendes- <tmendes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 13:22:31 by tmendes-          #+#    #+#             */
/*   Updated: 2020/05/07 16:39:12 by tmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H
#include <unistd.h>
#include <stdlib.h>

unsigned long	ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_strdup(const char *s);
void			ft_bzero(void *s, size_t n);
int				get_next_line(int fd, char **line);

#endif