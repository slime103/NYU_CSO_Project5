/*
*
*
*
* Compile with gcc -Wall problem2p.c -o problem2p
*
*
*/



#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include<time.h>

pid_t pid;
int missedQ = 0;
int outOfTime = 0; //bool

void handle_sigint(int sig)
{
    missedQ++;
    outOfTime = 1;
    printf("Out of Time!\n");
}

int main(int argc, char **argv)
{
    //setup signaling
    signal(SIGINT, handle_sigint);

    //number of questions
    int n;
    printf("Please enter the number of questions you would like to answer.\n");
    scanf("%d", &n);
    int max = 12;

    //numbers & operator
    int n1, n2, op;
    char charOp;
    int answer;
    int input = 0;

    //answer saving
    int incorrect[50];
    int i_incorrect = 0;
    int answers[n];
    int i_answers = 0;

    //Create Child process
    pid = fork();
    if (pid == 0)
    {
        pid= execve("problem2c",NULL, NULL);
    }

    while (i_answers < n)
    {
        //pick random number seed
        srand(time(0));

        //number picking
        n1 = rand() % max;
        n2 = rand() % max;
        op = rand() % 3;

        //select operation
        switch(op)
        {
            case 0: answer = n1 * n2;
                charOp = '*';
                break;
            case 1: answer = n1 + n2;
                charOp = '+';
                break;
            case 2: answer = n1 - n2;
                charOp = '-';
                break;
        }

        //save answer
        answers[i_answers] = answer;
        i_answers++;

        printf("What is %d %c %d ?\n", n1, charOp, n2);

        while (input != answer)
        {
            //Get Input
            scanf("%d", &input);

            if (outOfTime)
            {
                outOfTime = 0;
                kill(pid, SIGINT);
                break;
            }

            if (input == answer)
            {
                printf("You win!\n");

                //Reset Timer
                kill(pid, SIGINT);
            }
            else
            {
                if (i_incorrect < 50)
                    incorrect[i_incorrect] = input;
                i_incorrect++;
                printf("Incorrect, try again.\n");
            }
        }
    }

    //print correct answers

    printf("Correct Answers:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", answers[i]);
    }
    printf("\n");

    //print incorrect answers

    printf("Incorrect Answers:\n");
    for (int k = 0; k < i_incorrect; k++)
    {
        if (i_incorrect < 50)
            printf("%d, ", incorrect[k]);
        else
            printf("You had %d incorrect answers.", i_incorrect);
    }
    printf("\n");

    //number of question missed
    printf("Number of questions missed: %d\n", missedQ);

    return 0;
}