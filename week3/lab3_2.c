#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max_token_LENGTH 100

typedef enum
{
    token_ID,
    token_NUMBER,
    token_OPERATOR,
    token_KEYWORD,
    token_STRING,
    token_COMMENT,
    token_PREPROCESSOR,
    token_UNKNOWN,
    token_EOF
} TokenType;

typedef struct
{
    int row;
    int col;
    TokenType type;
    char value[max_token_LENGTH];
} Token;

const char *keywords[] = {
    "int", "float", "double", "char", "return", "if", "else", "while", "for", "void", NULL};

int isKeyword(const char *word)
{
    for (int i = 0; keywords[i] != NULL; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

Token getNextToken(FILE *source, int *row, int *col)
{
    Token token;
    token.row = *row;
    token.col = *col;
    token.type = token_UNKNOWN;
    token.value[0] = '\0';

    int c;
    while ((c = fgetc(source)) != EOF)
    {
        (*col)++;

        // Handle new lines
        if (c == '\n')
        {
            (*row)++;
            *col = 0;
            continue;
        }

        // Skip whitespace
        if (isspace(c))
        {
            continue;
        }

        // Handle comments
        if (c == '/')
        {
            c = fgetc(source);
            if (c == '/')
            { // Single-line comment
                while ((c = fgetc(source)) != EOF && c != '\n')
                {
                    (*col)++;
                }
                (*row)++;
                *col = 0;
                continue;
            }
            else if (c == '*')
            { // Multi-line comment
                while (1)
                {
                    c = fgetc(source);
                    if (c == EOF)
                        break;
                    if (c == '*')
                    {
                        c = fgetc(source);
                        if (c == '/')
                        {
                            break;
                        }
                    }
                    if (c == '\n')
                    {
                        (*row)++;
                        *col = 0;
                    }
                }
                continue;
            }
            else
            {
                ungetc(c, source); // Not a comment, put back the character
                c = '/';
            }
        }

        // Handle preprocessor directives
        if (c == '#')
        {
            token.type = token_PREPROCESSOR;
            token.value[0] = c;
            int i = 1;
            while ((c = fgetc(source)) != EOF && c != '\n')
            {
                token.value[i++] = c;
                (*col)++;
            }
            token.value[i] = '\0';
            return token;
        }

        // Handle string literals
        if (c == '"')
        {
            token.type = token_STRING;
            int i = 0;
            token.value[i++] = c;
            while ((c = fgetc(source)) != EOF)
            {
                token.value[i++] = c;
                (*col)++;
                if (c == '"')
                {
                    break;
                }
            }
            token.value[i] = '\0';
            return token;
        }

        // Handle identifiers and keywords
        if (isalpha(c) || c == '_')
        {
            token.type = token_ID;
            int i = 0;
            token.value[i++] = c;
            while (isalnum((c = fgetc(source))) || c == '_')
            {
                token.value[i++] = c;
                (*col)++;
            }
            ungetc(c, source);
            token.value[i] = '\0';
            if (isKeyword(token.value))
            {
                token.type = token_KEYWORD;
            }
            return token;
        }

        // Handle numbers
        if (isdigit(c))
        {
            token.type = token_NUMBER;
            int i = 0;
            token.value[i++] = c;
            while (isdigit((c = fgetc(source)))){
                token.value[i++] = c;
                (*col)++;
            }
            ungetc(c, source);
            token.value[i] = '\0';
            return token;
        }

        // Handle operators
        token.type = token_OPERATOR;
        token.value[0] = c;
        token.value[1] = '\0';
        return token;
    }

    token.type = token_EOF;
    return token;
}

int main()
{
    char filename[128];
    printf("\nEnter the filename: ");
    scanf("%s", filename);

    FILE *file1 = fopen(filename, "r");
    if (file1 == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    int row = 1, col = 0;
    Token token = getNextToken(file1, &row, &col);

    printf("\nFormat: <value,token_type,row,col>");
    while (token.type != token_EOF)
    {
        printf("<%d, %d, %d, %s>\n", token.row, token.col, token.type, token.value);
        token = getNextToken(file1, &row, &col);
    }

    fclose(file1);
    return 0;
}
