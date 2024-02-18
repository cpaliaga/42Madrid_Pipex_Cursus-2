#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // System calls - family exec 
#include <sys/wait.h>
#include <errno.h>

char *select_env(char **env)
{
    char *pat;
    int match;
    int e;
    int i;
    
    pat = "PATH=";
    match = 0;
    e = -1;
    i = -1;
    while (env[++e])
    {
        while (++i < 5)
        {
            if (pat[i] == env[e][i])
            {
                match += 1;
            }
        }
        if (match == 5)
            return (env[e]);
        match = 0;
        i = -1;
    }
    return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (*(str + a) != '\0')
		a++;
	return (a);
} 

char	*ft_strjoin_slash(const char *s1, const char *s2)
{
	char	*sjoin;
	size_t	size;
	size_t	i;
	size_t	j;

	if (s1 == 0 || s2 == 0)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2) + 2; // +2 Añado slash
	sjoin = (char *)malloc(size * sizeof(char));
	if (sjoin == 0)
		return (0);
	i = -1;
	while (++i < ft_strlen(s1))
	{
		sjoin[i] = s1[i];
	}
    sjoin[i] = '/'; // Le colocamos el slash se va a 26 líneas
    i++;
	j = -1;
	while (++j < ft_strlen(s2))
	{
		sjoin[i + j] = s2[j];
	}
	sjoin[i + j] = '\0';
	return (sjoin);
}

int main(int argc, char **argv, char **env)
{
    // ./a.out hola
    
    printf("Parámetros %i", argc);
    int a;
    a = -1;
    while (argv[++a])
        printf("%s --> ", argv[a]);

    char *ruta = select_env(env);
    char *add = argv[1];
    printf("1 -> %s | 2 -> %s \n", ruta, add);

    printf("Join: %s\n", ft_strjoin_slash(ruta, argv[1]));

    return (0);
}