# include <stdio.h>
# include <unistd.h>

int ft_isSquote(int c)
{
	if (c >= 39)
		return (1);
	return (0);
}

int ft_isDquote(int c)
{
	if (c >= 34)
		return (1);
	return (0);
}

// esta función restablece el puntero de inicio y recalcula la longitud de una cadena.
void reset_str_param(const char *s, int *start, int *len)
{
    if (!s || !start || !len)
        return ;
    *start = 0;
    *len = 0;
    while (s[*len] != '\0')
        *len += 1;
    // int *mid    *mid = len / 2;
}

// La función  pair_move_to_macht() configura por referencia los parámetros start y len, 
// que funcionan como el indice inicial y íncide final de la cadena que estamos "parseando".
// Posicion los indices en la doble coincidencia de caracter.
void pair_move_to_macht(char c, const char *s, int *start, int *len)
{
    // localizar la primera pareja del caracter "int c".
    // devolver mmodificados por parámetros "start" y "len" que hemos pasado por referencia.
    // desplazamos desde el inicio hasta coincidencia ó hasta final.
    while (s[*start] != c) // aumentar hasta la coincidencia.
    {
        if (*start < *len) // si el inicio es menor que el final.
        {
            *start += 1;
            printf("*start = %i \n", *start);
        }             
        else // cuando el inicio sea igual que el final rompemos el bucle.
            break ;
    }
    
    //printf("M-t-M start %i y len %i \n", *start, *len);

    // desplazamos desde el final hasta coincidencia ó hasta el inicio.
    while (s[*len] != c) // disminuir hasta la coincidencia.
    {
        if (*start < *len)
            *len -= 1;  // si aquí aumentásemos len tendríamos un bus error.
        else
            break ;
    }
}

int check_single(const char *s, int *start, int *len)
{
    if (*start > *len) // la posición final no puede ser traspasada por la posición inicial.
        return (-1); // control de errores.

    // Si start es igual a len : significa que 
    // o bien sólo se localizó una coincidencia del caracter y el recorrido se detubo ahí, 
    // ó bien que satart llegó a len sin encontrar ninguna coincidencia.

    if (*start == *len) // sólo se encontró una comilla simple ó ninguna comilla simple.
        return (-1); // no son ó no hay comillas de cierre.
    
    // Si start es uno menor que len : significa que
    // el carácter se localizó por duplicado pero de manera contigua, 
    // sin otros carácteeres entre ambas coincidencias.

    if ((*start + 1) == *len) // las coincidencias encontradas son consecutivas.
        return (1); // nos encontramos ante un caso de cadena vacía.
    
    if (s[*start] == 39 && s[*len] == 39)
        return (0); // comillas de cierre detectadas.
    return (-1); // error por defecto.
}

int check_doble(const char *s, int *start, int *len)
{
    if (*start > *len) // la posición final no puede ser traspasada por la posición inicial.
        return (-1); // control de errores.

    if (*start == *len) // sólo se encontró una comilla simple ó ninguna comilla simple.
        return (-1); // no son ó no hay comillas de cierre.

    if ((*start + 1) == *len) // las coincidencias encontradas son consecutivas.
        return (1); // nos encontramos ante un caso de cadena vacía.
    
    if (s[*start] == 34 && s[*len] == 34)
        return (0); // comillas de cierre detectadas.
    return (-1); // error por defecto.
}

int quotes_close(const char *s, int *start, int *len)
{
    // PARSEO DE COMILLAS SIMPLES '\'' ó ascii 39
    // restableccer los parámetros y localizar el final de la cadena.
    reset_str_param(s, start, len);
    pair_move_to_macht('\'', s, start, len);
    check_single(s, start, len);

    // PARSEO DE COMILLAS DOBLES '\"' ó ascii 34
    // restableccer los parámetros y localizar el final de la cadena.
    reset_str_param(s, start, len);
    pair_move_to_macht('\'', s, start, len);
    check_single(s, start, len);   

    return (-1); // error por defecto.
}

int main()
{
    printf("Comillas Simples\n");
    
    int start00, len00;
    char *c00 = "hola mmundo 'sd' ";
    int q00 = quotes_close(c00, &start00, &len00);
    printf("Prueba 00 : %i \n", q00);

    int start01, len01;
    char *c01 = " 'c' hola mmundo ";
    int q01 = quotes_close(c01, &start01, &len01);
    printf("Prueba 01 :%i \n",q01);
    
    int start02, len02;
    char *c02 = "hola '' hola";
    int q02 = quotes_close(c02, &start02, &len02);
    printf("Prueba 02 :%i \n",q02);
    
    int start03, len03;
    char *c03 = "hola mmundo 'sd ";
    int q03 = quotes_close(c03, &start03, &len03);
    printf("Prueba 03 :%i \n",q03);
    
    int start04, len04;
    char *c04 = "hola mmundo sd ";
    int q04 = quotes_close(c04, &start04, &len04);
    printf("Prueba 04 :%i \n",q04);

    printf("Comillas Dobles\n");
    int start05, len05;
    char *c05 = "hola \"mm\"undo sd ";
    int q05 = quotes_close(c05, &start05, &len05);
    printf("Prueba 05 :%i \n",q05);

    return (0);
}

// gcc -Wall -Wextra -Werror pair_quotes.c -o pair_quotes
// ./pair_quotes