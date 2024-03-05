/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_execve.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:50:13 by caliaga-          #+#    #+#             */
/*   Updated: 2024/03/05 19:51:05 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* How to execute another program in C (using exec) 
https://www.youtube.com/watch?v=OVFEWSP7n8c

https://manpages.debian.org/stretch/manpages-es/execve.2.es.html
https://www.um.es/earlyadopters/actividades/a3/PCD_Activity3_Session1.pdf
https://manpages.debian.org/stretch/manpages-es/wait.2.es.html
https://en.wikipedia.org/wiki/File_descriptor
*/

/** En zsh localizaremos la ruta del comando con "whence -p" (tells executable path). 
 * */

#include <stdio.h> // printf() function
#include <unistd.h> // System calls: close() - family exec() functions.
#include <sys/types.h> 
/* tipo pid_t que no es mas que un identificador de proceso linux PID */
#include <sys/wait.h> 
// wait() function
#include <errno.h> // Variable errno
#include <stdlib.h> // exit() function.
#include <fcntl.h> // O_RDONLY, O_WRONLY, O_RDWR
#include <string.h>

//** Las funciones de la familia exec_() necesitan
// *  ocupar un proceso existente por ello

// ** Control de errores EXIT_FAILURE *

/*
void err_ctl(int exe)
{   if (exe == -1)
    {
        perror(strerror(errno));
        exit(EXIT_FAILURE); // exit(1);
    }
}

int fd_openfile(char *url, char opt)
{
    int fd;

    if (opt == 'R')
        fd = open(*url, O_RDONLY, 0770);
    else
        fd = open(*url, O_WRONLY, 0770);
    if (fd == -1)
        return (1);
    return (fd);
}
*/

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (*(str + a) != '\0')
		a++;
	return (a);
}

int main(void)
{
    char *argVec[]={"/bin/lss","-la", NULL}; // Parámetro de execve()
    char *env[]={NULL};  // Parámetro de execve()
    pid_t pid; /** Nos reparamos para clonar el proceso y tener un proceso hijo */
    
    pid = fork(); /** Bifurcamos/clonamos el proceso para obtener el proceso hijo */
    if (pid == -1) /** Control de errores EXIT_FAILURE */
        return(1);

    if (pid == 0) /* PROCESO HIJO */
    {
        int ex = execve(argVec[0], argVec, env); /** 
        * Una vez que se ejecute execve() sobreescribirá ∑overwrite∑ 
        * el procedimiento de main(). Todas las instrucciones 
        * a partir de este punto no se ejecutarán. Excepto que execve()
        * se ejecute en un proceso hijo de main() */
       if (ex == -1) 
       {
        /**write(2, strerror(errno), ft_strlen(strerror(errno)));
            perror("");
         * 
        */
            
             	write(2, "zsh", 3);
                write(2, ": ", 2);
                write(2, strerror(errno), ft_strlen(strerror(errno)));
                write(2, "\n", 1);

            /* exit(1); exit (int status) Produce la terminación del proceso actual */
            /** status - El uso de EXIT_SUCCESS y EXIT_FAILURE es ligeramente 
             * más portable (para entornos no Unix) que el de 0 y algún 
             * valor distinto de cero como 1 o -1.*/
            exit(1);
        };
    }
    else /* PROCESSO PADRE */
    {
        wait(NULL); // Susspendemos el procceso padre hasta que el proceso hijo termine.
        printf("Processo ejecutado. \n");
        // close(int fd); 
        /** int close(int fd) cierra un file descriptor.
         * Returns zero on success. On error, -1 is returned, 
         * and errno is set to indicate the error. */
    }
    return (0); // EXIT_SUCCESS
}
