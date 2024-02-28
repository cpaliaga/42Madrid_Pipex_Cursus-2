/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:48:29 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/28 17:58:05 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	err_ctl(int exe)
{
	if (exe == -1)
	{
		perror(strerror(errno));
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
