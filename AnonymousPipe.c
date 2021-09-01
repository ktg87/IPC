#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 1024

// Global Variables
int pipefds[2];
int status;
char writemessage[BUFFER_SIZE];
char readmessage[BUFFER_SIZE];
extern int errno;

//Funciton for handling system call errors
void sysCallFailed(int errnoVal, char *errmsg)
{
    int errnum = errnoVal;
    printf("%s.  Value of errno: %d\n", errmsg, errnoVal);
    perror("Error printed by perror.");
    printf("%s: %s\n.", errmsg, strerror(errnum)); 
}

// pipeOperation() to perform read and write Operations.
int pipeOperation()
{  

    printf("Writing to pipe - Message is %s", writemessage);
    status = write(pipefds[1], writemessage, sizeof(writemessage));
    
    if(status == -1)
    {
        sysCallFailed(errno, "Unable to write to pipe");    
        return -1;
    }

    status = read(pipefds[0], readmessage, sizeof(readmessage));
    printf("Reading from pipe – Message is %s", readmessage);
    
    if(status == -1)
    {
        sysCallFailed(errno, "Unable to read from pipe");
        return -1;
    }

    return 0;
}

int main() 
{
  status = pipe(pipefds);
  int errnum;

  if (status == -1) 
  {
     errnum = errno; 
     printf("Unable to create pipe.  Value of errno: %d\n", errno);
     perror("Error printed by perror");
     printf("Error creating pipe: %s\n", strerror(errnum));
     return 1;
  }
  
  printf("Enter the message to write into Pipe\n");
  printf("To exit type \"quit\" \n");
  
  fgets(writemessage, BUFSIZ, stdin);

  // This loop is used to take continuous Standard input.
  while (strcmp(writemessage, "quit\n") != 0) 
  { 
    status = pipeOperation();

    if(status == -1)
    {
        goto fail;
    }

    fgets(writemessage, BUFSIZ, stdin);
   }
  
fail:  
  printf("Closing pipe.\n");
  close(pipefds[0]);
  close(pipefds[1]);
  
  return 0;
}
