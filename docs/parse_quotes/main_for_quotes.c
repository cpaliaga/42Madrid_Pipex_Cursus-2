/**
 * PROGRAMA «main_for_quotes.c»
*/
       
#include <stdio.h>
#include <unistd.h>
//  El objetivo de este ejercicio es entender
//  cómo se comporta la función «main»
//  cuando se le pasa un argumento con comillas.
//  Se imprimirá el argumento que se le pasa a la función.

int main(int argc, char **argv)
{
    if (argc != 2)
        return (-1);
    printf("argv[1] = %s\n", argv[1]);
    return (0);
}

//  COMPILADO gcc -Wall -Wextra -Werror main_for_quotes.c -o MfQ

//  EJECUCIÓN ./MfQ "Hola mundo"
//  argv[1] = Hola mundo

// ./MfQ "tr ' ' '\n'"
// argv[1] = tr ' ' '\n'

// ./MfQ "awk '{print $1}'"
// argv[1] = awk '{print $1}'

//  ./MfQ "cat /etc/passwd | awk -F ":" '{print $1}'"
//  ERROR:  argv[1] = cat /etc/passwd | awk -F : '{print }'

//  ./MfQ "awk -F ':' '{print $1}'"
//  argv[1] = awk -F ':' '{print }'

//  ./MfQ 'awk -F ":" '{print $1}''
//  Con esta estructura se entiende que se le pasa más de un argumento.
//  Por tanto el programa no se ejecuta.

//  ./MfQ "awk -F \":\" '{print \$1}'"
//  argv[1] = awk -F ":" '{print $1}'

//  CONCLUSIONES
//  La cadena que se delimita por comillas dobles 
//  es capáz de albergar comillas simples, pero nó al revés.
//  Dentro de esta cadena siempre hay que escapar las comillas dobles y el signo de dolar.

//  https://geekland.eu/uso-del-comando-awk-en-linux-y-unix-con-ejemplos/