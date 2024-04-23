#include <stdio.h>

void matrix_swap_char(char **str, char old, char new)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (str == NULL)
        return;
    while (str[i] != NULL)
    {
        while (str[i][j] != '\0')
        {
            if (str[i][j] == old)
                str[i][j] = new;
            j += 1;
        }
        i += 1;
    }
}

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (*(str + a) != '\0')
		a++;
	return (a);
}

// CONTAR LAS COMILLAS DE UNA CADENA. type 39 o 34
int space_betwen_quotes(char *str, int type)
{
    int i;
    int quotes;

    quotes = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == type && i == 0) // La comilla de apertura es LA PRIMERA.
            quotes += 1;
        if (str[i] == 32 && str[i + 1] == type)
            quotes += 1;
        if (str[i] == type && str[i + 1] == 32) // La comilla de cierre tiene un ESPACIO DESPUES.
            quotes += 1;
        if (str[i] == type && i == (int)ft_strlen(str)-1) // La comilla de cierre es LA ULTIMA.
            quotes += 1;
        if (str[i + 1] != type)
            if (quotes != 0 && quotes % 2 != 0)
                if (str[i] == 32)
                    str[i] = 95;
        if (str[i] == type)
            str[i] = 32;
        i++;
    }
   return (quotes); 
}

int main()
{
    //char str[] = "Hola mundo 'hi lolo'";
    //matrix_swap_char(str,  ' ', '_');
    //printf("%s\n", str);

    //char str0[] = "Hola 'lolo'";
    //printf("%i\n", count_quotes(str0, 39));
    
    //printf("%i\n", quote_position(str0, 39)[0]);
    //printf("%i\n", quote_position(str0, 39)[1]);

    char str1[] = "Hola 'hi lolo' segundo 'par de'";
    printf("%i\n", space_betwen_quotes(str1, 39));
    printf("%s\n", str1);

    return (0);
}
// "awk '{count++} END {print count}'"
// gcc -Wall -Wextra -Werror swap_str.c -o Swap-Str && ./Swap-Str