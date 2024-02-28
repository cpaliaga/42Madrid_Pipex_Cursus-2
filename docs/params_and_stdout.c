/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_and_stdout.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:03:53 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/28 14:11:40 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * ESTUDIO DE PARAMETROS POR REFERENCIA Y LA SALIDA ESTANDAR
*/
#include <stdio.h>

int var(int *a)
{
    // PARAMETROS La función recibe un PUNTERO A UNA VARIABLE de enteros.
    //  int num = 10; p(&num);   
    //  Si el parámetro es una variable se pasa por referencia.
    //  int *clon = &num; p(clon); 
    //  Si el parámetro es un puntero se pasa sin más, porque 
    //  el puntero ya es en sí mismo una referencia.
    *a += 1;
    //  Usamos el puntero por valor para que se modifique la variable original externa.
    return (*a); // STDOUT tipo int
}

int *pa(int *arr)
{
    // PARAMETROS La función recibe un PUNTERO A UN ARRAY de enteros.
    //  int arr[2]; int *arrclon = pa(arr);   
    //  El array es un puntero, y por tanto, ya es una referencia.
    int copi[2] = {arr[0]+5, arr[1]+5};
    arr[0] += 1;
    arr[1] += 2;
    //  Para acceder al valor y modificar el array externo, 
    //  sólo hay que acceder por el índice del array.
    int *pt = copi;     // int *pt; pt = copi;
    // RETURN siempre se retornará un puntero y no el array.
    //  Si se retornase el array directamente daría un problema de «scope»
    //  por tratarse de una variable local (interna de la función).
    //  se asignará a un puntero (int *arrclon = pa(arr);), 
    //  y no a un array (int arrclon[2] = pa(arr);) esto daría error.
    return (pt); // STDOUT tipo int *
}

int main()
{
    int num = 10;
    int num2;
    int *clon = &num;
    num2 = var(&num);
    var(clon);
    printf("%i \n", num);
    printf("%i \n", *clon);
    printf("%i \n", num2);

    int arr[2];
    //arr[0] = 10;  También es posible asignar el valor dentro de la función.
    //arr[1] = 20;  También es posible asignar el valor dentro de la función.
    int *arrclon = pa(arr);
    printf("[%i, %i] \n", arr[0], arr[1]);
    printf("[%i, %i] \n", arrclon[0], arrclon[1]);

    return 0;
}
