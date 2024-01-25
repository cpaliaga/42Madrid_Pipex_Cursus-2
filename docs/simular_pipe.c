/*
Simulating the pipe "|" operator in C  
https://www.youtube.com/watch?v=6xbLgZpOBi8
Recrea la instrucción de bash shell:
ping -c 5 google.com | grep rtt
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // System calls - family exec 
#include <sys/wait.h>

int main (void)
{
    /* Mientra que el proceso hijo siga abierto el proceso padre
    «parent process» debe existir para que el proceso hijo 
    no se quede huérfano */
    /* Declaramos un array de dos enteros para los 
    «file descriptors» */
    int fd[2];
    // fd[0] - read (para leer)
    // fd[1] - write (pasa escribir)
    
    /* Creamos el «pipe» y controlamos errores */
    if (pipe(fd) == -1)
    {
        return (1);    
    }
    
    /* Ahora vamos a crear dos procesos hijos «child process». 
    Uno de los procesos creados con fork será nuestro principal 
    */
    
    int pid1 = fork();
    
    /* Control de errores del primer proceso hijo */
    if (pid1 < 0)
    {
        return (1);
    }
    
    if (pid1 == 0)
    {
        /* Ahora estamos en el proceso hijo «child process» («ping») */
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
    }
    
    int pid2 = fork();

    /* Control de errores del segundo proceso hijo */
    if (pid2 < 0)
    {
        return (3);
    }
    
    if (pid2 == 0) 
    {
        /* Ahora estamos en el proceso hijo «child process» («grep»)
         */
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("grep", "grep", "rtt", NULL);
    }
    
    close(fd[0]);
    close(fd[1]);
    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    return (0);    
}