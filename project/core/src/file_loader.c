#include "file_loader.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    char filename[100];
    FILE *fp;

    // Check if filename is provided
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open file for reading
    fp = fopen(argv[1], "r");

    // Check if file exists
    if (fp == NULL) {
        printf("Error: File does not exist\n");
        return 1;
    }

    // Read contents of file
    while (fgets(filename, sizeof(filename), fp) != NULL) {
        printf("%s", filename);
    }

    // Close file
    fclose(fp);

    return 0;
}
