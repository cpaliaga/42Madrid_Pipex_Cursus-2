/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:09:14 by caliaga-          #+#    #+#             */
/*   Updated: 2024/04/02 18:09:22 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
