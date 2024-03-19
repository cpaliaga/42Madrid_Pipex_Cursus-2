#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <stdint.h>

int	fd_openfile(char *url, char opt)
{
	int	fd;

	if (opt == 'R')
		fd = open(url, O_RDONLY, 0777);
	else
		fd = open(url, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("Error: ");
		return (1); // EXIT_FAILURE
	}
	return (fd);
}

size_t fd_bytesToRead(int fd)
{
 
    size_t bytesRead;
    char buffer[32];
    int rd;

    rd = 1;
    bytesRead = 0;
    // Cuando el read retorne 0, significa que ya no hay nada que leer 
    // y que hemos llegado al final del fichero.
    while (rd != 0)
    {
        rd = read(fd, buffer, sizeof(buffer));
        bytesRead = bytesRead + rd;
     
    }
    return (bytesRead);
}

char *fd_read(int fd ,size_t bRead)
{
    int fd_read;
    char *buffer;

    buffer = (char *)malloc(bRead);
	if (!buffer)
		return (NULL);
    fd_read = read(fd, buffer, bRead);
    if (fd_read == -1)
    {
        perror("Error: ");
        return(NULL);
    }
    return (buffer);
}

char *swap(char *buffer, size_t bRead)
{
    char *newBuffer;
    newBuffer = (char *)malloc(bRead);
    if (!newBuffer)
        return (NULL);
    for (size_t i = 0; i < bRead; i++)
    {
        if (buffer[i] == ',')
            newBuffer[i] = '\t';
        else
            newBuffer[i] = buffer[i];
    }
    free(buffer);
    return (newBuffer);
}

int main(int argc, char **argv)
{
    // gcc csv-to-tsv.c -o csv-tsv
    // ./csv-tsv smile.csv smile.tsv
    if (argc != 3)
        return (1); // EXIT_FAILURE
    int fd_c = fd_openfile(argv[1], 'R');
    size_t bRead = fd_bytesToRead(fd_c);
    // Llegados a este paso ya tenemos el tamaño del fichero en bytes.
    // Tendremos que volver a abrir el fichero, ya que el puntero de lectura está al final del fichero.
    // Y lo necesitamos al principio para leer el contenido.
    int fd = fd_openfile(argv[1], 'R');
    char *buffer = fd_read(fd, bRead);
    char *newBuffer = swap(buffer, bRead);
    printf("Buffer: %s\n", newBuffer);
    // Llegados a este paso ya tenemos el buffer alojado en memoria dinámica 
    // con el contenido del fichero para poder trabajar con el mismo.
    // En un formato Comma Sepatate Values (CSV) los valore s de la tabla están separados por comas.
    // Para convertirlo a un formato Tab Separated Values (TSV) 
    // simplemente tenemos que reemplazar las comas por tabuladores.
    int fd_wr = fd_openfile(argv[2], 'W');
    int wr = write(fd_wr, newBuffer, bRead);
    if (wr == -1)
    {
        perror("Error: ");
        return (1); // EXIT_FAILURE
    }
    free(newBuffer);   
    return (0);
}