#include <stdio.h> // printf()
#include <unistd.h> // access(), F_OK, unlink()
#include <stdlib.h> // wait()

int main(int argc, char *argv[])
{
    if (argc != 2)
        return (1);

    // Accessing the file EXISTENCE
    if (access(argv[1], F_OK) == 0) {
        printf("File exists\n");
    } else {
        printf("File does not exist\n");
    }

    // Accessing the file READ
    if (access(argv[1], R_OK) == 0) {
        printf("File can be read\n");
    } else {
        printf("File can't be read\n");
    }

    // Accessing the file WRITE
    if (access(argv[1], W_OK) == 0) {
        printf("File can be write\n");
    } else {
        printf("File can't be write\n");
    }

    // Accessing the file EXECUTE
    if (access(argv[1], X_OK) == 0) {
        printf("File can be executed\n");
    } else {
        printf("File can't be executed\n");
    }
     
    // Unlinking the file
    if (unlink(argv[1]) == 0) {
        printf("File unlinked\n");
    } else {
        printf("Error unlinking file\n");
    }

    // Accessing the file
    if (access(argv[1], F_OK) == 0) {
        printf("File exists\n");
    } else {
        printf("File does not exist\n");
    }
    
    return 0;
}
// echo "hola mundo" > file.txt && chmod 555 file.txt
//  $ gcc command_access.c -o cm && ./cm file.txt