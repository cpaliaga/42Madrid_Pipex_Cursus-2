/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_reel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:15:54 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/28 18:28:10 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

static char	**error_matrix_free(char **arr, size_t row)
{
	if (!arr[row])
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
	}
	return (NULL);
}

static size_t	ft_cuts(const char *str, int c)
{
	size_t	cut[2];

	cut[0] = 0;
	cut[1] = 0;
	while (str[cut[0]] != '\0')
	{
		if (cut[0] == 0)
			if (str[cut[0]] != c)
				cut[1] += 1;
		if (str[cut[0]] != c)
			if (str[cut[0] - 1] == c)
				cut[1] += 1;
		cut[0]++;
	}
	printf("Longitud %li cortes %li \n", cut[0], cut[1]);
	return (cut[1]);
}

static size_t	ft_reels(const char *str, char c, size_t *reel)
{
	size_t	dim[3];

	dim[0] = 0;
	while (str[dim[0]] != '\0')
		dim[0]++;
	dim[1] = 0;
	dim[2] = *reel;
	while (str[dim[1] + dim[2]] == c)
	{
		if ((dim[1] + dim[2]) < dim[0])
			dim[2]++;
		else
			break ;
	}
	while (str[dim[1] + dim[2]] != c)
	{
		if ((dim[1] + dim[2]) < dim[0])
			dim[1]++;
		else
			break ;
	}
	*reel = dim[2];
	printf("En reel: letras %li desplazamiento %li \n", dim[1], dim[2]);
	return (dim[1]);
}

static void	ft_fill(char *arr, const char *str, size_t letters, size_t *reel)
{
	size_t	l;
	//size_t	clone;

	l = 0;
	//clone = *reel;
	printf("En relleno: desplazamiento %lu \n", *reel);
	while (l < letters && str[*reel + l] != '\0')
	{
		arr[l] = str[*reel + l];
		printf("En relleno: letra %c ", arr[l]);
		l++;
	}
	printf("En relleno: indice %lu \n", l);
	arr[l] = '\0';
	
}

char	**split_reel(const char *str, char c, size_t reel)
{
	char	**spine;
	size_t	letters;
	size_t	cuts;
	size_t	p;

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
		printf("Al final de while: desplazamiento %li \n", reel);
		p++;
	}
	spine[p] = NULL;
	return (spine);
}

int main()
{
	char *str = "  hola  lo_lo  ";
	char **arr = split_reel(str, ' ', 0);
	// *** LEER ***
	printf("LEER\n");
	int i = 0;
	while (arr[i] != NULL)
	{
		int j = 0;
		while (arr[i][j] != '\0')
		{
			printf("%c", arr[i][j]);
			j++;
		}
		printf("- %i\n", j);
		i++;
	}
	printf("Central %i\n", i);
	// *** LIBERAR ***
	while (i-- > 0)
	{
		if (arr[i] != NULL)
		{
			free(arr[i]);
			arr[i] = NULL;
		}
	}
	if (arr)
	{
		free(arr);
		arr = NULL;
	}

	return (0);
}

// gcc -g -Wall -Wextra -Werror split_reel.c -o SP && valgrind --leak-check=yes -s ./SP

// Input: "  hola  lo_lo  "
// Output:
// Longitud 15 cortes 2 
// En reel: letras 4 desplazamiento 2
// En relleno: desplazamiento 2 
// En relleno: letra h En relleno: letra o En relleno: letra l En relleno: letra a En relleno: indice 4 
// Al final de while: desplazamiento 6 
// En reel: letras 5 desplazamiento 8 
// En relleno: desplazamiento 8 
// En relleno: letra l En relleno: letra o En relleno: letra _ En relleno: letra l En relleno: letra o En relleno: indice 5 
// Al final de while: desplazamiento 13 
// LEER
// hola- 4
// lo_lo- 5 
// Central 2

// https://komodor.com/learn/sigsegv-segmentation-faults-signal-11-exit-code-139/
