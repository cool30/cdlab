#include <stdio.h>

int main()
{
    int a, b;
    float c;
    printf("\nEnter the a: ");
    scanf("%d", &a);
    printf("\nEnter the b: ");
    scanf("%d", &b);
    if (a < b)
    {
        printf("%d\t is smallest number", a);
    }
    else
    {
        printf("%d\t is smallest number", b);
    }
    return 0;
}