/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:48:29 by caliaga-          #+#    #+#             */
/*   Updated: 2024/03/06 19:49:19 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_err_ctl(int exe, char *url)
{
	if (exe == -1)
	{
		write(2, "zsh: ", 5);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		write(2, url, ft_strlen(url));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
}

void	command_err_ctl(int exe, const char *url)
{
	if (exe == -1)
	{
		write(2, "zsh: command not found: ", 24);
		write(2, url, ft_strlen(url));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
}

void	err_ctl(int exe, char *msg)
{
	if (exe == -1)
	{
		perror(msg);
		exit(EXIT_FAILURE);
	}
}

char	**matrix_free(char **arr, size_t row)
{
	while (row-- > 0)
	{
		if (arr[row])
		{
			free(arr[row]);
			arr[row] = NULL;
		}
	}
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
	return (NULL);
}

char	**error_matrix_free(char **arr, size_t row)
{
	if (!arr[row])
	{
		while (row-- > 0)
		{
			if (arr[row])
			{
				free(arr[row]);
				arr[row] = NULL;
			}
		}
		if (arr)
		{
			free(arr);
			arr = NULL;
		}
	}
	return (NULL);
}
