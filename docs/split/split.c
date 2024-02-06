/**
 * Dynamically allocated multi-dimensional arrays in C
 * https://www.youtube.com/watch?v=-y8FUvRq_88&t=4s
*/
#include <stdio.h> // printf()
#include <stdlib.h> // malloc(), free()

/** matrix_free(char **array, size_t row) libera la memoria del array 
 * de 2 dimensiones (matriz ó array de array's) que hemos creado ó 
 * intentado crear mediante la alocación dinámica de memoria. 
 * Recibe dos parámetros: 
 * la matriz y el número del array dentro de la matriz. */
static char **error_matrix_free(char **arr, size_t row) 
{
    if (!arr[row])
    {
        while (row-- > 0)
            if (arr[row])
            {
                free(arr[row]);
                arr[row] = NULL;
            }
        if (arr)
        {
            free(arr);
            arr = NULL;
        }
    }
	return (NULL);
}

size_t  ft_cuts(const char *str, int c)
{
    size_t rep[2]; // El array contiene dos valores.

    rep[0] = 0; // 0 - length
    rep[1] = 0; // 1 - repetitions number
    while(str[rep[0]] != '\0') // Mientras no llegue al final de la cadena.
    {
        if (rep[0] == 0)    /* Si es el primero */
            if(str[rep[0]] != c)    /* Si es letra */
                rep[1] += 1;
        if (str[rep[0] + 1] != '\0')  /* Si no es el último */
            if (str[rep[0]] == c && str[rep[0] + 1] != c) /* Si es delimitador y siguiente letra */
                rep[1] += 1;
        rep[0]++;         
    }
    return (rep[1]); // No se pueden devolver arrays, pero sí punteros.
}

size_t  ft_reels(const char *str, char c, size_t *reel)
{
    size_t dim[3];

    dim[0] = 0;
    while (str[dim[0]] != '\0')
        dim[0]++; /* Longitud de la cadena */
    dim[1] = 0;   /* Número de letras */
    dim[2] = *reel; /* Índice externo de la cadena */
    while (str[dim[1] + dim[2]] == c)
    {// Mientras haya delimitadores.
        if ((dim[1] + dim[2]) < dim[0]) // Si no supera la longitud de la cadena.
            dim[2]++; // Avanzamos el puntero de delimitadores.
        else
            break; // Si supera la longitud de la cadena, salimos del bucle.
    }
    while (str[dim[1] + dim[2]] != c)
    {// Mientras no haya delimitadores.
        if ((dim[1] + dim[2]) < dim[0]) // Si no supera la longitud de la cadena.
            dim[1]++; // Avanzamos el contador de letras.
        else
            break; // Si supera la longitud de la cadena, salimos del bucle.
    }; 
    *reel = dim[2];
    return (dim[1]); // Devolvemos la longitud de la palabra.
}

void    ft_fill(char *arr, size_t letters, const char *str, size_t *reel)
{
    size_t l;

    l = 0;
    while (l < (letters + 1))
    {
        arr[l++] = str[*reel++];
    }
    arr[l] = '\0';
}

/** La función «split» devolverá un array de arrays. 
 * Ya que su finalidad es la de divir una cadena por el delimitador.
 * https://www.youtube.com/watch?v=Cj69VbwloW8
 * 
 * */

char **split(const char *str, char c)
{
    char **spine;
    size_t reel;
    size_t letters;
    size_t cuts;
    size_t p;

    if (!str || !c)
        return (NULL);
    cuts = ft_cuts(str, c);
    spine = (char **)malloc(sizeof(char *) * (cuts));
    if (!spine)
        return (NULL);
    reel = 0;
    p = 0;
    printf(" Spine creaado ");
    while (p++ < (cuts + 1))
    {
        letters = ft_reels(str, c, &reel);
        spine[p] = (char *)malloc(sizeof(char) * (letters + 1));
        error_matrix_free(spine, p);
        ft_fill(spine[p], letters, str, &reel);
    }
    return (spine);
}

int main()
{
    char *chain = "hola mundo  que tal esta ";
    int c = ' ';
    char **arr = split(chain, c);
    int row = 0; 
    while (arr[++row] != '\0')
    {
        printf("%s\n", arr[row]);
        arr++;
    }
    /** FREE MATRIX 
    while (row-- > 0)
        if (arr[row])
        {
            free(arr[row]);
            arr[row] = NULL;
        }
    if (arr)
    {
        free(arr);
        arr = NULL;
    } */
    return (0);
}
/* [1]    20109 segmentation fault  ./a.out */