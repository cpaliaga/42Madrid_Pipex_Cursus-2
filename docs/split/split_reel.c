/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_reel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:54:11 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/18 20:36:16 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    size_t cut[2];
    
    cut[0] = 0;
    cut[1] = 0;
    while(str[cut[0]] != '\0')
    {
        if (cut[0] == 0)
            if(str[cut[0]] != c)
                cut[1] += 1;
            
        if (str[cut[0]] != c)
            if (str[cut[0]-1] == c)
                cut[1] += 1;
        cut[0]++;         
    }
    return (cut[1]);
}

size_t  ft_reels(const char *str, char c, size_t *reel)
{
    size_t dim[3];

    dim[0] = 0;
    while (str[dim[0]] != '\0')
        dim[0]++; 
    dim[1] = 0;
    dim[2] = *reel;
    while (str[dim[1]+dim[2]] == c)
    {
        if ((dim[1]+dim[2]) < dim[0])
            dim[2]++;
        else
            break;
    }
    while (str[dim[1]+dim[2]] != c)
    {
        if ((dim[1]+dim[2]) < dim[0])
            dim[1]++;
        else
            break;
    };
    *reel = dim[2];
    return (dim[1]);
}

void    ft_fill(char *arr, const char *str, size_t letters, size_t *reel)
{
    size_t l;
    size_t clone;

    l = 0;
    clone = *reel;
    while (l < letters && str[clone + l] != '\0')
    {
        arr[l] = str[clone + l];
        l++;
    }
    arr[l] = '\0';
}

/** La función «split_reel» devolverá un array de arrays. 
 * Ya que su finalidad es la de divir una cadena por el delimitador.
 * https://www.youtube.com/watch?v=Cj69VbwloW8
 * 
 * */

char **split_reel(const char *str, char c, size_t *reel)
{
    char **spine;
    
    size_t letters;
    size_t cuts;
    size_t p;

    if (!str || !c)
        return (NULL);
    cuts = ft_cuts(str, c);
    spine = (char **)malloc(sizeof(char *) * (cuts + 1));
    if (!spine)
        return (NULL);
    p = 0;
    while (p < (cuts))
    {
        letters = ft_reels(str, c, reel);
        spine[p] = (char *)malloc(sizeof(char) * (letters + 1));
        error_matrix_free(spine, p);
        ft_fill(spine[p], str, letters, reel);
        *reel += letters;
        p++;
    }
    spine[p] = NULL;
    return (spine);
}

char *select_env(char **env)
{
    char *pat;
    int match;
    int e;
    int i;
    
    pat = "PATH=";
    match = 0;
    e = -1;
    i = -1;
    while (env[++e])
    {
        while (++i < 5)
        {
            if (pat[i] == env[e][i])
            {
                match += 1;
            }
        }
        if (match == 5)
            return (env[e]);
        match = 0;
        i = -1;
    }
    return (NULL);
}

int main(int argc, char **argv, char **env)
{
    printf("Parámetros %i", argc);
    int a;
    a = -1;
    while (argv[++a])
        printf("argv - %s -->\n", argv[a]);
    // ./a.out grep

    //char *chain = "hola holas hola hola ";
    //char *chain = " hola mundo como esta hoy ";
    //char *chain = "hola lolo";
    //char *chain = "hola holas hola hola ";
    
    //char *cmd = argv[1];
    //char sl = '/';
    char *chain = select_env(env);
    int c = ':';
    size_t reel = 5;
    char **arr = split_reel(chain, c, &reel);
    //char **arr = split_reel(chain, c, (size_t *)5); No admite casting
    int row = 0;
    while (arr[row] != NULL)
    {
        printf("Matriz %i \n", row);
        printf("\n %s \n", arr[row]);
        row++;
    }
    /** FREE MATRIX */
    while (row-- > 0)
    {
        if (arr[row])
        {
            free(arr[row]);
            arr[row] = NULL;
        }
    }
    if (arr)
    {
        free(arr);
        arr = NULL;
    }
    return (0);
}