/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_con_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:29:52 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/20 11:59:04 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h> // printf()
#include <string.h>
#include <unistd.h> // System calls - family exec close ()
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h> 
// open() function #include <fcntl.h> https://man7.org/linux/man-pages/man2/open.2.html
// open() function - Modos de Acceso: O_RDONLY, O_WRONLY, or O_RDWR
// open() function - Permisos: 00700 user (file owner) has read, write, and execute.

void err_ctl(int exe)
{   if (exe == -1)
    {
        printf("Número %i ", errno);
        perror(strerror(errno));
        exit(EXIT_FAILURE); // exit(1);
    }
}

int fd_openfile(char *url, char opt){
    int fd;

    if (opt == 'R')
        fd = open(*url, O_RDONLY, 0777);
    else
        fd = open(*url, O_WRONLY | O_CREATE | O_TRUNCATE, 0644);
    if (fd == -1)
        exit (1);
    return (fd);
}

int main (void)
{
    int fd_infile;
    int fd_outfile;
    char *argVec1[]={"/bin/ls","-la", NULL}; // Parámetro de execve()
    char *argVec2[]={"/usr/bin/grep",".html", NULL}; // /usr/bin
    char *ex_env[]={NULL};  // Parámetro ENVIROMENT de execve()

    // Los file descriptors de las entradas y salidas 
    // estandar son: 0 - STDIN 1- STDOUT y 2 - STDERR
    // tras estos se numeran otros file descriptors,
    // como por ejemplo los del archivo que se abre con open()
    fd_infile = fd_openfile("infile", 'R');
    printf("fd_infile: %i\n", fd_infile);
    printf("fd_outfile: %i\n", fd_outfile);
    fd_outfile = fd_openfile("outfile", 'W');

    if (fd_infile == 1 || fd_outfile == 1)
        return (1);

    int fd[2];
    if (pipe(fd) == -1)
        return (1);
    
    int pid1 = fork(); // CREACIÓN DEL PRIMER PROCESO HIJO.
    if (pid1 < 0)
        return (1);
    
    if (pid1 == 0)  // PRIMER PROCESO HIJO.
    {
        dup2(fd[1], STDOUT_FILENO); // WRITE pasa a ser la salida estandar.
        close(fd[0]); // Cierro READ O_RDONLY
        close(fd[1]); // Cierro WRITE O_WRONLY
        int ex1 = execve(argVec1[0], argVec1, ex_env);
        err_ctl(ex1);
    
    }
    
    int pid2 = fork(); // CREACIÓN DEL SEGUNDO PROCESO HIJO.
    if (pid2 < 0)
        return (1);
        
    if (pid2 == 0)  //  SEGUNDO PROCESO HIJO. 
    {
        dup2(fd[0], STDIN_FILENO); // READ pasa a ser la salida estandar.
        close(fd[0]);// Cierro READ O_RDONLY
        close(fd[1]);// Cierro WRITE O_WRONLY
        int ex2 = execve(argVec2[0], argVec2, ex_env);
        err_ctl(ex2);
    }
    
    // PROCESO PADRE
    close(fd[0]);
    close(fd[1]);
    
    waitpid(pid1, NULL, 0); // Espera a que el proceso hijo 1 termine.
    waitpid(pid2, NULL, 0); // Espera a que el proceso hijo 2 termine.
    
    return (0);
}