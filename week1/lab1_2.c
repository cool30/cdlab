#include<stdio.h>

void reverseFile(FILE *file1, FILE *file2)
{
    char c = fgetc(file1);
    if (c==EOF)
    {
        return;
    }
    reverseFile(file1,file2);
    fputc(c,file2);
}

int main()
{
    char srcFile[128], destFile[128];
    printf("\nEnter the source file : ");
    scanf("%s",srcFile);
    printf("\nEnter the destination file : ");
    scanf("%s", destFile);
    FILE *file1 = fopen(srcFile,"r");
    FILE *file2 = fopen(destFile,"w+");
    reverseFile(file1,file2);
    printf("Reversed successfully, open file named %s to view",destFile);
    fclose(file1);
    fclose(file2);
    return 0;
}