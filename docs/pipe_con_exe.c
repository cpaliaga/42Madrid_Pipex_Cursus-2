/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_con_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:29:52 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/14 21:03:00 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // System calls - family exec 
#include <sys/wait.h>

int main (void)
{
    char *argVec1[]={"/bin/ls","-la", NULL}; // Parámetro de execve()
    char *env1[]={NULL};  // Parámetro de execve()
    char *argVec2[]={"./grep",".html", NULL}; // Parámetro de execve()
    char *env2[]={"PATH=/usr/bin/", NULL};  // Parámetro de execve()

    int fd[2];
    if (pipe(fd) == -1)
        return (1);
    
    int pid1 = fork();
    if (pid1 < 0)
        return (1);
    
    if (pid1 == 0)  // PRIMER PROCESO HIJO.
    {
        dup2(fd[1], STDOUT_FILENO); // WRITE pasa a ser la salida estandar.
        close(fd[0]); // Cierro READ O_RDONLY
        close(fd[1]); // Cierro WRITE O_WRONLY
        int ex1 = execve(argVec1[0], argVec1, env1);
        if (ex1 == -1)
            exit(1);
    
    }
    
    int pid2 = fork();
    if (pid2 < 0)
        return (1);
        
    if (pid2 == 0)  //  SEGUNDO PROCESO HIJO. («grep»).
    {
        dup2(fd[0], STDIN_FILENO); // READ pasa a ser la salida estandar.
        close(fd[0]);
        close(fd[1]);
        int ex2 = execve(argVec2[0], argVec2, env2);
        if (ex2 == -1)
            exit(1);
    }
    
    // PROCESO PADRE.
    close(fd[0]);
    close(fd[1]);
    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    return (0);
}