/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions_family.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:36:44 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/28 13:37:11 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Executing commands in C 
https://www.youtube.com/watch?v=uh2FqejQRk8

https://manpages.debian.org/stretch/manpages-es/execve.2.es.html
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // System calls - family exec() 
#include <time.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[])
{
    /* Las funciones de la familia exec_() necesitan 
    ocupar un proceso existente por ello necesitamos 
    crear un proceso hijo que será ocupado por exec_() */
    int pid = fork();
    /* Control de errores */
    if (pid == -1)
        return (1);
    
    if (pid == 0)
    {
        /* CHILD PROCESS */
        execlp("ping", "ping", "-c", "3", "google.com", NULL);
        printf("Proceso HIJO terminado");
    }
    else
    {
        /* Parent Process (pid > 0) */
        /* Antes de terminar el proceso padre, el proceso hijo 
    debe haber terminado, por lo que lo esperaremos */
        wait(NULL);
        printf("Proceso PADRE terminado");
    }
    
    return (0);
}
