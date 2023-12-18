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

/* int argc  nos informa del número de argumentos que va a tener 
 * nuestro programa ejecutable, por defecto este será ./a.out*/

/* El número de argumentos nunca es 0 ya que por defecto cuenta el 
 * nombre del programa como primer argumento.*/
/* argv es donde se guardan los valores de lor parametros introducidos 
 * en la ejecución.*/
/* environ permite acceder al contenido del entorno desde shell con el 
 * comando end; no se suele usar el 99% de las veces */
int	main(int argc, char **argv, char **enviro)
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
