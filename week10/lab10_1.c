#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 1024

void toUpperCase(char *word)
{
    int i = 0;
    while (word[i] != '\0')
    {
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            word[i] -= 32;
        }
        i++;
    }
}

int isKeyword(char *word, char **keywords, int num_keywords)
{
    for (int i = 0; i < num_keywords; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void keyword_to_Uppercase(char **keywords, int num_keywords, char *srcFile, char *destFile)
{
    char buffer[SIZE];
    FILE *file1 = fopen(srcFile, "r");
    FILE *file2 = fopen(destFile, "w");
    
    if (!file1 || !file2) {
        printf("Error opening files.\n");
        return;
    }

    char c = fgetc(file1);
    while (c != EOF)
    {
        int k = 0;
        // Skip non-alphabetic characters and get the next word
        while (c != EOF && !isalpha(c)) 
        {
            fputc(c, file2); // Write punctuation/space directly to the output file
            c = fgetc(file1);
        }

        // Read the word into the buffer
        while (c != EOF && isalpha(c)) 
        {
            buffer[k++] = c;
            c = fgetc(file1);
        }
        buffer[k] = '\0';

        if (k > 0 && isKeyword(buffer, keywords, num_keywords))
        {
            toUpperCase(buffer);
        }

        // Write the word (or uppercase word) to the output file
        if (k > 0)
        {
            fprintf(file2, "%s", buffer);
        }
    }

    fclose(file1);
    fclose(file2);
}

int main()
{
    char srcFile[SIZE], destFile[SIZE];
    char *keywords[] = {"int", "if", "void", "char","return"};
    printf("\nEnter the srcFile: ");
    scanf("%s", srcFile);
    printf("\nEnter the destFile: ");
    scanf("%s", destFile);
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);
    keyword_to_Uppercase(keywords, num_keywords, srcFile, destFile);
    return 0;
}
