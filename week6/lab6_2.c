#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char wording[128];
int indx = 0;

/*
S→UVW
U →(S) | aSb | d
V → aV | null
W → cW | null
*/

void S();
void U();
void V();
void W();

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

void W()
{
    if (wording[indx] == 'c')
    {
        indx++;
        W();
    }
    else if (wording[indx] == '$')
    {
        return;
    }
}

void V()
{
    if (wording[indx] == 'a')
    {
        indx++;
        V();
    }
    else if (wording[indx] == '$')
    {
        return;
    }
}

void U()
{
    if (wording[indx] == '(')
    {
        indx++;
        S();
        if (wording[indx] == ')')
        {
            indx++;
            return;
        }
    }
    else if (wording[indx] == 'a')
    {
        indx++;
        S();
        if (wording[indx] == 'b')
        {
            indx++;
            return;
        }
    }
    else if (wording[indx] == 'd')
    {
        indx++;
        return;
    }
}

void S()
{
    if (wording[indx] == '$')
    {
        return;
    }
    U();
    V();
    W();
}

int main()
{
    printf("\nEnter the message: ");
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