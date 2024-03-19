/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror-n-strerror.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:42:16 by caliaga-          #+#    #+#             */
/*   Updated: 2024/03/19 13:38:26 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** Handling Errors in C/Unix (perror, strerror, errno) 
 * https://www.youtube.com/watch?v=IZiUT-ipnj0
 * Error Handling | C Programming Tutorial 
 * https://www.youtube.com/watch?v=OOuZLI5ingc
 * Getting exit status code in C 
 * https://www.youtube.com/watch?v=DiNmwwQWl0g
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h> // Variable global "errno" y "const char *sys_errlist[]""
/** Cuanddo las funciones execve()) y access() no tienenn éxito (0),
 * retornan un error genérico en (-1). Para conocer el error específfico 
 * la variable global "erno" (que es un "int") se configura automáticamente.
 * La función strerror() nos ofrece el texto del errror que se 
 * corresponde con su número "errno".
 * Por otro lado la función perror() nos permite informar por pantalla 
 * del error.
*/
int main()
{
	int i;

	i = 0;
	while(i<=106)
	{
		printf("%i - %s\n", i, strerror(i));
		write(2, &i, 1);
		//perror(sys_errlist[i]);
		//perror(strerror(i));
		i++;
	}
	printf("%i", 108*17);
	//const char *s = strerror(5);
	//printf("%s", s);	perror(sys_errlistt[i]);
	return(0);
}
