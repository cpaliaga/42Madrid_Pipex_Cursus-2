/* SWAP_CHAR.C */
#include <stdio.h>

// Esta función localiza un carácter en un string y lo reemplaza por otro. 
// Modifica el string original y Retorna void en caso de cadena nula. 
void swap_char(char *str, int *i, char old, char new)
{
    if (str == NULL)
        return;
    while (str[*i] != '\0')
    {
        if (str[*i] == old)
            str[*i] = new;
        *i += 1;
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
        // La comilla de apertura tiene un ESPACIO ANTES. Puede ser comilla de cierre.
        // He tenido problemas de conteo con la expresión: str[i] == 39 && str[i - 1] == 32
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

void find_quote(int *pos, int *p, char i)
{
    pos[*p] = i;
    *p += 1;
}
// ARRAY CON LAS POSICIONES DE LAS COMILLAS
int *quote_position(char *str, int type)
{
    int i;
    int *quotes;
    int pos[32];
    int p;

    p = 0;
    quotes = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == type && i == 0)
            find_quote(pos, &p, i);
        if (str[i] == 32 && str[i + 1] == type)
            find_quote(pos, &p, i);
        if (str[i] == type && str[i + 1] == 32)
            find_quote(pos, &p, i);
        if (str[i] == type && i == (int)ft_strlen(str)-1)
            find_quote(pos, &p, i);
        i++;
    }
    *quotes = *pos;
    return (quotes);
}
// Las comillas simpre han de tener una apertura y un cierre. Por lo que van por pares. 
// El resto de dividir el número total de comillas por 2 será 0.

void quotes_swap_char(char *str, char old, char new)
{
    //int i;
    int quotes[2];
    int len;

    quotes[0] = count_quotes(str, 39);
    quotes[1] = count_quotes(str, 34);
    len = ft_strlen(str);

    //while (str[i] != '\0')
    //{
        //if (str[i] == old)
            //str[i] = new;
        //i++;
    //}


    if (quotes[0]%2 != 0)
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
    
    printf("%i\n", quote_position(str0, 39)[0]);
    printf("%i\n", quote_position(str0, 39)[1]);

    char str1[] = "Hola mundo 'hi lolo'";
    quotes_swap_char(str1, ' ', '_');
    printf("%s\n", str1);

    return (0);
}

// gcc -Wall -Wextra -Werror swap_char.c -o swap_char && ./swap_char
