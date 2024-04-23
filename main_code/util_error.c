/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:48:29 by caliaga-          #+#    #+#             */
/*   Updated: 2024/04/23 18:00:40 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_err_ctl(int exe, char *url)
{
	if (exe == -1)
	{
		write(2, "zsh: no such file or directory: ", 32);
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

void	command_err_env(int exe, const char *url)
{
	if (exe == -1)
	{
		write(2, "env: ", 5);
		write(2, url, ft_strlen(url));
		write(2, ": no such file or directory", 27);
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
