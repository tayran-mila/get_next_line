/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmendes- <tmendes-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:43:01 by tmendes-          #+#    #+#             */
/*   Updated: 2020/05/15 09:02:47 by tmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

unsigned long	ft_strlen(const char *s)
{
	unsigned long	k;

	k = 0;
	while (*(s + k) != 0)
	{
		k++;
	}
	return (k);
}

char			*ft_strjoin(const char *s1, const char *s2)
{
	char			*p;
	unsigned long	len_1;
	unsigned long	size;
	unsigned long	k;

	if (!s1 || !s2)
		return (NULL);
	len_1 = ft_strlen(s1);
	size = len_1 + ft_strlen(s2);
	if (!(p = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	k = 0;
	while (k < len_1)
	{
		*(p + k) = *(s1 + k);
		k++;
	}
	while (k < size)
	{
		*(p + k) = *(s2 + k - len_1);
		k++;
	}
	*(p + k) = 0;
	return (p);
}

void			*ft_memcpy(void *dst, const void *src, unsigned long n)
{
	unsigned long	k;

	k = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (k < n)
	{
		*((unsigned char *)dst + k) =
		(unsigned char)*((char *)src + k);
		k++;
	}
	return (dst);
}

char			*ft_strdup(const char *s)
{
	char	*p;

	if (!(p = (char *)malloc((ft_strlen(s) + 1))))
		return (NULL);
	p = (char *)ft_memcpy(p, s, (ft_strlen(s) + 1));
	return (p);
}

void			ft_bzero(void *s, unsigned long n)
{
	unsigned long	k;

	k = 0;
	while (k < n)
	{
		*((char *)s + k) = (unsigned char)0;
		k++;
	}
}
