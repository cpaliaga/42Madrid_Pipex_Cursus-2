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
// #include <errno.h> // Variable errno
// #include <stdlib.h> // exit() function.
/** tr [OPTION]... SET1 [SET2]
 * Translate, squeeze (-s), and/or delete (-d) characters from 
 * standard input (keyboard), writing to standard output (screen).
*/

/** Las funciones de la familia exec_() necesitan
 *  ocupar un proceso existente por ello */

int main(void)
{
    pid_t pid; /** Nos reparamos para clonar el proceso y tener un proceso hijo */
    
    char *argVec[]={"/bin/ls","-la", NULL}; // Parámetro de execve()
    char *env[]={NULL};  // Parámetro de execve()

    pid = fork(); /** Bifurcamos/clonamos el proceso para obtener el proceso hijo */
    if (pid == -1) /** Control de errores EXIT_FAILURE */
    {
        return(-1);
    }

    if (pid == 0) /* PROCESO HIJO */
    {
        int ex = execve(argVec[0], argVec, env); /** 
        * Una vez que se ejecute execve() sobreescribirá ∑overwrite∑ 
        * el procedimiento de main(). Todas las instrucciones 
        * a partir de este punto no se ejecutarán. Excepto que execve()
        * se ejecute en un proceso hijo de main() */
       if (ex == -1) /** Control de errores EXIT_FAILURE */
       {
            perror("Error");
            /* exit(1); exit (int status) Produce la terminación del proceso actual */
            /** status - El uso de EXIT_SUCCESS y EXIT_FAILURE es ligeramente 
             * más portable (para entornos no Unix) que el de 0 y algún 
             * valor distinto de cero como 1 o -1.*/
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