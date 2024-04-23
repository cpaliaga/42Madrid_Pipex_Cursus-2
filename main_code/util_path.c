/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:59:03 by caliaga-          #+#    #+#             */
/*   Updated: 2024/04/18 13:05:22 by caliaga-         ###   ########.fr       */
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

int is_command_path(char *str)
{
    if (access(str, F_OK | X_OK) == -1)
        return (-1);
    return (0);
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
	if (env[1] == NULL)
		command_err_env(-1, argv);
	command_err_ctl(-1, argv);
	return (target_path);
}