/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_enviroment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:49:27 by caliaga-          #+#    #+#             */
/*   Updated: 2024/04/02 14:24:17 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // System calls - family exec 
#include <sys/wait.h>
#include <errno.h>

// OBTENIENDO EL ENTORNO (VARIABLES) CUANDO EL VALOR DEL PARÁMETRO ES NULL

int main(int argc, char **argv, char **env)
{
    // env -i  ./a.out
    //** SI EL PARÁMETRO env ES NULL LE DAMOS EL VALOR DE UNA VARIABLE QUE HEMOS CREADO CON LAS RUTAS MAS PROBABLES
    if (!env[0])
    {
        env[0] = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
        env[1] = NULL;
    }
    //** IMPRIMIENDO EL ENTORNO PASADO POR EL PARÁMETRO
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
