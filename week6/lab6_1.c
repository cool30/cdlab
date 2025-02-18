#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char wording[128];
int indx = 0;

/*
S→a | > | ( T )
T→T,S | S  // has left recusrion so below 2 lines removes left recursion
    T->S T'
    T'->,ST' | null
*/

void S();
void T();
void Tprime();

void valid()
{
    printf("\n===================SUCCESS!==================\n");
    exit(0);
}

void invalid()
{
    printf("\n===================ERROR!==================\n");
    exit(0);
}

void Tprime()
{
    if (wording[indx] == ',')
    {
        indx++;
        S();
        Tprime();
    }
    else if (wording[indx] == '$')
    {
        return ;
    }
}

void T()
{
    S();
    Tprime();
}

void S()
{
    if (wording[indx] == 'a' || wording[indx] == '>')
    {
        indx++;
    }
    else if (wording[indx] == '(')
    {
        indx++;
        T();
        if (wording[indx] == ')')
        {
            indx++;
            return;
        }
    }
    else
    {
        printf("\tError char in S: %c\t", wording[indx]);
        invalid();
    }
}

int main()
{
    printf("Enter the message: ");
    scanf("%s", wording);
    S();
    if (wording[indx] == '$')
    {
        valid();
    }
    else
    {
        invalid();
    }
    return 0;
}