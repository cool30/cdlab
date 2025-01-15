#include <stdio.h>

void removeSpace(char *srcFile, char *destFile)
{
    FILE *file1 = fopen(srcFile, "r");
    FILE *file2 = fopen(destFile, "w");
    char c = fgetc(file1);
    while (c != EOF)
    {
        if (c == ' ')
        {
            while (c == ' ')
            {
                c = fgetc(file1);
            }
            if (c != ' ')
            {
                fputc(' ', file2);
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

int main()
{
    char srcFile[1024], destFile[1024];
    printf("\nEnter the srcFile: ");
    scanf("%s", srcFile);
    printf("\nEnter the destFile: ");
    scanf("%s", destFile);
    removeSpace(srcFile, destFile);
    return 0;
}