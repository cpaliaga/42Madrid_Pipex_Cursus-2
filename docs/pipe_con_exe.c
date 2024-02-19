/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_con_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:29:52 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/19 18:51:08 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // System calls - family exec 
#include <sys/wait.h>
#include <errno.h>

void exe_error_control(int exe)
{   if (exe == -1)
    {
        printf("Número %i ", errno);
        perror(strerror(errno));
        exit(1);
    }
}


int main (void)
{
    char *argVec1[]={"/bin/ls","-la", NULL}; // Parámetro de execve()
    char *argVec2[]={"/usr/bin/grep",".html", NULL}; // /usr/bin
    char *ex_env[]={NULL};  // Parámetro de execve()
    // "PATH=bin/:usr/bin/"
    // "PATH=/bin/:/usr/bin/"
    // "PATH=/bin:/usr/bin"

    // PATH=/home/tonic_water/.local/bin:
    // -->  /usr/local/sbin:
    // -->  /usr/local/bin:
    // -->  /usr/sbin:
    // -->  /usr/bin:
    // -->  /sbin:
    // -->  /bin:

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
        int ex1 = execve(argVec1[0], argVec1, ex_env);
        exe_error_control(ex1);
    
    }
    
    int pid2 = fork();
    if (pid2 < 0)
        return (1);
        
    if (pid2 == 0)  //  SEGUNDO PROCESO HIJO. 
    {
        dup2(fd[0], STDIN_FILENO); // READ pasa a ser la salida estandar.
        close(fd[0]);// Cierro READ O_RDONLY
        close(fd[1]);// Cierro WRITE O_WRONLY
        int ex2 = execve(argVec2[0], argVec2, ex_env);
        exe_error_control(ex2);
    }
    
    // PROCESO PADRE.
    close(fd[0]);
    close(fd[1]);
    
    waitpid(pid1, NULL, 0); // Espera a que el proceso hijo 1 termine.
    waitpid(pid2, NULL, 0); // Espera a que el proceso hijo 2 termine.
    
    return (0);
}