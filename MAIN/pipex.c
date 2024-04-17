/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:12:19 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/28 14:12:22 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // System calls - family exec 
#include <sys/wait.h>
#define READ    0 
#define WRITE   1

void msg_error_open(int *url)
{
    write(2, "zsh: ", 5);
    write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, ": ", 2);
	write(2, url, ft_strlen(*url));
	write(2, "\n", 1)
}

int	fd_openfile(char *url, char opt)
{
	int	fd;

	if (opt == 'R')
		fd = open(url, O_RDONLY);
	else
		fd = open(url, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
	{
		msg_error_open();
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void    create_pipe(int *pip, int fd[2])
{
    *pip = pipe(fd);
    if (*pip == -1)
    {
        perror("Pipe error:");
        exit (1);
    }
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
	if (path == NULL)
		err_ctl(-1, "Bad path");
	exe = execve(path, s_argv, env);
	matrix_free(s_argv, s);
	err_ctl(exe, "Bad execution");
}
void initial_exe(){
        char *argVec[]={"/usr/bin/ls", NULL}; 
    char *ex_env[]={NULL};
    if (execve(argVec[0], argVec, ex_env) == -1)
            exit(1);

}

void cretate_initial_child(int *pid, int *fd)
{
    int file_in;

    *pid = fork();
    if (*pid < 0)
        exit (1);
    file_in = fd_openfile("file_in", 'R');
    if (*pid == 0)
    {
        dup2(file_in, STDIN_FILENO);
        close(file_in);
        close(fd[READ]);
        dup2(fd[WRITE], STDOUT_FILENO);
        close(fd[WRITE]);
    }
    close(fd[WRITE]);
    close(file_in);
}

void cretate_final_child(int *pid, int *fd)
{
    char *argVec[]={"/usr/bin/grep", ".c", NULL};
    char *ex_env[]={NULL};

    *pid = fork();
    if (*pid < 0)
        exit (1);
    if (*pid == 0)
    {
        dup2(fd[READ], STDIN_FILENO);
        close(fd[READ]);
        if (execve(argVec[0], argVec, ex_env) == -1)
            exit(1);
    }
    close(fd[READ]);
}

int main (void)
{
    int fd[2];
    int pipe[1];
    int pid[2];
    int i;

    create_pipe(&pipe[0], fd);
    cretate_initial_child(&pid[0], fd);
    cretate_final_child(&pid[2], fd);
    i=-1;
    while (pid[++i] != 0)
    {
        waitpid(pid[i], NULL, 0);
    }
    return (0);    
}
// gcc -Wall -Wextra -Werror simulating_pipe.c -o SP && ./SP
// sudo apt-get install valgrind ==> https://valgrind.org/docs/manual/quick-start.html
// gcc -g -O0 -Wall -Wextra -Werror simulating_pipe.c -o SP && valgrind --leak-check=yes ./SP