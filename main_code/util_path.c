/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:59:03 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/29 20:57:24 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*select_env(char **env)
{
	char	*pat;
	int		match;
	int		e;
	int		i;

	pat = "PATH=";
	match = 0;
	e = -1;
	i = -1;
	while (env[++e])
	{
		while (++i < 5)
		{
			if (pat[i] == env[e][i])
			{
				match += 1;
			}
		}
		if (match == 5)
			return (env[e]);
		match = 0;
		i = -1;
	}
	return (NULL);
}

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

char	*filepath_generator(const char *argv, char **env)
{
	char	**paths;
	int		row;
	char	*target_path;

	paths = split_reel(select_env(env), ':', 5);
	row = -1;
	while (paths[++row] != NULL)
	{
		target_path = ft_strjoin_slash(paths[row], argv);
		if (access(target_path, X_OK || F_OK) == 0)
			return (target_path);
		free(target_path);
		target_path = NULL;
	}
	matrix_free(paths, row);
	return (NULL);
}
