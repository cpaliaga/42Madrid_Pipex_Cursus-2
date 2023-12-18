/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror-n-strerror.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:42:16 by caliaga-          #+#    #+#             */
/*   Updated: 2023/12/18 18:39:09 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h> // const char *sys_errlist[]
int main()
{
	int i;

	i = 0;
	while(i<=106)
	{
		printf("%i - %s\n", i, strerror(i));
		perror(sys_errlist[i]);
		perror(strerror(i));
		i++;
	}
	printf("%i", 108*17);
	//const char *s = strerror(5);
	//printf("%s", s);	perror(sys_errlistt[i]);
	return(0);
}
