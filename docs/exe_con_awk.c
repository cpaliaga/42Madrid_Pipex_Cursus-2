/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_con_awk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:46:52 by caliaga-          #+#    #+#             */
/*   Updated: 2024/03/31 22:46:52 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
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

int main (void)
{
    char *argVec1[]={"/usr/bin/cat","/etc/group", NULL}; 
    // cat /etc/passwd | awk -F ":" '{print $1"\t"$3"\t"$4}'
    
    //  OK      imprime correctamente.
    //  char *argVec2[]={"/usr/bin/awk","-F", ":", "{print $1 \"\t\" $2}", NULL};
    
    //  OK      imprime correctamente.   
    //  char *argVec2[]={"/usr/bin/awk","-F", ":", "{print $1}", NULL};

    //  OK      imprime pero ignora el tabulador.
    //  char *argVec2[]={"/usr/bin/awk","-F", ":", "{print $1 \t $2}", NULL};

    //  FAIL    awk: 1: unexpected character 
    //  char *argVec2[]={"/usr/bin/awk","-F", ":", "{print $1 '\t' $2}", NULL};
    
    //  FAIL    awk: 1: unexpected character 
    //  char *argVec2[]={"/usr/bin/awk","-F", ":", "{print $1 \'\t\' $2}", NULL};

    //  FAIL    no compila.
    //  char *argVec2[]={"/usr/bin/awk","-F", ":", "{print $1 "\t" $2}", NULL};

    //  FAIL    no compila.
    //  char *argVec2[]={"/usr/bin/awk","-F", ":", "'{print $1"\t"$3"\t"$4}'", NULL};

    //  FAIL    awk: 1: unexpected character
    //  char *argVec2[]={"/usr/bin/awk","-F", ":", "'{print $1 $2}'", NULL};

    char *ex_env[]={NULL};  // Parámetro ENVIROMENT de execve()

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