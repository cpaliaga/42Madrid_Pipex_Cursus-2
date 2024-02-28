/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting_file_descriptors.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:11:52 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/28 14:11:54 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** Redirecting standard output in C
 * https://www.youtube.com/watch?v=5fnVr-zH-SE
 * https://www.youtube.com/watch?v=rA7-c37WjXk
*/

/** Linux Programmer's Manual
 * https://tldp.org/LDP/lpg-0.4.pdf 
 * https://hackmd.io/@brlin/orncb-linux-programmer-s-manual/https%3A%2F%2Fhackmd.io%2F%40brlin%2Forncb-linux-programmer-s-manual%2Fedit%3Fedit
 * */
#include <stdio.h> // printf() function
#include <unistd.h> // System calls - family exec close ()
#include <sys/wait.h> // wait() function
#include <fcntl.h> // open() function
// open() function #include <fcntl.h> https://man7.org/linux/man-pages/man2/open.2.html
// open() function - Modos de Acceso: O_RDONLY, O_WRONLY, or O_RDWR
// open() function - Permisos: 00700 user (file owner) has read, write, and execute.

int fd_openfile(char *url, char opt){
    int fd;

    if (opt == 'R')
        fd = open(url, O_RDONLY, 0777);
    if (opt == 'W')
        fd = open(url, O_WRONLY, 0777);
    else
        fd = -1;
    if (fd == -1)
        return (1);
    return (fd);
}

int main (void)
{
    // Los file descriptors de las entradas y salidas 
    // estandar son: 
    // 0-STDIN_FILENO, 
    // 1-STDOUT_FILENO
    // y 2-STDERR
    // tras estos se numeran otros file descriptors,
    // como por ejemplo los del archivo que se abre con open()

    int pid = fork(); // CREACIÓN DEL PROCESO HIJO.
    if (pid < 0)
        return (1);
    if (pid == 0) /* PROCESO HIJO */
    {
        int fd_file = fd_openfile("outfile", 'W');
        printf("fd_outfile: %i\n", fd_file);

        int fd_dup = dup2(fd_file, STDOUT_FILENO); 
        // Redireccionamos la salida estandar al archivo.
        // Ahora el «fd» del archivo va a ser el «fd»
        // de la salida estandar, el archivo va a 
        // tomar la posición de esta.
        // Hecho esto ya podemos cerrar el «fd» del archivo.
        // Apartir de aquí todo lo que se imprima en la salida
        // estandar se va a escribir en el archivo.
        printf("fd_dup: %i\n", fd_dup); // Sale en el archivo.
        close(fd_file); // Ya no es necesario tener abierto el archivo.
        printf("fd_dup: %i\n", fd_dup); // Sale en el archivo.       

        int ex = execlp("ping", "ping", "-c", "5", "google.com", NULL);
        if (ex == -1)
            return (1);
    }
    waitpid(pid, NULL, 0); // Esperamos a que el proceso hijo termine.
    return (0);
}
