/* How to execute another program in C (using exec) 
https://www.youtube.com/watch?v=OVFEWSP7n8c

https://manpages.debian.org/stretch/manpages-es/execve.2.es.html
https://www.um.es/earlyadopters/actividades/a3/PCD_Activity3_Session1.pdf
https://manpages.debian.org/stretch/manpages-es/wait.2.es.html
https://en.wikipedia.org/wiki/File_descriptor
*/

#include <stdlib.h> // exit() function.
#include <stdio.h>
#include <unistd.h> // System calls - family exec functions.
#include <time.h>
#include <sys/types.h> /* tipo pid t que no es mas que un 
identificador de proceso linux PID*/
#include <sys/wait.h> // wait() function
#include <errno.h> // Variable errno
/** tr [OPTION]... SET1 [SET2]
 * Translate, squeeze (-s), and/or delete (-d) characters from 
 * standard input (keyboard), writing to standard output (screen).
*/

/** Las funciones de la familia exec_() necesitan
 *  ocupar un proceso existente por ello */

int main(void)
{
    int ex;   
    char cmd_path[] = "/usr/bin/tr";
    char *argVec[]={"tr"," ", "\n", NULL};
    char *env[]={NULL};
    ex = execve(cmd_path, argVec, env);
    if (ex == -1)
    {
        perror("No se puede ejecutar");
        exit(1); 
        /* exit (int status) Produce la terminación del proceso actual */
        /* status - El uso de EXIT_SUCCESS y EXIT_FAILURE es ligeramente 
        más portable (para entornos no Unix) que el de 0 y algún 
        valor distinto de cero como 1 o -1.*/
    };
    printf("%i", ex);
    //close(); close a file descriptor
    /* #include <unistd.h>  int close(int fd);
    Returns zero on success.  On error, -1 is returned, and
       errno is set to indicate the error.
    */
    return (0);
}