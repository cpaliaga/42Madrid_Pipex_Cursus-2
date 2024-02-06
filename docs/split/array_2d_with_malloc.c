/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_2d_with_malloc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:02:38 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/06 19:04:42 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   Dynamically allocated multi-dimensional arrays in C                      */
/*   https://www.youtube.com/watch?v=-y8FUvRq_88&t=4s                         */
/*   How to properly deal with dynamically allocated memory                   */
/*   https://www.youtube.com/watch?v=el5F2aa0jfc                              */
/* ************************************************************************** */
#include <stdio.h> // printf()
#include <stdlib.h> // malloc(), free()

void char_array()
{
        char **arr_char;
    int ch;

    arr_char = (char **)malloc(sizeof(char *) * 3);
    if (!arr_char)
        return ; 
        /* En una funcion que retornase «char» sería return (NULL);*/
        /* En una funcion que retornase «int» sería return (-1);*/
        /* En una funcion que retornase «void» sería return ;*/
    ch = 0;
    while (ch++ < 4)
    {
        arr_char[ch] = (char *)malloc(sizeof(char *) * 4);
        arr_char[ch] = "Hola"; 
        printf("%s\n", arr_char[ch]);
    }
    /** FREE MATRIX */
    /** La memoria alocada dinámicamente no se gestiona automáticamente,
    * al dejar de usarse ha de liberarse manualmente con «free()», una única vez.
    * y lugego asignarle el valor NULL para evitar errores de segmentación.
    */
    while (ch-- < 3)
    {
        free(arr_char[ch]);
        arr_char[ch] = NULL;
    }
    free(arr_char);
    arr_char = NULL;
}

void int_array()
{
    int **arr;
    int i;

    arr = (int **)malloc(sizeof(int *) * 3);
    if (!arr)
        return ;
    //memset(arr,0, sizeof(int *) * 3);
    i = 0;
    while (i++ < 4)
    {
        arr[i] = (int *)malloc(sizeof(int *) * 4);
        arr[i][0] = 1;
        arr[i][1] = 2;
        arr[i][2] = 3;
        arr[i][3] = 0;    
        printf("%i - %i - %i - %i \n",arr[i][0], arr[i][1], arr[i][2], arr[i][3]);
    }
    /** FREE MATRIX */
    /** La memoria alocada dinámicamente no se gestiona automáticamente,
    * al dejar de usarse ha de liberarse manualmente con «free()», una única vez.
    * y lugego asignarle el valor NULL para evitar errores de segmentación.
    */
    while (i-- < 3)
    {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
    arr = NULL;
}

int main()
{
    char_array();
    int_array();

    return (0);
}