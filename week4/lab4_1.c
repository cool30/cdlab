#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "myfun.h"

#define TABLE_SIZE 100  // Define the size of the hash table

// Define the symbol table entry structure
typedef struct {
    int slno;
    char lexemeName[128];
    char tokenType[128];
    char datatype[128];
    int size;
} Local;

// Define a hash table to store the local symbol table
Local symbolTable[TABLE_SIZE];

// Hash function to calculate the index
unsigned int hashFunction(char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % TABLE_SIZE;
}

int insertSymbolTable(Local symbolTable[], char *lexemeName, char *tokenType, char *datatype, int size) {
    unsigned int index = hashFunction(lexemeName);

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (symbolTable[i].lexemeName[0] == '\0') {
            symbolTable[i].slno = i + 1;
            strncpy(symbolTable[i].lexemeName, lexemeName, sizeof(symbolTable[i].lexemeName) - 1);
            strncpy(symbolTable[i].tokenType, tokenType, sizeof(symbolTable[i].tokenType) - 1);
            strncpy(symbolTable[i].datatype, datatype, sizeof(symbolTable[i].datatype) - 1);
            symbolTable[i].size = size;
            return 1;  // Insertion successful
        }
    }

    return 0;  // Symbol table is full
}

void displaySymbolTable(Local symbolTable[]) {
    printf("Sl.no\tLexeme_Name\tToken_Type\tData_Type\tSize\n");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (symbolTable[i].lexemeName[0] != '\0') { // non-empty slot
            printf("%d\t%s\t\t%s\t%s\t\t%d\n", symbolTable[i].slno, symbolTable[i].lexemeName,
                   symbolTable[i].tokenType, symbolTable[i].datatype, symbolTable[i].size);
        }
    }
}

// Function to determine if a string represents a basic data type
int isDataType(char *lexeme) {
    char *dataTypes[] = {"int", "float", "char", "double", "long", "short", "void"};
    for (int i = 0; i < sizeof(dataTypes) / sizeof(dataTypes[0]); i++) {
        if (strcmp(lexeme, dataTypes[i]) == 0) {
            return 1;  // It's a data type
        }
    }
    return 0;  // Not a data type
}

int main() {
    char filename[128];
    printf("Enter the filename: ");
    scanf("%s", filename);

    FILE *source = fopen(filename, "r");
    if (!source) {
        printf("Error opening file\n");
        return 1;
    }

    int row = 1, col = 1;
    Token token;
    
    while ((token = getNextToken(source, &row, &col)).type != token_EOF) {
        if (token.type == token_ID || token.type == token_KEYWORD) {
            char datatype[128] = "int";  // Default datatype for identifiers
            int size = strlen(token.value);  // Placeholder for size based on lexeme length

            // Check if the token is a data type keyword
            if (isDataType(token.value)) {
                strncpy(datatype, token.value, sizeof(datatype) - 1); // Set the correct datatype
            }

            // Check if the token is an identifier and if it's followed by '(' (indicating it's a function)
            int nextChar = fgetc(source);  // Look ahead to check for '('
            if (nextChar == '(') {
                insertSymbolTable(symbolTable, token.value, "Function", datatype, size);
            } else {
                // If it's not a function, treat it as a regular identifier (variable)
                ungetc(nextChar, source);  // Put back the character for further processing
                insertSymbolTable(symbolTable, token.value, "Identifier", datatype, size);
            }
        }
    }
    fclose(source);
    
    // Display the local symbol table
    displaySymbolTable(symbolTable);
    return 0;
}