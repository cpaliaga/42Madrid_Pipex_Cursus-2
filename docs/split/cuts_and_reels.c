/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuts_and_reels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:26:19 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/06 19:53:38 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // printf()

size_t cuts(const char *str, int c)
{
    size_t rep[2]; // El array contiene dos valores.

    rep[0] = 0; // 0 - length
    rep[1] = 0; // 1 - repetitions number
    while(str[rep[0]] != '\0') // Mientras no llegue al final de la cadena.
    {
        if (rep[0] == 0)    /* Si es el primero */
            if(str[rep[0]] != c)    /* Si es letra */
                rep[1] += 1;
        if (str[rep[0]+1] != '\0')  /* Si no es el último */
            if (str[rep[0]] == c && str[rep[0]+1] != c) /* Si es delimitador y siguiente letra */
                rep[1] += 1;
        rep[0]++;         
    }
    return (rep[1]); // No se pueden devolver arrays, pero sí punteros.
}

/**
 * La función «cuts()» devolverá un size_t con el número de cortes que 
 * ha creado el delimitador.
 * En la posición «0» el valor será la longitud de la cadena.
 * En la posición «1» el valor será el número de coincidencias del delimitator.
*/

size_t reels(const char *str, char c, size_t *reel)
{
    size_t dim[3];

    dim[0] = 0;
    while (str[dim[0]] != '\0')
        dim[0]++; /* Longitud de la cadena */
    dim[1] = 0;   /* Número de letras */
    dim[2] = *reel; /* Índice externo de la cadena */
    while (str[dim[1]+dim[2]] == c)
    {// Mientras haya delimitadores.
        if ((dim[1]+dim[2]) < dim[0]) // Si no supera la longitud de la cadena.
            dim[2]++; // Avanzamos el puntero de delimitadores.
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

/**
 * La función «reels()» devolverá un entero con el número de letras
 * de las palabra de la cadena delimitada por el delimitador. 
 * Manejará un índice externo «int reel = 0;» que irá pasando 
 * por cada una de las palabras de la cadena con cada paso de la función.
*/

int main()
{
    //char *chain = " hola mundo  que tal";
    //char *chain = "hola mundo  que tal esta";
    char *chain = "   hola mundo  que tal esta hoy";
    //char *chain = " hola mundo  que tal esta";
    int c = ' ';
    size_t cts = cuts(chain, c);
    printf("Longitud , cortes %li\n", cts);

    size_t reel = 0;
    size_t rls;
    size_t i = 0;
    while(i++ < cts)
    {
        rls = reels(chain, c, &reel);
        printf("Letras %li ", rls);
        reel += rls; 
        /* Hay que actualizar el indice reel con las letras de reels, 
        para un posicionamiento correcto en la siguiente vuelta. */
        printf("Indice %li \n", reel);
    }

    return (0);
}