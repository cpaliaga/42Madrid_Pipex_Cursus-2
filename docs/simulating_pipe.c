/*
Simulating the pipe "|" operator in C  
https://www.youtube.com/watch?v=6xbLgZpOBi8
Recrea la instrucción de bash shell:
ping -c 5 google.com | grep rtt
https://www.youtube.com/watch?v=8LdQ09Ep9RY

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // System calls - family exec 
#include <sys/wait.h>

int main (void)
{
    
    // Declaramos un array de dos enteros para los «file descriptors»
    //  fd[0] - read (para leer) O_RDONLY
    //  fd[1] - write (pasa escribir) O_WRONLY
    int fd[2];
    if (pipe(fd) == -1) //  Creamos el «pipe» y controlamos errores del mismo.
        return (1);
    //  pipe() es una función de envoltorio «wrap» de una estructura «struct» 
    //  de dos enteros que van a alojar los «file descriptors» del «pipe».
    
    //  Ahora vamos a crear dos procesos hijos «child process». 
    //  Uno de los procesos creados con fork será nuestro principal.
    //  La ejecución comienza con el último fork-child, y lo hace 
    //  en el sentido inverso a la creación.
    //  pipe() existirá en todos los procesos.

    int pid1 = fork();  //  Creamos el segundo proceso hijo.
    if (pid1 < 0)  //  Control de errores del primer proceso hijo.
        return (1);
    if (pid1 == 0)  // PRIMER PROCESO HIJO. («ping»)
    {
        // Redireccionamos la salida estandar al pipe.
        // Ya se puede cerrar el pipe entero fd[0] y fd[1].
        // Ahora cuando se ejecute «ping» su salida estandar 
        // será al «pipe» en «write».
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
    }
    
    int pid2 = fork(); //  Creamos el segundo proceso hijo.
    if (pid2 < 0)   //  Control de errores del segundo proceso hijo.
        return (3);
    if (pid2 == 0)  //  SEGUNDO PROCESO HIJO. («grep»).
    {
        // Redireccionamos la entrada estandar al pipe.
        // Ya se puede cerrar el pipe entero fd[0] y fd[1].
        // Ahora cuando se ejecute «grep» su entrada estandar 
        // será al «pipe» en «read».
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("grep", "grep", ".html", NULL);
    }
    
    close(fd[0]);
    close(fd[1]);
    //  * Mientra que el proceso hijo siga abierto el proceso padre
    //  «parent process» debe existir para que el proceso hijo no se 
    //  quede huérfano */
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    return (0);    
}