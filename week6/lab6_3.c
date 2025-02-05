#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char wording[128];
int indx = 0;

/*
S → aAcBe
A → Ab|b //has left recusrion so below 2 lines removes left recursion
    A -> bA'
    A'-> bA' | null
B → d
*/

void S();
void A();
void Aprime();
void B();

void valid()
{
    printf("\n===================SUCCESS!==================\n");
    exit(0);
}

void invalid()
{
    printf("\nError char : %c at index %d", wording[indx], indx);
    printf("\n===================ERROR!==================\n");
    exit(0);
}

void A()
{
    if (wording[indx] == 'b')
    {
        indx++;
        Aprime();
    }
    else if (wording[indx] == '$')
    {
        return;
    }
}

void Aprime()
{
    if (wording[indx] == 'b')
    {
        indx++;
        Aprime();
    }
    else if (wording[indx] == '$')
    {
        return;
    }
}

void B()
{
    if (wording[indx] == 'd')
    {
        indx++;
        return;
    }
    else
    {
        invalid();
    }
}

void S()
{
    if (wording[indx] == 'a')
    {
        indx++;
        A();
        if (wording[indx] == 'c')
        {
            indx++;
            B();
            if (wording[indx] == 'e')
            {
                indx++;
                return;
            }
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}

int main()
{
    printf("\nEner the message: ");
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