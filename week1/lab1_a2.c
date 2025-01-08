#include <stdio.h>

void paginationN(char *filename, int size)
{
    char buffer[1024];
    int counter = 0;
    FILE *file1 = fopen(filename, "r");
    char c = fgetc(file1), t;
    while (c != EOF)
    {
        printf("%c", c);
        if (c == '\n')
        {
            counter++;
            if (counter % 5 == 0)
            {
                counter = 1;
                printf("\n=======Pagination at every %d lines===========\n", size);
                scanf("%c", &t);
            }
        }
        c = fgetc(file1);
    }
    fclose(file1);
}

void main()
{
    char filename[128];
    int size;
    printf("\nEnter the line for pagination: ");
    scanf("%d", &size);
    printf("\nEnter the filename: ");
    scanf("%s", filename);
    paginationN(filename, size);
}