#include <stdio.h>

void mergeLinesfromFiles(char *srcFile1, char *srcFile2, char *destFile)
{
    char buffer[1024], c1, c2;
    int i = 0;
    FILE *file1 = fopen(srcFile1, "r");
    FILE *file2 = fopen(srcFile2, "r");
    FILE *file3 = fopen(destFile, "w+");
    if (file1 == NULL)
    {
        printf("\n%s not found", srcFile1);
        return;
    }
    if (file2 == NULL)
    {
        printf("\n%s not found", srcFile2);
        return;
    }
    while (1)
    {
        if (fgets(buffer, sizeof(buffer), file1)) // potential to get the string upto '\n'
        {
            fputs(buffer, file3);
        }
        else
        {
            break;
        }
        if (fgets(buffer, sizeof(buffer), file2))
        {
            fputs(buffer, file3);
        }
        else
        {
            break;
        }
    }

    while (fgets(buffer,sizeof(buffer),file1))
    {
        fputs(buffer,file3);
    }

    while (fgets(buffer,sizeof(buffer),file2))
    {
        fputs(buffer,file3);
    }

    fclose(file1);
    fclose(file2);
    fclose(file3);
}

void main()
{
    char srcFile1[128], srcFile2[128], destFile[128];
    printf("Enter the source filename1: ");
    scanf("%s", srcFile1);
    printf("Enter the source filename2: ");
    scanf("%s", srcFile2);
    printf("Enter the destination filename: ");
    scanf("%s", destFile);
    mergeLinesfromFiles(srcFile1, srcFile2, destFile);
}