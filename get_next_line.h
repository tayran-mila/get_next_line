/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmendes- <tmendes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 13:22:31 by tmendes-          #+#    #+#             */
/*   Updated: 2020/05/15 07:33:07 by tmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNLB_H
# define GNLB_H
#include <unistd.h>
#include <stdlib.h>

# define MAX_FD 1024 + 1

unsigned long	ft_strlen(const char *s);
char			*ft_strjoin(const char *s1, const char *s2);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_strdup(const char *s);
void			ft_bzero(void *s, size_t n);
int				get_next_line(int fd, char **line);

#endif