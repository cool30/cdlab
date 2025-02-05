#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char wording[128];
int indx = 0;

/*
S →(L) | a
L → L,S | S //has left recusrion so below 2 lines removes left recursion

    L -> SL'
    L' -> ,SL' | null
*/

void S();
void L();
void Lprime();

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

void Lprime()
{
    if (wording[indx] == ',')
    {
        indx++;
        S();
        Lprime();
    }
    else if (wording[indx] == '$')
    {
        return;
    }
}

void L()
{
    S();
    Lprime();
}

void S()
{
    if (wording[indx] == 'a')
    {
        indx++;
    }
    else if (wording[indx] == '(')
    {
        indx++;
        L();
        if (wording[indx]==')')
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
    printf("\nEnter the string input: ");
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