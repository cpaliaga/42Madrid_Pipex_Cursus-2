/* ************************************************************************** */
/*   array_2d_with_malloc.c                                                   */
/*   By: caliaga-                                                             */
/*   Created: 2024/02/03 16:59:21 by caliaga-                                 */ 
/*   Dynamically allocated multi-dimensional arrays in C                      */
/*   https://www.youtube.com/watch?v=-y8FUvRq_88&t=4s                         */
/*   How to properly deal with dynamically allocated memory                   */
/*   https://www.youtube.com/watch?v=el5F2aa0jfc                              */
/* ************************************************************************** */
#include <stdio.h> // printf()
#include <stdlib.h> // malloc(), free()

int main()
{
    int **arr;
    int i;

    arr = (int **)malloc(sizeof(int *) * 3);
    if (!arr)
        return (1);
    memset(arr,0, sizeof(int *) * 3);
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

    return (0);
}