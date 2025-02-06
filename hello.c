#include <stdio.h>
#include "mpi.h"

int revNum(int num)
{
    int rev = 0, temp = num;
    while (temp > 0)
    {
        rev = (rev * 10) + (temp % 10);
        temp/=10;
    }
    return rev;
}

int main(int argc, char *argv[])
{
    int size, rank, input[9], output[9];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        printf("\nEnter the %d array elements: ", size);
        for (int i = 0; i < 9; i++)
        {
            scanf("%d", &input[i]);
        }
    }
    //Make array available to all process
    MPI_Bcast(input,9,MPI_INT,0,MPI_COMM_WORLD);
    int temp = revNum(input[rank]);
    // printf("\n%d",temp); //to display the intermidiate result
    MPI_Gather(&temp, 1, MPI_INT, output, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("\nReverse numbers are: ");
        for (int i = 0; i < 9; i++)
        {
            printf("%d\t", output[i]);
        }
    }
    MPI_Finalize();
    return 0;
}

/*
18
523
301
1234
2
14
108
150
1928
*/

#include <stdio.h>
#include <math.h>
#include "mpi.h"

int isPrime(int num)
{
    if (num < 2)
    {
        return 0;
    }
    else
    {
        for (int i = 2; i < sqrt(num); i++)
        {
            if (num % i == 0)
            {
                return 0;
            }
        }
        return 1;
    }
}

void getPrimeNum(int *input, int *output)
{
    int j = 0;
    for (int i = 0; i < 100; i++)
    {
        if (isPrime(input[i]))
        {
            output[j++] = input[i];
        }
        else
        {
            output[j++] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    int size, rank, input[100], output[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        printf("\nEnter the array element: ");
        for (int i = 0; i < 100; i++)
        {
            input[i] = i + 1;
        }
    }
    MPI_Bcast(input, sizeof(input) / sizeof(input[0]), MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 1)
    {
        getPrimeNum(input, output);
        printf("\nPrime numbers are: ");
        for (int i = 0; i < 100; i++)
        {
            if (output[i]!=0)
            {
                printf("\t%d", output[i]);
            }        
        }
    }

    MPI_Finalize();
    return 0;
}

#include <stdio.h>
#include <math.h>
#include "mpi.h"

int isPrime(int num)
{
    if (num < 2)
    {
        return 0;
    }
    else
    {
        for (int i = 2; i < sqrt(num); i++)
        {
            if (num % i == 0)
            {
                return 0;
            }
        }
        return num;
    }
}

int main(int argc, char *argv[])
{
    int size, rank, input[20], output[20];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        printf("\nEnter the array element: ");
        for (int i = 0; i < 20; i++)
        {
            input[i] = i + 1;
        }
    }
    MPI_Bcast(input, sizeof(input) / sizeof(input[0]), MPI_INT, 0, MPI_COMM_WORLD);
    int temp = isPrime(input[rank]);
    MPI_Gather(&temp, 1, MPI_INT, output, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("\nPrime numbers are: ");
        for (int i = 0; i < 20; i++)
        {
            if (output[i] != 0)
            {
                printf("\t%d", output[i]);
            }
        }
    }

    MPI_Finalize();
    return 0;
}



#include <stdio.h>
#include "mpi.h"

int fact(int num)
{
    if (num < 2)
    {
        return 1;
    }
    else
    {
        return num * fact(num - 1);
    }
}

int summation(int num)
{
    return num * (num + 1) / 2;
}

int main(int argc, char *argv[])
{
    int size, rank, res, finRes = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if ((rank + 1) % 2 == 1)
    {
        res = fact(rank + 1);
        printf("\nProcess%d says, Factorial result = %d", rank, res);
    }
    else
    {
        res = summation(rank + 1);
        printf("\nProcess%d says, Summation result = %d", rank, res);
    }
    MPI_Reduce(&res, &finRes, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("\n\nFinal Result: %d\n", finRes);
    }

    MPI_Finalize();
    return 0;
}


#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int size, rank, input[9], element, totlen, oddCount = 0, count;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        totlen = size; // to take array length from terminal
        printf("\nEnter %d number of elements: ", totlen);
        for (int i = 0; i < totlen; i++)
        {
            scanf("%d", &input[i]);
        }
    }
    MPI_Bcast(&totlen, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(input, 1, MPI_INT, &element, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if ((element % 2) == 0)
    {
        element = 1;
        input[rank] = element;
        oddCount++;
    }
    else
    {
        element = 0;
        input[rank] = element;
    }
    //  get the oddsum so that total array element count - (odd count) = (even count)
    MPI_Reduce(&oddCount, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Gather(&element, 1, MPI_INT, input, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("Result array is: ");
        for (int i = 0; i < totlen; i++)
        {
            printf("%d\t", input[i]);
        }
        printf("\nEven(Count) = %d\nOdd(Count) = %d\n", count, (totlen - count));
    }

    MPI_Finalize();
    return 0;
}


/*
Output: 
student@dbl-23:~/Desktop/220905536/lab1.c/addn$ mpicc lab3a_1.c
student@dbl-23:~/Desktop/220905536/lab1.c/addn$ mpirun -np 9 ./a.out

Enter 9 number of elements: 1 2 3 4 5 6 7 8 9
Result array is: 0      1       0       1       0       1       0       1       0
Even(Count) = 4
Odd(Count) = 5
student@dbl-23:~/Desktop/220905536/lab1.c/addn$ 
*/


