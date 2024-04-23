/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:36:54 by caliaga-          #+#    #+#             */
/*   Updated: 2024/04/23 17:37:18 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (*(str + a) != '\0')
		a++;
	return (a);
}

char	*ft_strjoin_slash(const char *s1, const char *s2)
{
	char	*sjoin;
	size_t	size;
	size_t	i;
	size_t	j;

	if (s1 == 0 || s2 == 0)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2) + 2;
	sjoin = (char *)malloc(size * sizeof(char));
	if (sjoin == 0)
		return (0);
	i = -1;
	while (++i < ft_strlen(s1))
		sjoin[i] = s1[i];
	sjoin[i] = '/';
	i++;
	j = -1;
	while (++j < ft_strlen(s2))
		sjoin[i + j] = s2[j];
	sjoin[i + j] = '\0';
	return (sjoin);
}

void	ft_bzero(void *s, size_t n)
{
	char	*mem;

	mem = s;
	while (n-- > 0)
		*mem++ = '\0';
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;
	size_t	len;

	len = (count * size);
	if (len < count && len < size)
		return (NULL);
	if (len > SIZE_MAX)
		return (NULL);
	str = malloc(len);
	if (!str)
		return (NULL);
	ft_bzero(str, len);
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	len;
	size_t	i;

	len = 0;
	while (*(s1 + len) != '\0')
		len++;
	i = 0;
	copy = (char *)ft_calloc((len + 1), sizeof(char));
	if (!copy)
		return (NULL);
	while (i < len)
	{
		*(copy + i) = *(s1 + i);
		i++;
	}
	*(copy + i) = '\0';
	return (copy);
}
