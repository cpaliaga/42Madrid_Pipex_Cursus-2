/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork-work.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:09:34 by caliaga-          #+#    #+#             */
/*   Updated: 2023/12/19 18:11:57 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main()
{
	/* El tipo de datos "pid_t" es un tipo de datos que se empllea en la 
	 * identificación de procesos.
	 * Se usa junto con las funciones getpid() y getppid() que retornan 
	 * el ID de proceso actual y de su proceso padre, respectivamennte. 
	 * Las librerías a incluir son "unistd.h" y/o "sys/types.h" */
	pid_t pid;
	
	/* fork() creates a child process that differs from the parent process 
	 * only in its PID and PPID, and in the fact that resource 
	 * utilizations are set to 0. File locks and pending signals
	 * are not inherited.*/
	pid = fork();
	if (pid == -1)
	{
		printf("No se ha creado el hijo. %i \n", pid);
		return (0);
	}
	if (pid == 0)
	{
		printf("Soy el hijo %i mi ID es %i y el de mi padre %i \n", pid, getpid(), getppid());
	}
	else
	{
		printf("Soy el padre %i mi ID es %i no tengo padre %i \n", pid, getpid(), getppid());
		sleep(2);
	}
	return (0);
}
