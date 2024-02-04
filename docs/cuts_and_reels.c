/* ************************************************************************** */
/*   cuts_and_reels.c                                                         */
/*   By: caliaga-                                                             */
/*   Created: 2024/02/03 16:59:21 by caliaga-                                 */
/* ************************************************************************** */
#include <stdio.h> // printf()

int *cuts(const char *str, int c)
{
    int rep[2]; // El array contiene dos valores.
    int *clon; // Creamos un puntero para retornar el array.

    rep[0] = -1; // 0 - length
    rep[1] = 0; // 1 - repetitions number
    while(str[++rep[0]]) // Mientras no llegue al final de la cadena.
    {
        if (str[rep[0]] == c && rep[0] != 0)
        {    // Cuando coincida el caracter y no sea el primer caracter.
            if(str[rep[0]+1] != '\0' && str[rep[0]+1] != ' ')
            {   // Cuando el siguiente no sea el final ni otro espacio.
                printf("Primera Letra %c\n", str[rep[0]+1]);
                rep[1] += 1;
            }
        }
    };
    clon = rep; // Pasamos el array a un puntero para retornarlo.
    return (clon); // No se pueden devolver arrays, pero sí punteros.
}

/**
 * La función «cuts()» devolverá un puntero a un array de dos enteros.
 * En la posición «0» el valor será la longitud de la cadena.
 * En la posición «1» el valor será el número de coincidencias del delimitator
 * dentro de la cadena; sin contar con las coincidencias al principio ó al final
 * de la cadena, ni la duplicidad de delimitadores contiguos.
*/

int reels(const char *str, int c, int *reel)
{
    int stop;

    stop = 0;
    if (!str || !c)
        return (-1);
    while (str[*reel+stop] == c && str)
        *reel += 1;
    while (str[*reel+stop] != c && str)
        stop++;
    *reel += stop; // Avanzamos el puntero y modificamos la valiable externa (por referencia).
    
    return (stop); // Devolvemos la longitud de la palabra.
}

/**
 * La función «reels()» devolverá un entero con el número de letras
 * de las palabra de la cadena delimitada por el delimitador. 
 * Manejará un índice externo «int reel = 0;» que irá pasando 
 * por cada una de las palabras de la cadena con cada paso de la función.
*/

int main()
{
    char *chain = " hola mundo  que tal esta ";
    int c = ' ';
    int *cts = cuts(chain, c);
    printf("Longitud %i, cortes %i\n", cts[0], cts[1]);

    int reel = 0;
    int i = 0;
    while(i++ < (cts[1]+1))
    {
        printf("Reels %i \n", reels(chain, c, &reel));
    }

    return (0);
}