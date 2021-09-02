#include <errno.h>
#include <stdio.h>
#include <string.h>

//Funciton for handling system call errors
//
//  @param errnoVal - This should be the errno that comes from errno.h
//  @param errmsg   - This is the string that you want printed in your message
//
void sysCallFailed(int errnoVal, char *errmsg)
{
    int errnum = errnoVal;
    printf("%s.  Value of errno: %d\n", errmsg, errnoVal);
    perror("Error printed by perror.");
    printf("%s: %s\n.", errmsg, strerror(errnum)); 
}
