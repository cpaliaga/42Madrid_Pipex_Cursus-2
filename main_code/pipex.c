/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:40:48 by caliaga-          #+#    #+#             */
/*   Updated: 2024/04/23 22:28:26 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fd_openfile(char *url, char opt)
{
	int	fd;

	if (opt == 'R')
		fd = open(url, O_RDONLY);
	else
		fd = open(url, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	open_err_ctl(fd, url);
	return (fd);
}

void	exec(char *argv, char **env)
{
	char	**s_argv;
	int		s_len;
	char	*path;

	space_betwen_quotes(argv, 39);
	s_argv = split_reel(argv, ' ', 0);
	matrix_swap_char(s_argv);
	s_len = 0;
	while (s_argv[s_len] != NULL)
		s_len++;
	if (is_command_path(s_argv[0]) == 0)
		path = s_argv[0];
	else
		path = filepath_generator(s_argv[0], env);
	if (path == NULL)
		err_ctl(-1, "Bad path");
	if (execve(path, s_argv, env) == -1)
		err_ctl(-1, "Bad execution");
	matrix_free(s_argv, s_len);
}

void	child(int *fd_pipe, char **argv, char **env)
{
	int		fd_in;
	int		redir_in;
	int		redir_out;

	fd_in = fd_openfile(argv[1], 'R');
	redir_in = dup2(fd_in, STDIN_FILENO);
	err_ctl(redir_in, "Child bad pipe in");
	redir_out = dup2(fd_pipe[1], STDOUT_FILENO);
	err_ctl(redir_out, "Child bad outfile");
	close(fd_pipe[0]);
	exec(argv[2], env);
}

void	parent(int *fd_pipe, char **argv, char **env)
{
	int		fd_out;
	int		redir_in;
	int		redir_out;

	fd_out = fd_openfile(argv[4], 'W');
	redir_out = dup2(fd_out, STDOUT_FILENO);
	err_ctl(redir_out, "Parent bad outfile");
	redir_in = dup2(fd_pipe[0], STDIN_FILENO);
	err_ctl(redir_in, "Parent bad pipe in");
	close(fd_pipe[1]);
	exec(argv[3], env);
}

int	main(int argc, char **argv, char **env )
{
	int		fd_pipe[2];
	pid_t	pid;

	if (argc != 5)
		err_ctl(-1, "Bad params");
	if (*env == NULL)
	{
		env[0] = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
		env[1] = NULL;
	}
	if (*env == NULL)
		err_ctl(-1, "No enviroment");
	if (pipe(fd_pipe) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		child(fd_pipe, argv, env);
	parent(fd_pipe, argv, env);
	return (0);
}
