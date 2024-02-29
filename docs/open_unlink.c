// close and unlink system calls in Linux
// https://www.youtube.com/watch?v=1KMK967_fiQ

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
// La función «unlink()» se usa para borrar un archivo del directorio.
// En la pantalla se muestra 0 de lo contrario error.
int main(){
    close(2); // close stderr
    int fd = open("smile.txt", O_RDONLY | O_CREAT, 0777);
    printf("fd = %d (0 is sucess, -1 is failure)\n", fd);
    int un = unlink("smile.txt");
    printf("un = %d\n", un);
    printf("EXIT_SUCCESS = %d\n", EXIT_SUCCESS);
    printf("EXIT_FAILURE = %d\n", EXIT_FAILURE);
    printf("STDIN_FILENO = %d\n", STDIN_FILENO);
    printf("STDOUT_FILENO = %d\n", STDOUT_FILENO);
    printf("STDERR_FILENO = %d\n", STDERR_FILENO);

    return (0);
}
// gcc -o 3 open_unlink.c
// ./3 &   <--- esto ejecuta y muestra el número de proceso del programa. 
// cd /proc  <--- esto nos lleva al directorio donde se encuentran los procesos.
// Exit Codes in Linux.
// https://www.youtube.com/watch?v=hg_vmrHhe84