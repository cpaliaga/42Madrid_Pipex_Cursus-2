#include <stdio.h> // printf()
#include <unistd.h> // access(), F_OK, unlink()
#include <stdlib.h> // wait()

int main()
{
    // Creating a file
    FILE* file = fopen("file.txt", "w");
    if (file == NULL) {
        printf("Error creating file\n");
        return 1;
    }
    printf("File created\n");

    // Closing the file
    fclose(file);
    printf("File closed\n");

    // Accessing the file EXISTENCE
    if (access("file.txt", F_OK) == 0) {
        printf("File exists\n");
    } else {
        printf("File does not exist\n");
    }

    // Accessing the file READ
    if (access("file.txt", R_OK) == 0) {
        printf("File can be read\n");
    } else {
        printf("File can't be read\n");
    }

    // Accessing the file WRITE
    if (access("file.txt", W_OK) == 0) {
        printf("File can be write\n");
    } else {
        printf("File can't be write\n");
    }

    // Accessing the file EXECUTE
    if (access("file.txt", X_OK) == 0) {
        printf("File can be executed\n");
    } else {
        printf("File can't be executed\n");
    }

    // Unlinking the file
    if (unlink("file.txt") == 0) {
        printf("File unlinked\n");
    } else {
        printf("Error unlinking file\n");
    }

    // Accessing the file
    if (access("file.txt", F_OK) == 0) {
        printf("File exists\n");
    } else {
        printf("File does not exist\n");
    }

    return 0;
}   
//  INVESTIGATIONS:

//  https://bs2manuals.ts.fujitsu.com/psCRTEV111en/c-library-functions-for-posix-applications-reference-manual-21430-1/functions-and-variables-in-alphabetical-order-c-library-functions-for-posix-applications-4-0b03-125/u-c-library-functions-for-posix-applications-4-0b03-821/unlink-unlinkat-remove-link-c-library-functions-for-posix-applications-4-0b03-677

//  https://pubs.opengroup.org/onlinepubs/009695299/functions/access.html
//  https://pubs.opengroup.org/onlinepubs/009695399/functions/unlink.html

//  https://www.gnu.org/software/libc/manual/html_node/Accessing-Directories.html
//  https://www.gnu.org/software/libc/manual/html_node/Testing-File-Access.html
//  https://www.gnu.org/software/libc/manual/html_node/Hard-Links.html
//  https://www.gnu.org/software/libc/manual/html_node/Symbolic-Links.html
//  https://www.gnu.org/software/libc/manual/html_node/Deleting-Files.html
//  https://www.gnu.org/software/libc/manual/html_node/Low_002dlevel-Directory-Access.html
//
//  gcc access_unlink.c -o au && ./au
