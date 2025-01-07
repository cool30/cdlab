#include <stdio.h>

void reverseSomething(char *srcFile, char *destFile, FILE *file1, FILE *file2)
{
    char c = fgetc(file1);
    if (c == EOF)
    {
        return;
    }
    reverseSomething(srcFile, destFile, file1, file2);
    fputc(c, file2);
}

void main()
{
    char srcFile[128], destFile[128];
    printf("Enter the source filename: ");
    scanf("%s", srcFile);
    printf("Enter the destination filename: ");
    scanf("%s", destFile);

    FILE *file1 = fopen(srcFile, "r");
    FILE *file2 = fopen(destFile, "w+");
    reverseSomething(srcFile, destFile, file1, file2);

    fclose(file1);
    fclose(file2);
}