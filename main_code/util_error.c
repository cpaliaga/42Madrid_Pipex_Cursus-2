#include "pipex.h"

void err_ctl(int exe)
{   if (exe == -1)
    {
        printf("Número %i ", errno);
        perror(strerror(errno));
        exit(EXIT_FAILURE);
    }
}

static char **matrix_free(char **arr, size_t row)
{
    while (row-- > 0)
    {
        if (arr[row])
        {
            free(arr[row]);
            arr[row] = NULL;
        }
    }
    if (arr)
    {
        free(arr);
        arr = NULL;
    }
    return (NULL);
}

static char **error_matrix_free(char **arr, size_t row) 
{
    if (!arr[row])
    {
        while (row-- > 0)
            if (arr[row])
            {
                free(arr[row]);
                arr[row] = NULL;
            }
        if (arr)
        {
            free(arr);
            arr = NULL;
        }
    }
	return (NULL);
}