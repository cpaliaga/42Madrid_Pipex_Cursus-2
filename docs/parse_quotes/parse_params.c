
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * #include "util_split_reel.c"

char	**split_reel(const char *str, char c, size_t reel);
*/



char *set_command(const char *s, int *ix)
{
	int		cm;
	int		i;
	char	*comm;

	cm = 0;
	while (s[cm] != '\0' && s[cm] != ' ')
		cm++;
	comm = (char *)malloc(sizeof(char) * (cm + 1));
	if (!comm)
		return(NULL);
	i = 0;
	while (i < cm)
	{
		comm[i] = s[i];
		i++;
	}
	comm[i] = '\0';
	*ix = cm;
	return (comm);
}

int main(int argc, char **argv)

{
    if (argc != 2)
    {
        printf("Usage: %s <string>\n", argv[0]);
        return (1);
    }

    int ix = 0;
    char *com = set_command(argv[1], &ix);
    printf("comm = %s , ix = %i \n", com, ix);
    printf("argv[1] = %s\n", argv[1]);
 
    return (0);
}


// COMPILACIÓN      gcc -Wall -Wextra -Werror parse_params.c -o parse_params
// EJECUTAR         ./parse_params "ls -l 'hello world' -a"

// OK         ./parse_params "tr ' ' '\n'"

// OK         ./parse_params "awk '{print $1}'"


//  cat /etc/passwd | awk -F ":" '{print $1}'
// tengo cuatro comillas patrón bb aa.

// EJECUTAR         ./parse_params "awk -F ":" '{print $1}'"
// Recibo Error     awk -F : '{print }'

// EJECUTAR         ./parse_params "awk -F ':' '{print $1}'"
// Recibo           awk -F ':' '{print }'

// EJECUTAR         ./parse_params 'awk -F ":" '{print $1}''
// Recibo Error     Usage: ./parse_params <string>

// EJECUTAR         ./parse_params "awk -F \":\" '{print \$1}'"
// Recibo Exacto    awk -F ":" '{print $1}'

//	El programa «awk» puede admitir «flags» con un parámertro entre comillas dobles,
//	y los programas cortos generalmente se ingresan en la línea de comando
//	encerrado en comila simples para evitar la interpretación del shell.
//	Se pueden realizar programas más largos leer desde un archivo con la opción -f.

// Patrón de comillas todas iguales en número par: "" "" ó '' ''
// Patrón de comillas diferenctes en número par: "" '' ó '' ""

//  https://geekland.eu/uso-del-comando-awk-en-linux-y-unix-con-ejemplos/