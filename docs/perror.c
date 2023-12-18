/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:42:16 by caliaga-          #+#    #+#             */
/*   Updated: 2023/12/18 16:18:06 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int main()
{
	int i;

	i = 0;
	while(i<=100)
	{
		printf("%i - %s\n", i, strerror(i));
		i++;
	}
	//const char *s = strerror(5);
	//printf("%s", s);	perror("Input/output error");
	return(0);
}
