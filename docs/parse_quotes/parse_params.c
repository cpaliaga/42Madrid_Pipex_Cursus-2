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
		err_ctl(-1, "Bad malloc");
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

char **parse_params(const char *s)
{
	int		cm;
	int		ix;
	char	*comm;
	char	**argv;
	char	**q_argv;

	ix = 0;
	comm = set_command(s, &ix);


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

int main(int argc, char **argv)

{
    if (argc != 2)
    {
        printf("Usage: %s <string>\n", argv[0]);
        return (1);
    }
    char **params = parse_params(argv[1]);
    int i = 0;
    while (params[i] != NULL)
    {
        printf("params[%d] = %s\n", i, params[i]);
        i++;
    }
    return (0);
}

// gcc -Wall -Wextra -Werror parse_params.c -o parse_params
// ./parse_params "ls -l 'hello world' -a"
