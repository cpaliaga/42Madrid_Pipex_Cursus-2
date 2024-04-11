/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:13:56 by caliaga-          #+#    #+#             */
/*   Updated: 2023/10/11 14:46:34 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>

void	ft_pchar(int c, int *wr)
{
	int	wr_int;

	wr_int = 0;
	wr_int += write(1, &c, 1);
	if (wr_int == -1)
		return;
	*wr = wr_int;
}

void	ft_pnumber(int n, int *wr)
{
	if (n == -2147483648)
		*wr += write(1, "-2147483648", 11);
	else if (n == 0)
		*wr += write(1, "0", 1);
	else
	{
		if (n < 0)
		{
			*wr += write(1, "-", 1);
			ft_pnumber(n = n * -1, wr);
		}
		else
		{
			if (n > 9)
				ft_pnumber(n / 10, wr);
			ft_pchar(n % 10 + '0', wr);
		}
	}
}

int main (void)
{
	
	//int try = '';
	// int try = '%';
	// int try_5 = 13;
	// int try_4 = '\n';
	// int try_3 = 97; 
	// int try_2 = 164;
	// int try_1 = '0';
	
	// int wr = 0;
	// ft_pchar(try, &wr);
	// printf(" - ");
	// int pwr = printf("%c", try);
	// printf(" == %d %d\n", wr, pwr);	
	ft_printf("%%%%%%");

	return (0);
}

/**26:     TEST(2, print(" %c ", '0'));
27:     TEST(3, print(" %c", '0' - 256));
29:     TEST(5, print(" %c %c %c ", '0', 0, '1'));
30:     TEST(6, print(" %c %c %c ", ' ', ' ', ' '));
31:     TEST(7, print(" %c %c %c ", '1', '2', '3'));
32:     TEST(8, print(" %c %c %c ", '2', '1', 0));
33:     TEST(9, print(" %c %c %c ", 0, '1', '2'));

Error in test 2: ft_printf(" %%"): returned: 1, but expected: 2
Error in test 4: ft_printf("%%%%%%"): returned: 1, but expected: 3
Error in test 5: ft_printf("%%%c", 'x'): returned: 1, but expected: 2
For c format:
Error in test 2: ft_printf(" %c", 'x'): returned: 1, but expected: 2
Error in test 4: ft_printf("%c%c%c", 'a', '\t', 'b'): returned: 1, but expected: 3
Error in test 5: ft_printf("%cc%cc%c", 'a', '\t', 'b'): returned: 1, but expected: 5
Error in test 6: ft_printf("%cs%cs%c", 'c', 'b', 'a'): returned: 1, but expected: 5
For d format:
Error in test 2: ft_printf("%d", -10): returned: 1, but expected: 3
Error in test 3: ft_printf("%d", -200000): returned: 1, but expected: 7
Error in test 4: ft_printf("%d", -6000023): returned: 1, but expected: 8
Error in test 5: ft_printf("%d", 10): returned: 1, but expected: 2
Error in test 6: ft_printf("%d", 10000): returned: 1, but expected: 5
Error in test 7: ft_printf("%d", 100023): returned: 1, but expected: 6
Error in test 8: ft_printf("%d", INT_MAX): returned: 1, but expected: 10
Error in test 10: ft_printf("dgs%dxx", 10): returned: 3, but expected: 7
Error in test 11: ft_printf("%d%dd%d", 1, 2, -3): returned: 1, but expected: 5

*/