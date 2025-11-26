#include <stdio.h>
#include <stdlib.h>

char* readFile(const char* filePath, int* error)
{
    int e = 0;
    int n; //more error handling
    //e = 1 if opening failed
    //e = 2 if reading failed
    //e = 3 if closing failed
    //e = 4 if memory allocation failed

    FILE* file = fopen(filePath, "rb");
    if (file == NULL)
    {
        printf("Could not open file: %s\n", filePath);
        e = 1;
        return NULL;
    }

    //count size of file
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* output = malloc(size + 1); //+1 is used for \0 at the end.

    if (!output)
    {
        printf("Could not allocate memory.\n");
        e = 4;
        return NULL;
    }
    

    n = fread(output, 1, size, file);
    output[size] = '\0';

    if (n != size)
    {
        printf("Could not read file: %s\n", filePath);
        e = 2;
        return NULL;
    }
    
    n = fclose(file);
    if (n == EOF)
    {
        printf("Could not close file: %s\n", filePath);
        e = 3;
        return NULL;
    }

    *error = e;
    return output;
}