#include <stdio.h> // printf() function
#include <unistd.h> // System calls: close() - family exec() functions.
#include <sys/types.h> 
/* tipo pid_t que no es mas que un identificador de proceso linux PID */
#include <sys/wait.h> 
// wait() function
#include <errno.h> // Variable errno
#include <stdlib.h> // exit() function.
#include <string.h>

//** Las funciones de la familia exec_() necesitan
// *  ocupar un proceso existente por ello

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

int main(void)
{
    char *argVec[]={"/usr/bin/env", NULL}; // Parámetro de execve() /bin/ls     /usr/bin/env
    // En este caso el comando ls sí tieene su stdout por pantalla
    // pero el comando env no hace stdour por pantalla.
    char *env[]={NULL};  // Parámetro de execve()
    pid_t pid; /** Nos reparamos para clonar el proceso y tener un proceso hijo */
    
    pid = fork(); /** Bifurcamos/clonamos el proceso para obtener el proceso hijo */
    if (pid == -1) /** Control de errores EXIT_FAILURE */
        return(1);

    if (pid == 0) /* PROCESO HIJO */
    {
        int ex = execve(argVec[0], argVec, env);
        printf("exe %i \n", ex);
        if (ex == -1)
        {
            perror("");
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
