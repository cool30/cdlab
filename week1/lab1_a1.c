#include <stdio.h>

void getDetails(char *filename)
{
    int blankSpace = 0, semiColon=0, blankLine=0;
    FILE *file1 = fopen(filename, "r");
    if (file1 == NULL)
    {
        printf("\nFile does not exists");
        return;
    }
    char c1 = fgetc(file1), c2;
    while (c1 != EOF)
    {
        if (c1 == ' ' || c1 == '\t')
        {
            blankSpace++;
        }
        if (c1 == ';')
        {
            semiColon++;
        }
        if (c1 == '\n')
        {
            blankLine++;
        }
        c1=fgetc(file1);
    }
    printf("\nBlankSpace: %d", blankSpace);
    printf("\nSemincolon: %d", semiColon);
    printf("\nBlankLine: %d", blankLine);
    fclose(file1);
}

void main()
{
    char filename[100];
    printf("\nEnter the filename: ");
    scanf("%s", filename);

    getDetails(filename);
}
