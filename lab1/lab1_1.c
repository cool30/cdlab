#include <stdio.h>
#include <sys/types.h>

void copyFileContent(char *srcFile, char *destFile)
{
    FILE *file1 = fopen(srcFile, "r");
    FILE *file2 = fopen(destFile, "w+");
    if (file1 == NULL)
    {
        printf("\nFile does not exists");
        return;
    }

    char c = fgetc(file1);
    while (c != EOF)
    {
        fputc(c, file2);
        c = fgetc(file1);
    }
    printf("Copied Done, Check the destination file: %s", destFile);
    fclose(file2);
    fclose(file1);
}

void countLinesCharacters(char *filename)
{
    FILE *file1 = fopen(filename, "r");
    if (file1 == NULL)
    {
        printf("\nFile does not exists");
        return;
    }
    ssize_t lineCount = 1, charCount = 0;
    char c = fgetc(file1);
    while (c != EOF)
    {
        if (c == '\n')
        {
            lineCount++;
        }
        c = fgetc(file1);
        charCount++;
    }
    printf("FileName: %s,\tTotal Charcter(s):%d,\tTotal Line(s)%d", filename, charCount, lineCount);
    fclose(file1);
}

void main()
{
    char srcFile[128], destFile[128];
    printf("Enter the source filename: ");
    scanf("%s", srcFile);
    countLinesCharacters(srcFile);
}