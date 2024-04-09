#include <stdio.h>

int main(int argc, char **argv, char **env)
{
    char *hola = "hola mundo"; // 10 caracteres en posiciones del 0 al 9.
    
    printf("Pruebas con el índice en 0 \n");

    int a = 0;
    while (hola[a] != '\0')
    {
        printf("%i - ", a++);
    }
    printf("\n while(){a++} OBTENEMOS EL NÚMERO DE CARACTERES \n\n");
    
    int b = 0;
    while (hola[b] != '\0')
    {
        printf("%i - ", ++b);
    }
    printf("\n while(){++b} OBTENEMOS EL NÚMERO DE CARACTERES \n\n");
    
    int c = 0;
    while (hola[c++] != '\0')
    {
        printf("%i - ", c);
    }
    printf("\n while(c++){} OBTENEMOS EL NÚMERO DE CARACTERES \n\n");
    
    int d = 0;
    while (hola[++d] != '\0')
    {
        printf("%i - ", d);
    }
    printf("\n while(++d){} OBTENEMOS LA ULTIMA POSICION DEL INDICE \n\n");

    printf("Pruebas con el índice en -1 \n");

    int aa = -1;
    while (hola[aa] != '\0')
    {
        printf("%i - ", aa++);
    }
    printf("\n while(){aa++} OBTENEMOS EL NÚMERO DE CARACTERES \n\n");
    
    int bb = -1;
    while (hola[bb] != '\0')
    {
        printf("%i - ", ++bb);
    }
    printf("\n while(){++bb} OBTENEMOS EL NÚMERO DE CARACTERES \n\n");
    
    int cc = -1;
    while (hola[cc++] != '\0')
    {
        printf("%i - ", cc);
    }
    printf("\n while(cc++){} OBTENEMOS EL NÚMERO DE CARACTERES \n\n");
    
    int dd = -1;
    while (hola[++dd] != '\0')
    {
        printf("%i - ", dd);
    }
    printf("\n while(++dd){} OBTENEMOS LA ULTIMA POSICION DEL INDICE \n\n");

    return (0);
}

//  gcc run.c -o ru && ./ru