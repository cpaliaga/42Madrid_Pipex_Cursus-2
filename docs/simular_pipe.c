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
    «parent process» debe existir para que el proceso hijo no se 
    quede huérfano */
    /* Declaramos un array de dos enteros para los  «file 
    descriptors» */
    int fd[2];
    //  fd[0] - read (para leer) O_RDONLY
    //  fd[1] - write (pasa escribir) O_WRONLY
    if (pipe(fd) == -1) //  Creamos el «pipe» y controlamos errores del mismo.
        return (1);
    
    //  Ahora vamos a crear dos procesos hijos «child process». 
    //  Uno de los procesos creados con fork será nuestro principal.
    int pid1 = fork();  //  Creamos el segundo proceso hijo.
    if (pid1 < 0)  //  Control de errores del primer proceso hijo.
        return (1);
    
    if (pid1 == 0)  // PRIMER PROCESO HIJO. («ping»)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]); // Cierro READ
        close(fd[1]); // Cierro WRITE
        execlp("ls", "ls", "-la", NULL);
    }
    
    int pid2 = fork(); //  Creamos el segundo proceso hijo.
    if (pid2 < 0)   //  Control de errores del segundo proceso hijo.
        return (3);
        
    if (pid2 == 0)  //  SEGUNDO PROCESO HIJO. («grep»).
    {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("grep", "grep", ".html", NULL);
    }
    
    close(fd[0]);
    close(fd[1]);
    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    return (0);    
}