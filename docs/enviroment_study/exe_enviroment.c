#include <stdio.h> // printf() function
#include <unistd.h> // System calls: close() - family exec() functions.
#include <sys/types.h> 
/* tipo pid_t que no es mas que un identificador de proceso linux PID */
#include <sys/wait.h> 
// wait() function
#include <errno.h> // Variable errno
#include <stdlib.h> // exit() function.
#include <fcntl.h> // O_RDONLY, O_WRONLY, O_RDWR
#include <string.h>

//** Las funciones de la familia exec_() necesitan
// *  ocupar un proceso existente por ello

// ** Control de errores EXIT_FAILURE *

/*
void err_ctl(int exe)
{   if (exe == -1)
    {
        perror(strerror(errno));
        exit(EXIT_FAILURE); // exit(1);
    }
}

int fd_openfile(char *url, char opt)
{
    int fd;

    if (opt == 'R')
        fd = open(*url, O_RDONLY, 0770);
    else
        fd = open(*url, O_WRONLY, 0770);
    if (fd == -1)
        return (1);
    return (fd);
}
*/

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (*(str + a) != '\0')
		a++;
	return (a);
}

int main(void)
{
    char *argVec[]={"/bin/lss","-la", NULL}; // Parámetro de execve()
    char *env[]={NULL};  // Parámetro de execve()
    pid_t pid; /** Nos reparamos para clonar el proceso y tener un proceso hijo */
    
    pid = fork(); /** Bifurcamos/clonamos el proceso para obtener el proceso hijo */
    if (pid == -1) /** Control de errores EXIT_FAILURE */
        return(1);

    if (pid == 0) /* PROCESO HIJO */
    {
        /**
        if (access(argVec[0], X_OK || F_OK) == 0)
        {
            perror("Acceso");  // No such file or directory
            exit(1);
        }
        */
        int ex = execve(argVec[0], argVec, env); /** 
        * Una vez que se ejecute execve() sobreescribirá ∑overwrite∑ 
        * el procedimiento de main(). Todas las instrucciones 
        * a partir de este punto no se ejecutarán. Excepto que execve()
        * se ejecute en un proceso hijo de main() */
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
