/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:40:48 by caliaga-          #+#    #+#             */
/*   Updated: 2023/12/18 14:59:21 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(0);
	}
}

void	child(int *fd, char **argv, char **env)
{
	int		fd;

	fd = open_file(argv[1], 0);
	dup2(fd, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	exec(argv[2], env);
}

void	parent(int *fd, char **argv, char **env)
{
	int		fd;

	fd = open_file(argv[4], 1);
	dup2(fd, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	exec(argv[3], env);
}

int	main(int argc, char **argv, char **env )
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		exit_handler(1);
	if (pipe(fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		child(fd, argv, env);
	parent(fd, argv, env);
}


/* int argc  nos informa del número de argumentos que va a tener 
 * nuestro programa ejecutable, por defecto este será ./a.out*/

/* El número de argumentos nunca es 0 ya que por defecto cuenta el 
 * nombre del programa como primer argumento.*/
/* argv es donde se guardan los valores de lor parametros introducidos 
 * en la ejecución.*/
/* environ permite acceder al contenido del entorno desde shell con el 
 * comando end; no se suele usar el 99% de las veces */
int	main(int argc, char **argv, char **env)
{ 
	/* Para no tener problemas de compilacción por no estar declaradas 
	 * las variables usamos (void) para declararlas e inicializarlas. */
	(void) argc;
	(void) argv;
	(void) enviro;

	/* Ahora los parámeros que usemos a continuación de la intrucción 
	 * para ejecutar se guardarán en argv y podremos usarlos dentro de 
	 * nuestro programa*/
	
	/* Complilas  gcc -Wall -Wextra -Werror main_arg.c */

	/* Por ejemplo: ./a.out hola lola pin pan
	 * devolverá 5 elementos*/
	printf ("Numero de argumentos: %d \n", argc);
	printf ("Primer  argumento: %s \n", argv[0]);
	printf ("Segudo argumento: %s \n", argv[1]);
	printf ("Tercer argumento: %s \n", argv[2]);
	printf ("Cuarto argumento: %s \n", argv[3]);
	printf ("Quinto argumento: %s \n", argv[4]);
	return(0);
}
