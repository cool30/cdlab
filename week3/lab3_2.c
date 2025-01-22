#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100
#define MAX_TOKENS 1000

typedef enum
{
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_KEYWORD,
    TOKEN_STRING,
    TOKEN_COMMENT,
    TOKEN_PREPROCESSOR,
    TOKEN_UNKNOWN,
    TOKEN_EOF
} TokenType;

typedef struct
{
    int row;
    int col;
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
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
    token.type = TOKEN_UNKNOWN;
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
            token.type = TOKEN_PREPROCESSOR;
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
            token.type = TOKEN_STRING;
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
            token.type = TOKEN_IDENTIFIER;
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
                token.type = TOKEN_KEYWORD;
            }
            return token;
        }

        // Handle numbers
        if (isdigit(c))
        {
            token.type = TOKEN_NUMBER;
            int i = 0;
            token.value[i++] = c;
            while (isdigit((c = fgetc(source))))
            {
                token.value[i++] = c;
                (*col)++;
            }
            ungetc(c, source);
            token.value[i] = '\0';
            return token;
        }

        // Handle operators
        token.type = TOKEN_OPERATOR;
        token.value[0] = c;
        token.value[1] = '\0';
        return token;
    }

    token.type = TOKEN_EOF;
    return token;
}

int main()
{
    Token *tokens = NULL;
    char filename[128];
    printf("\nEnter the filename: ");
    scanf("%s", filename);
    FILE *file1 = fopen("lab3_1.c", "r");
    tokens = getNextToken(file1, tokens->row, tokens->col);
    while (tokens->value != EOF)
    {
        printf("%c", tokens->value);
        tokens = getNextToken(file1, 0, 0);
    }

    fclose(file1);
    return 0;
}
