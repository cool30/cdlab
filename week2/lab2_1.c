#include <stdio.h>

void getNewFile(char *cfilename, char *filename)
{
    FILE *file1 = fopen(cfilename, "r");
    FILE *file2 = fopen(filename, "w+");
    char c = fgetc(file1);
    while (c != EOF)
    {
        if (c == ' ')
        {
            c = fgetc(file1);
            if (c == ' ')
            {
                continue;
            }
            else
            {
                fputc(c, file2);
            }
        }
        else
        {
            fputc(c, file2);
        }
        c = fgetc(file1);
    }
    fclose(file1);
    fclose(file2);
}

void main()
{
    char filename[128], cfilename[128];
    printf("\nEnter the c-filename: ");
    scanf("%s", cfilename);
    printf("\nEnter the filename: ");
    scanf("%s", filename);
    getNewFile(cfilename, filename);
}