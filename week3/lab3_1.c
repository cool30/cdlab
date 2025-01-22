#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isArithmeticOp(char *c)
{
    return (
        strcmp(c, "+") == 0 ||
        strcmp(c, "-") == 0 ||
        strcmp(c, "*") == 0 ||
        strcmp(c, "/") == 0 ||
        strcmp(c, "++") == 0 ||
        strcmp(c, "--") == 0 ||
        strcmp(c, "%") == 0);
}

int isLogicalOp(char *c)
{
    return (
        strcmp(c, "||") == 0 ||
        strcmp(c, "&&") == 0 ||
        strcmp(c, "!=") == 0);
}

int isRelationOp(char *c)
{
    return (
        strcmp(c, "<") == 0 ||
        strcmp(c, ">") == 0 ||
        strcmp(c, "<=") == 0 ||
        strcmp(c, ">=") == 0 ||
        strcmp(c, "=") == 0 ||
        strcmp(c, "==") == 0);
}

int isSpecialSymbol(char *c)
{

    return (
        strcmp(c, ";") == 0 ||
        strcmp(c, ",") == 0 ||
        strcmp(c, "(") == 0 ||
        strcmp(c, ")") == 0 ||
        strcmp(c, "{") == 0 ||
        strcmp(c, "}") == 0 ||
        strcmp(c, "[") == 0 ||
        strcmp(c, "]") == 0 ||
        strcmp(c, ".") == 0 ||
        strcmp(c, "&") == 0 ||
        strcmp(c, "|") == 0 ||
        strcmp(c, "^") == 0 ||
        strcmp(c, "~") == 0 ||
        strcmp(c, "?") == 0 ||
        strcmp(c, ":") == 0);
}

int isKeyword(char *c)
{
    char *keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while",
        "inline", "restrict", "bool", "complex", "imaginary"};

    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
    {
        if (strcmp(c, keywords[i]) == 0)
        {
            return 1; // It's a keyword
        }
    }
    return 0; // Not a keyword
}

int isNumericalConstant(char *c)
{
    int hasDecimalPoint = 0, i = 0;
    // Check for optional sign
    if (c[i] == '+' || c[i] == '-')
    {
        i++;
    }
    // Check digits
    while (c[i] != '\0')
    {
        if (c[i] == '.')
        {
            if (hasDecimalPoint)
            {
                return 0; // More than one decimal point
            }
            hasDecimalPoint = 1; // Found a decimal point
        }
        else if (!isdigit(c[i]))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

void identifyOperator(char *filename)
{
    char buffer[128];
    int i = 0, rowCount = 1;
    FILE *file1 = fopen(filename, "r");

    if (file1 == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return;
    }

    char c;
    while ((c = fgetc(file1)) != EOF)
    {
        // Skip whitespace
        if (isspace(c))
        {
            if (c == '\n')
            {
                rowCount++;
            }
            continue;
        }

        // Handle token extraction for operators
        i = 0;
        if (ispunct(c))
        {
            // Handle single character operators
            buffer[i++] = c;
            // Check for two-character operators
            if (c == '+' || c == '-' || c == '!' || c == '<' || c == '>')
            {
                char next = fgetc(file1);
                if (next == c || next == '=' || next == '-')
                { // Handle ++, --, ==, !=, <=, >=
                    buffer[i++] = next;
                }
                else
                {
                    ungetc(next, file1); // Put back the character if it's not part of an operator
                }
            }
            buffer[i] = '\0';
            if (isArithmeticOp(buffer))
            {
                printf("\nArithmetic Operator: %s at row number: %d\n", buffer, rowCount);
            }
            else if (isRelationOp(buffer))
            {
                printf("\nRelational Operator: %s at row number: %d\n", buffer, rowCount);
            }
            else if (isLogicalOp(buffer))
            {
                printf("\nLogical Operator: %s at row number: %d\n", buffer, rowCount);
            }
            else if(isNumericalConstant(buffer))
            {
                printf("\nNumeric Constant: %s at row number: %d\n", buffer, rowCount);
            }
            else if(isSpecialSymbol(buffer))
            {
                printf("\nSpecial Symbol: %s at row number: %d\n", buffer, rowCount);
            }
            else if(isKeyword(buffer)){
                printf("\nKeyword is: %s at row number: %d\n", buffer, rowCount);
            }
        }
    }
    fclose(file1);
}

int main()
{
    char filename[128];
    printf("\nEnter the filename: ");
    scanf("%s", filename);
    identifyOperator(filename);
    return 0;
}
