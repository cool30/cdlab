#include <stdio.h>
#include <stdlib.h>

void countChar_Lines(char *filename)
{
    int charCount=0, lineCount=0;
    FILE *file1 = fopen(filename,"r");
    char c = fgetc(file1);
    while (c!=EOF)
    {
        charCount++;
        if (c=='\n')
        {
            lineCount++;
            charCount--;
        }
        c = fgetc(file1);
    }
    printf("\nNumber of charcters is: %d",charCount);
    printf("\nNumber of Lines in file is: %d\n",lineCount);
    fclose(file1);
}

int main()
{
    char filename[100];
    printf("Enter the filename to open for reading: \n");
    scanf("%s", filename);
    countChar_Lines(filename);
    return 0;
}