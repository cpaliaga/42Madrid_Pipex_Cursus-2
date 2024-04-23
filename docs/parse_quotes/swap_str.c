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
        while (str[j] != '\0')
        {
            if (str[j] == old)
                str[j] = new;
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
int count_quotes(char *str, int type)
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
        i++;
    }
   return (quotes); 
}

void quotes_swap_char(char *str, char old, char new)
{
    //int i;
    int quotes[2];
    int len;

    quotes[0] = count_quotes(str, 39);
    quotes[1] = count_quotes(str, 34);
    len = ft_strlen(str);

    if (quotes[0] % 2 != 0)
    {
        printf("Las comillas están abiertas\n");
    }
        printf("Las comillas están cerradas\n");
    printf("Len: %d, old %c new %c \n", len, old, new);
    printf("\nQuotes: simples %d - doubles %d \n", quotes[0], quotes[1]);
}

int main()
{
    int i = 0;
    char str[] = "Hola mundo 'hi lolo'";
    swap_char(str, &i, ' ', '_');
    printf("%s\n", str);

    char str0[] = "Hola 'lolo'";
    printf("%i\n", count_quotes(str0, 39));
    
    //printf("%i\n", quote_position(str0, 39)[0]);
    //printf("%i\n", quote_position(str0, 39)[1]);

    char str1[] = "Hola mundo 'hi lolo'";
    quotes_swap_char(str1, ' ', '_');
    printf("%s\n", str1);

    return (0);
}