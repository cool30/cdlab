#include <stdio.h>

#define size 1024

void discardPreproessor(char *srcFile, char *destFile)
{
    FILE *file1 = fopen(srcFile, "r");
    FILE *file2 = fopen(destFile, "w");
    char c = fgetc(file1);
    while (c != EOF)
    {
        // this is done if string has pre-processor directives word in print statement
        if (c == '\"')
        {
            fputc(c, file2);
            c = fgetc(file1);
            while (c != '\"' && c != EOF)
            {
                fputc(c, file2);
                c = fgetc(file1);
            }
            if (c == '\"')
            {
                fputc(c, file2);
            }
        }
        // logic to skip directives
        else if (c == '#')
        {
            while (c != '\n' && c != EOF)
            {
                c = fgetc(file1);
            }
        }
        // any other characters
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
    char srcFile[size], destFile[size];
    printf("\nEnter the srcFile: ");
    scanf("%s", srcFile);
    printf("\nEnter the destFile: ");
    scanf("%s", destFile);
    discardPreproessor(srcFile, destFile);
    return 0;
}