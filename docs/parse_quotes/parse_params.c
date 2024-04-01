
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

/** 
char *count_quotes(const char *s, int *ix)
{
	int j;
	int count;
	int scount;
	int dcount;


	j = 0;
	count = 0;
	scount = 0;
	dcount = 0;

	while (s[*ix + j] != '\0')
	{
		if (s[*ix + j] == '\'')
		{
			scount++;
			count++;
		}
		if (s[*ix + j] == '\"')
			dcount++;
			count++;

		j++;
	}
	if (count % 2 != 0)
	{
		printf("Error: Quotes are not even\n");
		return (NULL);
	}

}
*/

/**
 * char **parse_params(const char *s)
{
	int		cm;
	int		ix;
	char	*comm;
	char	**argv;
	char	**q_argv;

	ix = 0;
	comm = set_command(s, &ix);
    printf("comm = %s\n", comm);


	q_argv = split_reel(s, '\'', ix);

	start = 0;
	len = 0;
	argv = (char **)malloc(sizeof(char *) * (ft_strlen(s) + 1));
	if (!argv)
		err_ctl(-1, "Bad malloc");
	while (s[len] != '\0')
	{
		if (s[len] == c)
		{
			argv[i] = ft_substr(s, start, len - start);
			start = len + 1;
			i++;
		}
		len++;
	}
	argv[i] = ft_substr(s, start, len - start);
	argv[i + 1] = NULL;
	return (argv);

} 
*/



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
    /**
    char **params = parse_params(argv[1]);
    int i = 0;
    while (params[i] != NULL)
    {
        printf("params[%d] = %s\n", i, params[i]);
        i++;
    }
    */
    return (0);
}


// COMPILACIÓN      gcc -Wall -Wextra -Werror parse_params.c -o parse_params
// EJECUTAR         ./parse_params "ls -l 'hello world' -a"

// EJECUTAR         ./parse_params "tr ' ' '\n'"
// tengo 4 comillas, patrón aa aa

// EJECUTAR         ./parse_params "awk '{print $1}'"
// tengo 2 comillas patrón aa.

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