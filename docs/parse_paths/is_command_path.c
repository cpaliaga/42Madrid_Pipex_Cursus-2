/** IS_COMMAND_PATH.C **/

# include <stdio.h>     // printf()
# include <unistd.h>    // access(), F_OK, X_OK

int is_command_path(char *str)
{
    if (access(str, F_OK | X_OK) == -1)
        return (-1);
    return (0);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    int res = is_command_path(argv[1]);
    printf("%d - %s\n", res, argv[1]);
    return (0);
}

// Esta función comprueba (retorno 0, -1) si el parámetro es la ruta a un comando válido.
// QUE LA RUTA EXISTA Y SEA EJECUTABLE.

// Averiguar la ruta de los comandos para pruebas : which ls
//      /usr/bin/ls

// gcc -Wall -Wextra -Werror is_command_path.c -o Is-Command-Path && ./Is-Command-Path ls
// gcc -Wall -Wextra -Werror is_command_path.c -o Is-Command-Path && ./Is-Command-Path /usr/bin/ls
// valdgrin --leak-check=yes ./Is-Command-Path
// Otras opciones de valgrin:
// To redirect outputs in a file:  --log-file=Valgrind.log
// To check memory leaks   :  --leak-check=yes
// Fix Memory Leaks in C Code with Valgrind
// https://www.youtube.com/watch?v=DyqstSE470s