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

// posicion los indices en la doble coincidencia de caracter.
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

int quotes_close(const char *s, int *start, int *len)
{
    int start;
    int len;
    
    // restableccer los parámetros y localizar el final de la cadena.
    reset_str_param(s, &start, &len);
    
    printf("RE start %i len %i \n", start, len);
    
    // La función  pair_move_to_macht configura por referencia los parámetros start y len, 
    // que funcionan como el indice inicial y íncide final de la cadena que estamos "parseando".
    // PARSEO DE COMILLAS SIMPLES '\'' ó ascii 39
    
    pair_move_to_macht('\'', s, &start, &len);
    //printf("MA start %i len %i \n", start, len);

    if (start > len) // la posición final no puede ser traspasada por la posición inicial.
            return (-1); // control de errores.

    // Si start es igual a len : significa que 
    // o bien sólo se localizó una coincidencia del caracter y el recorrido se detubo ahí, 
    // ó bien que satart llegó a len sin encontrar ninguna coincidencia.

    if (start == len) // sólo se encontró una comilla simple ó ninguna comilla simple.
            return (-1); // no son ó no hay comillas de cierre.
    
    // Si start es uno menor que len : significa que
    // el carácter se localizó por duplicado pero de manera contigua, 
    // sin otros carácteeres entre ambas coincidencias.

    if ((start + 1) == len) // las coincidencias encontradas son consecutivas.
            return (1); // nos encontramos ante un caso de cadena vacía.
    
    if (s[start] == 39 && s[len] == 39)
    {
        return (0); // comillas de cierre detectadas.
    }
    return (-1); // error por defecto.
}

int main()
{
    printf("Comillas Simples\n");
    /**
    char *c0 = "hola mmundo 'sd' ";
    int q0 = quotes_close(c0);
    printf("Prueba 00 : %i \n", q0);

    char *c1 = " 'c' hola mmundo ";
    int q1 = quotes_close(c1);
    printf("Prueba 01 :%i \n",q1);
    
    char *c2 = "hola '' hola";
    int q2 = quotes_close(c2);
    printf("Prueba 02 :%i \n",q2);
    
    char *c3 = "hola mmundo 'sd ";
    int q3 = quotes_close(c3);
    printf("Prueba 03 :%i \n",q3);
    */
    char *c4 = "hola mmundo sd ";
    int q4 = quotes_close(c4);
    printf("Prueba 04 :%i \n",q4);

    return (0);
}