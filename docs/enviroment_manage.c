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

int main(int argc, char **argv, char **env)
{
    // ./a.out hola mundo sio
    
    printf("Parámetros %i", argc);
    int a;
    a = -1;
    while (argv[++a])
        printf("%s -->\n", argv[a]);

    printf("%s", select_env(env));

    return (0);
}