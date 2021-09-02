#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#include "ErrorHandling.h"

#define BUFFER_SIZE 1024

// Global Variables
int pipefds[2];
int status, pid;
char writemessage[BUFFER_SIZE];
char readmessage[BUFFER_SIZE];


int pipeOperation()
{
   pid = fork();

   // Child Process to Read the Data.
    if(pid == 0)
    {
        status = read(pipefds[0], readmessage, sizeof(readmessage));

        if (status == -1)
        {
            sysCallFailed(errno, "Unable to read from pipe.");
            return -1;
        }    
        printf("Child Process: Reading from pipe – Message is %s", readmessage);
   }
   else
   {  // Parent Process to write the data.
       printf("Parent Process: Writing to pipe - Message is %s", writemessage);
       status = write(pipefds[1], writemessage, sizeof(writemessage));

       if (status == -1)
       {
           sysCallFailed(errno, "Unable to write to pipe.");
           return -1;
       }
   }

   return 0;
}

int main() 
{  
  status = pipe(pipefds);
  
  if (status == -1) 
  {
     sysCallFailed(errno, "Unable to create pipe");
     return 1;
  }
  
  printf("Enter the message to write into Pipe\n");
  printf("To exit type \"quit\" \n");
  
  fgets(writemessage, BUFSIZ, stdin);
  
  while (strcmp(writemessage, "quit\n") != 0) 
  {
       pipeOperation();
       fgets(writemessage, BUFSIZ, stdin);
       kill(pid, SIGKILL); // Killing
   }
  
  return 0;
}
