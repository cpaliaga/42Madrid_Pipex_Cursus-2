#include <unistd.h>
int main(){
char filename[] = /bin/shx00;
char **argv, **envp;
char **argv, **envp;
char **argv, **envp;
argv[0] = filename;             // único argumento: nombre del programa
argv[1] = 0;                    //  fin del array de argumentos
 
envp[0] = 0;                    //  fin del array de entorno
execve(filename, argv, envp);
}
