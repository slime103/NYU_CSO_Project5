/*
*
* Author: Zachary Stephens
*
* For compilation use: gcc -Wall problem1.c -o problem1
*
* Sample Output from test runs:
* Time to output (no forks) = 0.004131 (seconds)
* Time to output (with forks) = 0.000822 (seconds)
*
*/


#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>


int isPrime(int n)
{
    //base cases
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;

    //Base checks
    if (n % 2 == 0 || n % 3 == 0)
        return 0;

    //Check if of the form 6k +- 1
    for (int i = 5; i * i < n; i = i +6)
    {
        if (n % i == 0 || n % (i+2) == 0)
           return 0;
    }

    //printf("%d is prime\n", n);
    return 1;
}

//Checks if the sum of the digits equal 11
int addToEleven(int n)
{
    int sum = 0;

    while (n > 0)
    {
        sum += n%10;
        n/=10;

        if (sum > 11)
            return 0;
    }

    if (sum == 11)
    {
        return 1;
    }

    return 0;
}

void writeNum()
{

}

int main()
{
    clock_t time;
    time = clock();
    double cpuTimeElapsed;

    int n = 100000;

    //we want to find primes with digits that add to 7 so start at 29 which is first prime that adds to 7
    for (int i = 29; i <= n; i++)
    {
        if(isPrime(i) && addToEleven(i))
        {
            FILE *fp = fopen("p1Output1.txt", "a");
            fprintf(fp, "%d\n", i);
            fclose(fp);
        }
    }

    time = clock() - time;
    cpuTimeElapsed = ((double)(time))/CLOCKS_PER_SEC;

    printf("Time to output (no forks) = %f\n", cpuTimeElapsed);

    //Split 10 ways

    time = clock();

    n = 10000;

    char fileName[8] = {'o', 'u', 't', '0', '.', 't', 'x', 't'};

    for (int k = 0; k < 10; k++)
    {
        fileName[3] = k + '0';

        if (fork() == 0)
        {
            for (int j = 10000 * k + 1; j <= n; j++)
            {
                if(isPrime(j) && addToEleven(j))
                {

                    FILE *fp = fopen(fileName, "a");
                    fprintf(fp, "%d\n", j);
                    fclose(fp);
                }
            }
            exit(0);
        }
        if (n < 100000)
        {
            n += 10000;
        }

        wait(NULL);

    }

    //Merge Files
    FILE *outF = fopen("MergedOutput.txt", "a");

    for (int k = 0; k < 10; k++)
    {
        fileName[3] = k + '0';

         //open files
        FILE *outX = fopen(fileName, "r");

        //copy over contents
        char c = fgetc(outX);
        while (c != EOF)
        {
            fputc(c, outF);
            c = fgetc(outX);
        }

        fclose(outX);
    }

        //close files
        fclose(outF);

    time = clock() - time;
    cpuTimeElapsed = ((double)(time))/CLOCKS_PER_SEC;

    printf("Time to output (with forks) = %f\n", cpuTimeElapsed);


    return 0;
}