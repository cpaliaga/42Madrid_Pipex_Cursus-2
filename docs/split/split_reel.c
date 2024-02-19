/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_reel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:54:11 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/19 18:34:22 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Dynamically allocated multi-dimensional arrays in C
 * https://www.youtube.com/watch?v=-y8FUvRq_88&t=4s
*/
#include <stdio.h> // printf()
#include <stdlib.h> // malloc(), free()
#include <unistd.h>
#include <errno.h>

/** matrix_free(char **array, size_t row) libera la memoria del array 
 * de 2 dimensiones (matriz ó array de array's) que hemos creado ó 
 * intentado crear mediante la alocación dinámica de memoria. 
 * Recibe dos parámetros: 
 * la matriz y el número del array dentro de la matriz. */

static char **matrix_free(char **arr, size_t row)
{
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
    return (NULL);
}

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

char **split_reel(const char *str, char c, size_t reel)
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
        letters = ft_reels(str, c, &reel);
        spine[p] = (char *)malloc(sizeof(char) * (letters + 1));
        error_matrix_free(spine, p);
        ft_fill(spine[p], str, letters, &reel);
        reel += letters;
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

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (*(str + a) != '\0')
		a++;
	return (a);
} 

char	*ft_strjoin_slash(const char *s1, const char *s2)
{
	char	*sjoin;
	size_t	size;
	size_t	i;
	size_t	j;

	if (s1 == 0 || s2 == 0)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2) + 2; // Añado un espacio extra para el slash
	sjoin = (char *)malloc(size * sizeof(char));
	if (sjoin == 0)
		return (0);
	i = -1;
	while (++i < ft_strlen(s1))
        sjoin[i] = s1[i];
    sjoin[i] = '/'; // Le colocamos el slash
    i++;
	j = -1;
	while (++j < ft_strlen(s2))
        sjoin[i + j] = s2[j];
	sjoin[i + j] = '\0';
	return (sjoin);
}
/**/
char *filepath_generator(char **argv, char **env)
{
    char **arguments;
    int a_row;
    char **paths;
    int row;
    char *target_path;
 
    arguments = split_reel(argv[1], ' ', 0);
    a_row = 0;
    while (arguments[a_row] != NULL)
        a_row++;
    paths = split_reel(select_env(env), ':',5);
    row = -1;
    while (paths[++row] != NULL)
    {
        target_path = ft_strjoin_slash(paths[row], arguments[0]);
        if (access(target_path, X_OK || F_OK) == 0)
            return (target_path);
        free(target_path);
        target_path = NULL;
    }
    matrix_free(arguments, a_row);
    matrix_free(paths, row);
    return (NULL);
}

int main(int argc, char **argv, char **env)
{
    printf("Parámetros %i\n", argc);    
   
    char *t = filepath_generator(argv, env);
    printf("Paht: %s\n", t);

    return (0);
}