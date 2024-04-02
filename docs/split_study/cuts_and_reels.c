/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuts_and_reels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:04:16 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/14 19:09:48 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // printf()


/** La función «cuts()» devolverá el número de cortes que el delimitador hace
 * dentro de la cadena; sin contar con las coincidencias al principio ó al final
 * de la cadena, ni la duplicidad de delimitadores contiguos. */

size_t cuts(const char *str, char c)
{
    size_t cut[2]; // El array contiene dos valores.
    //int *clon; // Creamos un puntero para retornar el array.

    cut[0] = 0; // 0 - length
    cut[1] = 0; // 1 - repetitions number
    while(str[cut[0]] != '\0') // Mientras no llegue al final de la cadena.
    {
        if (cut[0] == 0)    // Si es el primero "hola "
            if(str[cut[0]] != c)    // Si es letra "hola "
            {   
                printf("%c- ", str[cut[0]]);
                cut[1] += 1;
            }
        if (str[cut[0]] != c) // Si es letra.
            if (str[cut[0]-1] == c) // Y si el anterior es delimitador.
            {
                printf("%c- ", str[cut[0]]);
                cut[1] += 1;
            }
        cut[0]++;         
    }
    // clon = rep; Pasamos el array a un puntero para retornarlo.
    return (cut[1]); // No se pueden devolver arrays, pero sí punteros.
}

/** La función «reels()» devolverá un entero con el número de letras
 * de las palabra de la cadena delimitada por el delimitador. 
 * Manejará un índice externo «int reel = 0;» que irá pasando 
 * por cada una de las palabras de la cadena con cada paso de la función.
*/

int reels(const char *str, char c, size_t *reel)
{
    size_t dim[3];

    dim[0] = 0; // Longitud de la cadena.
    while (str[dim[0]] != '\0')
        dim[0]++; 
    dim[1] = 0;   // Número de letras.
    dim[2] = *reel; // Índice externo de la cadena.
    printf("Indice start %li --> ", *reel);
    while (str[dim[1]+dim[2]] == c)
    {// Mientras haya delimitadores.
        if ((dim[1]+dim[2]) < dim[0]) // Si no supera la longitud de la cadena.
            dim[2]++; // Avanzamos el Índice externo de la cadena.
        else
            break; // Si supera la longitud de la cadena, salimos del bucle.
    }
    while (str[dim[1]+dim[2]] != c)
    {// Mientras no haya delimitadores.
        if ((dim[1]+dim[2]) < dim[0]) // Si no supera la longitud de la cadena.
            dim[1]++; // Avanzamos el contador de letras.
        else
            break; // Si supera la longitud de la cadena, salimos del bucle.
    };
    *reel = dim[2];
    printf("Posicion %li Letras %li\n", *reel, dim[1]);
    return (dim[1]); // Devolvemos la longitud de la palabra.
}

int main()
{
    //char *chain = " hola mundo  que tal";
    //char *chain = "  hola  mundo";
    char *chain = "   hola mundo  que tal esta ";
    //char *chain = " hola mundo  que tal esta";
    int c = ' ';
    size_t cts = cuts(chain, c);
    printf("Cortes %li\n\n", cts);

    size_t reel = 0;
    size_t letters;
    size_t i = 0;
    while(i++ < cts)
    {
        letters = reels(chain, c, &reel);
        printf("Out Posicion %li - ", reel);
        printf("Out Letras %li -->", letters);
        reel += letters; // Avanzamos «reel» con las «letters».
        /** Esto se hace por fuera de la función, para poder 
         * posicionar tener dos posiciones del «reel»
         * inicio y final de la palabra.*/
        printf("Indice stop %li \n\n", reel);
    }

    return (0);
}
