#include <stdio.h>

void readLinesAtsameTime(char *srcfile1, char *srcfile2, char *destFile)
{
    char buffer[1024];
    FILE *file1 = fopen(srcfile1, "r");
    FILE *file2 = fopen(srcfile2, "r");
    FILE *file3 = fopen(destFile, "w+");

    // to read same lines from two files concurrently
    while (1)
    {
        if (fgets(buffer, sizeof(buffer), file1))
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
    
    // if file2 is read but file1 not
    while (fgets(buffer, sizeof(buffer), file1))
    {
        fputs(buffer, file3);
    }

    // if file1 is read but file2 not
    while (fgets(buffer, sizeof(buffer), file2))
    {
        fputs(buffer, file3);
    }

    fclose(file1);
    fclose(file2);
    fclose(file3);
}

int main()
{
    char file1[128], file2[128], destFile[128];
    printf("\nEnter the source file1 : ");
    scanf("%s", file1);
    printf("\nEnter the source file2 : ");
    scanf("%s", file2);
    printf("\nEnter the destination file : ");
    scanf("%s", destFile);
    readLinesAtsameTime(file1, file2, destFile);
    printf("Operation accomplished, open file named %s to view",destFile);
    return 0;
}