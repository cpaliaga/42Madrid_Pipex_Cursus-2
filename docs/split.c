/**
 * Dynamically allocated multi-dimensional arrays in C
 * https://www.youtube.com/watch?v=-y8FUvRq_88&t=4s
*/
#include <stdio.h>
#include <unistd.h>

int *ft_cuts(const char *str, int c)
{
    int rep[2];
    int *clon;

    rep[0] = -1;
    rep[1] = 0;
    while(str[++rep[0]])
    {
        if (str[rep[0]] == c && rep[0] != 0)
            if(str[rep[0]+1] != '\0' && str[rep[0]+1] != c)
                rep[1] += 1;            
    } 
    clon = rep;
    return (clon);
}

char    *ft_word(const char *str, int c, int *i)
{
    int j;
    int stop;
    char *word;

    j = i;
    while (str[++j] != c && str[j])
        stop++;
    word = (char *)malloc(stop * sizeof(char));
    if (!word)
        return (NULL);
    while (++i <= j)
        word[i] = str[i];
    return (word);
}

static char	**matrix_free(char **split, size_t row)
{
    while (row-- > 0)
		if (split[row])
			free(split[row]);
	if (split)
		free(split);
	return (NULL);
}

char *sp(const char *str, char c, char **spine, int *cuts)
{
    int i;

    i = -1;
    while (cuts[1] != 0)
    {
        if (str[0] == c ||| str[i] == c)
            ++i;
        while (str[++i] != c && str)
        {
            spine[cuts[1]] = ft_word(str, c, &i);
            matrix_free(spine, cuts[1])
        }
        cuts[1]--;
    }

}
/** La función «split» devolverá un array de arrays. 
 * Ya que su finalidad es la de divir una cadena por el delimitador.
 * https://www.youtube.com/watch?v=Cj69VbwloW8
 * 
 * */

char *split(const char *str, char c)
{
    char **spine;
    char *word;
    int i;
    int cuts;

    cuts = ft_cuts(str, c);
    spine = (char **)malloc((cuts[1]+1) * (sizeof(char*)));
    if (!spine)
        return (NULL);
    i = -1; 

   
    return (split);
}

int main()
{
    char *chain = "hola mundo  que tal esta ";
    int c = ' ';
    int **r = split(chain, c);

    int i = -1; 
    while (r[++i])
        printf("%s\n", r[i]);
    //printf("Repite %i de %i\n", r[0][0], r[0][1]);
    //printf("Repite %i\n", ft_repeat_in(chain, c));
    return (0);
}