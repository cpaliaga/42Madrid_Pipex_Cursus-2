/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_unifile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:40:48 by caliaga-          #+#    #+#             */
/*   Updated: 2024/02/28 17:23:28 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

static char **matrix_free(char **arr, size_t row)
{
    while (row-- > 0)
    {
        if (arr[row])∫
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

char *filepath_generator(const char *argv, char **env)
{

    char **paths;
    int row;
    char *target_path;
 

    paths = split_reel(select_env(env), ':',5);
    row = -1;
    while (paths[++row] != NULL)
    {
        target_path = ft_strjoin_slash(paths[row], argv);
        if (access(target_path, X_OK || F_OK) == 0)
            return (target_path);
        free(target_path);
        target_path = NULL;
    }
    matrix_free(paths, row);
    return (NULL);
}

void err_ctl(int exe)
{   if (exe == -1)
    {
        printf("Número %i ", errno);
        perror(strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int fd_openfile(char *url, char opt){
    int fd;

    if (opt == 'R')
	{
		fd = open(url, O_RDONLY, 0777);
		err_ctl(fd);
	}
	else
	{
		fd = open(url, O_WRONLY, 0777);
		err_ctl(fd);
	}
    return (fd);
}

void	exec(char *argv, char **env)
{
	char	**s_argv;
	int 	s;
	char	*path;
	int		exe;

	s = 0;
	s_argv = split_reel(argv, ' ', 0);
	while (s_argv[s] != NULL)
        s++;
	path = filepath_generator(s_argv[0], env);
	exe = execve(path, s_argv, env);
	matrix_free(s_argv, s);
	err_ctl(exe);
}

void	child(int *fd_pipe, char **argv, char **env)
{
	int		fd_in;

	fd_in = fd_openfile(argv[1], 'R');
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[0]);
	exec(argv[2], env);
}

void	parent(int *fd_pipe, char **argv, char **env)
{
	int		fd_out;

	fd_out = fd_openfile(argv[4], 'W');
	dup2(fd_out, STDOUT_FILENO);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[1]);
	exec(argv[3], env);
}

int	main(int argc, char **argv, char **env )
{
	int		fd_pipe[2];
	pid_t	pid;

	if (argc != 5)
		err_ctl(-1);
	if (pipe(fd_pipe) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		child(fd_pipe, argv, env);
	parent(fd_pipe, argv, env);
	exit(0);
}

/* int argc  nos informa del número de argumentos que va a tener 
 * nuestro programa ejecutable, por defecto este será ./a.out*/

/* El número de argumentos nunca es 0 ya que por defecto cuenta el 
 * nombre del programa como primer argumento.*/
/* argv es donde se guardan los valores de lor parametros introducidos 
 * en la ejecución.*/
/* environ permite acceder al contenido del entorno desde shell con el 
 * comando end; no se suele usar el 99% de las veces */
//int	main(int argc, char **argv, char **env)
//{ 
	/* Para no tener problemas de compilacción por no estar declaradas 
	 * las variables usamos (void) para declararlas e inicializarlas. */
//	(void) argc;
//	(void) argv;
//	(void) enviro;

	/* Ahora los parámeros que usemos a continuación de la intrucción 
	 * para ejecutar se guardarán en argv y podremos usarlos dentro de 
	 * nuestro programa*/
	
	//* Complilas  gcc -Wall -Wextra -Werror main_arg.c */

//	./a.out infile "ls -l" "wc -l" outfile
//	./a.out "grep a1" "wc -w" outfile

	//* Por ejemplo: ./a.out hola lola pin pan
	// * devolverá 5 elementos*/
	//printf ("Numero de argumentos: %d \n", argc);
	//printf ("Primer  argumento: %s \n", argv[0]);
	//printf ("Segudo argumento: %s \n", argv[1]);
	//printf ("Tercer argumento: %s \n", argv[2]);
//	printf ("Cuarto argumento: %s \n", argv[3]);
//	printf ("Quinto argumento: %s \n", argv[4]);
//	return(0);
//}