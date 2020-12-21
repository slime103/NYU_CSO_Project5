/*
*
*   Author - Zachary Stephens
*
* Compile with gcc -Wall problem2p.c -o problem2p
*
* IMPORTANT NOTE: Make sure problem2c.c is compiled first before compiling
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
    printf("Out of Time! Enter any number to continue.\n");
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
    int correct = 0;

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

        //Create Child process / Timer
        if ((pid = fork()) == 0)
        {
            pid = execve("problem2c", NULL, NULL);
        }

        printf("What is %d %c %d ?\n", n1, charOp, n2);

        while (input != answer)
        {
            //Get Input
            scanf("%d", &input);

            if (outOfTime)
            {
                kill(pid, SIGINT);
                outOfTime = 0;
                break;
            }

            if (input == answer)
            {
                correct++;
                printf("Correct!\n");

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

        kill(pid, SIGKILL);
    }

    //print correct answers

    printf("Correct Answers:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", answers[i]);
    }
    printf("\nYou had %d correct answers.\n", correct);

    //print incorrect answers

    printf("Incorrect Answers:\n");
    for (int k = 0; k < i_incorrect; k++)
    {
        printf("%d, ", incorrect[k]);
    }
    printf("\nYou had %d incorrect answers.\n", i_incorrect);

    //number of question missed
    printf("Number of questions missed: %d\n", missedQ);

    return 0;
}