#include <stdio.h>

char	*filepath_generator(const char *argv, char **env)
{
	char	**paths;
	int		row;
	char	*target_path;
	int		check;

    int i;
    i = 0;
    while (argv)
        i++;
   
	check = access(argv, X_OK || F_OK);
	if (check == 0)
    {
        target_path = (char *)malloc(sizeof(char) * i)+1;
        target_path = argv;
        return (target_path);
    }

  
  
	return (NULL);
}

int main(int argc, char **argv, char **env)
{
    printf("");
    return (0);
}