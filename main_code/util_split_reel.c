/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_split_reel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:15:54 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/28 18:28:10 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_cuts(const char *str, int c)
{
	size_t	cut[2];

	cut[0] = 0;
	cut[1] = 0;
	while (str[cut[0]] != '\0')
	{
		if (cut[0] == 0)
			if (str[cut[0]] != c)
				cut[1] += 1;
		if (str[cut[0]] != c)
			if (str[cut[0] - 1] == c)
				cut[1] += 1;
		cut[0]++;
	}
	return (cut[1]);
}

size_t	ft_reels(const char *str, char c, size_t *reel)
{
	size_t	dim[3];

	dim[0] = 0;
	while (str[dim[0]] != '\0')
		dim[0]++;
	dim[1] = 0;
	dim[2] = *reel;
	while (str[dim[1] + dim[2]] == c && str)
	{
		if ((dim[1] + dim[2]) < dim[0])
			dim[2]++;
		else
			break ;
	}
	while (str[dim[1] + dim[2]] != c && str)
	{
		if ((dim[1] + dim[2]) < dim[0])
			dim[1]++;
		else
			break ;
	}
	*reel = dim[2];
	return (dim[1]);
}

void	ft_fill(char *arr, const char *str, size_t letters, size_t *reel)
{
	size_t	l;
	size_t	clone;

	l = 0;
	clone = *reel;
	while (l < letters && str[clone + l] != '\0')
	{
		arr[l] = str[clone + l];
		l++;
	}
	arr[l] = '\0';
}

char	**split_reel(const char *str, char c, size_t reel)
{
	char	**spine;
	size_t	letters;
	size_t	cuts;
	size_t	p;

	if (!str || !c)
		return (NULL);
	cuts = ft_cuts(str, c);
	spine = (char **)malloc(sizeof(char *) * (cuts + 1));
	if (!spine)
		return (NULL);
	p = 0;
	while (p < (cuts))
	{
		letters = ft_reels(str, c, &reel);
		spine[p] = (char *)malloc(sizeof(char) * (letters + 1));
		error_matrix_free(spine, p);
		ft_fill(spine[p], str, letters, &reel);
		reel += letters;
		p++;
	}
	spine[p] = NULL;
	return (spine);
}
