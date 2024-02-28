/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:40:48 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/28 18:37:03 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fd_openfile(char *url, char opt)
{
	int	fd;

	if (opt == 'R')
	{
		fd = open(url, O_RDONLY, 0777);
		err_ctl(fd);
	}
	else
	{
		fd = open(url, O_WRONLY, 0777);
		err_ctl(fd);
	}
	return (fd);
}

void	exec(char *argv, char **env)
{
	char	**s_argv;
	int		s;
	char	*path;
	int		exe;

	s = 0;
	s_argv = split_reel(argv, ' ', 0);
	while (s_argv[s] != NULL)
		s++;
	path = filepath_generator(s_argv[0], env);
	exe = execve(path, s_argv, env);
	matrix_free(s_argv, s);
	err_ctl(exe);
}

void	child(int *fd_pipe, char **argv, char **env)
{
	int		fd_in;

	fd_in = fd_openfile(argv[1], 'R');
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[0]);
	exec(argv[2], env);
}

void	parent(int *fd_pipe, char **argv, char **env)
{
	int		fd_out;

	fd_out = fd_openfile(argv[4], 'W');
	dup2(fd_out, STDOUT_FILENO);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[1]);
	exec(argv[3], env);
}

int	main(int argc, char **argv, char **env )
{
	int		fd_pipe[2];
	pid_t	pid;

	if (argc != 5)
		err_ctl(-1);
	if (pipe(fd_pipe) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		child(fd_pipe, argv, env);
	parent(fd_pipe, argv, env);
	exit(0);
}

//	./a.out infile "ls -l" "wc -l" outfile
//	./a.out "grep a1" "wc -w" outfile
