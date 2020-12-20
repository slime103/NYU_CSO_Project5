#include <unistd.h> 
#include <sys/types.h> 
#include <errno.h> 
#include <stdio.h> 
#include <sys/wait.h> 
#include <stdlib.h> 
#include<time.h> 
pid_t pid;
 
int main(int argc, char **argv)
{
  // populate arraay with random numbers
  
  int child_status;
  int i;
    pid = fork();
   if (pid == 0) {
    pid= execve("ProcessPractice",NULL, NULL);
     }
   int num;
 printf("What is 2 + 2" );
  while (num != 4) {
   scanf("%d", &num); 
   if (num==4) {
           printf("You win                    \n" );    
           kill(pid, SIGKILL);
      } else if (num==0) {
               kill(pid, SIGINT);
               printf("%i resetting time       ",num);     
               printf("\r\b\r");  
   
          }  else {
                   printf("%i incorrect - try again ",num);   
                   printf("\r\b\r");
              }
      
   }
   return(0);
   }

  
