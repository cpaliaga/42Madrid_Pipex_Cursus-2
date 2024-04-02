/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_enviroment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:49:27 by caliaga-          #+#    #+#             */
/*   Updated: 2024/04/02 13:03:22 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // System calls - family exec 
#include <sys/wait.h>
#include <errno.h>

// OBTENIENDO EL ENTORNO (VARIABLES) CUNADDO EL VALOS DE MAIN EN NULL

/**
 * 

size_t fd_bytesToRead(int fd)
{
 
    size_t bytesRead;
    char buffer[32];
    int rd;

    rd = 1;
    bytesRead = 0;
    // Cuando el read retorne 0, significa que ya no hay nada que leer 
    // y que hemos llegado al final del fichero.
    while (rd != 0)
    {
        rd = read(fd, buffer, sizeof(buffer));
        bytesRead = bytesRead + rd;
     
    }
    return (bytesRead);
}

char *fd_read(int fd ,size_t bRead)
{
    int fd_read;
    char *buffer;

    buffer = (char *)malloc(bRead);
	if (!buffer)
		return (NULL);
    fd_read = read(fd, buffer, bRead);
    if (fd_read == -1)
    {
        perror("Error: ");
        return(NULL);
    }
    return (buffer);
}
*/
void gen_env()
{
    int ex1;
    char *route; 
    char **argVec;
    //char ex_env[1];

    route = "/usr/bin/env";
    argVec[0] = route;
    argVec[1] = NULL;
    
    printf("Argumentos %s %s\n", argVec[0], argVec[1]);

    int pid1 = fork();  //  Creamos el proceso hijo.
    if (pid1 < 0)  //  Control de errores del proceso hijo.
        return ;
    if (pid1 == 0)  // PROCESO HIJO.
    {
        ex1 = execve(argVec[0], argVec, NULL);
        printf("exe %i \n", ex1);
        // ¿Se puede leer el file descripor de execve por su fd stdout 1?
        

    }
    //waitpid(pid1, NULL, 0); // Esperamos a que el proceso hijo termine.
}

int main(int argc, char **argv, char **env)
{
    // env -i  ./a.out
    /**
     * 
    
    if (!env[0])
    {
        printf("Entorno nulo %s \n", env[0]);
        gen_env();
    }
*/
    /** SI EL PARÁMETRO env ES NULL LE DAMOS EL VALOR DE UNA VARIABLE QUEE HEMOS CREADO CON LAS RUTAS MAS PROBABLES */
    if (!env[0])
    {
        env[0] = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
        env[1] = NULL;
    }
    /** IMPRIMIENDO EL ENTORNO PASADO POR EL PARÁMETRO */
    if (argc == 0)
        return(-1);
    printf("Arguments %i %s\n", argc, argv[0]);
    printf("Enviroment \n");
    int a = 0;
    while (env[a] != NULL)
    {
        printf("%s --> \n", env[a]);
        a++;
    }

    return (0);
}
