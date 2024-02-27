### 42Madrid Cursus
# Pipex Proyect

Realizaremos un ejecutable que recibe 4 parámetros de conformidaad con esta estructura:
./pipex archivo1 comando1 comando2 archivo2

Nuestro Makefile copilará este ejecutable y otras librerias permitidas como libft (Ver. Proyecto Libft)

LISTADO DE FUNCIONES PERMITIDAS
- open() close(), [an example](/docs/open-close.md/ "Title")
- read(), write(),
- malloc(), free(), 
- perror(), strerror(), 
- access(), 
- dup(), dup2(),
- execve(), 
- exit(), 
- fork(), 
- pipe(), [¿Cómo funciona?](/docs/mkd/pipe.md/ "Pipe function")
- unlink(), 
- wait(), waitpid(),
- ft_printf() and any equivalent YOU coded.

## Ejemplos gestiona los errores como lo hacen los comandos de shell

$> ./pipex infile "ls -l" "wc -l" outfile:

deberá hacer lo mismo que “<infile ls -l | wc -l >outfile”

$> ./pipex infile "grep a1" "wc -w" outfile

deberá hacer lo mismo que “<infile grep a1 | wc -w >outfile”
