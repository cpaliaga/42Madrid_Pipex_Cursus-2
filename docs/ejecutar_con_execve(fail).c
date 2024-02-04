/*
How to execute another program in C (using exec) 
https://www.youtube.com/watch?v=OVFEWSP7n8c

https://manpages.debian.org/stretch/manpages-es/execve.2.es.html
https://www.um.es/earlyadopters/actividades/a3/PCD_Activity3_Session1.pdf
https://manpages.debian.org/stretch/manpages-es/wait.2.es.html
*/

#include <stdlib.h> // exit() function.
#include <stdio.h>
#include <unistd.h> // System calls - family exec functions.
#include <time.h>
#include <sys/types.h> /* tipo pid t que no es mas que un 
identificador de proceso linux PID*/
#include <sys/wait.h> // wait() function
#include <errno.h> // Variable errno

int main(int argc, char *argv[], char *envp[])
{
    /* Las funciones de la familia exec_() necesitan 
    ocupar un proceso existente por ello necesitamos 
    crear un proceso hijo que será ocupado por exec_() */
    char *path = "pwd";
    char *vtr[]={"pwd", NULL};
    //char *vector[]={"ping","google.com", NULL};
    char *env[]={NULL};
    //char *enviroment[]={"TEST=envioment-variable", NULL};
    if (execve(path, vtr, env) == -1)
    {
        exit(0); /* Produce la terminación del proceso actual */
        /* El uso de EXIT_SUCCESS y EXIT_FAILURE es ligeramente 
        más portable (para entornos no Unix) que el de 0 y algún 
        valor distinto de cero como 1 o -1.
        */
    };
    int err = errno;
    
    return (0);
}