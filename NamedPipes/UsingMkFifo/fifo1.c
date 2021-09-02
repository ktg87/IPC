// C Program to implement one side of FIFO
// This is the side that writes first, then reads (i.e. Client)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFF_MAX  80
#define PATH_MAX 4096
#define FIFO_FILE "FIFO"

int main()
{

    int file_descriptor;
    int status;
    extern int errno;
    //File path to the FIFO file
    char cwd[PATH_MAX];
    if(getcwd(cwd, sizeof(cwd)) == NULL)
    {
        printf("Failed to get cwd");
        return 1;
    }

    int fullpathLen = strlen(cwd) + strlen(FIFO_FILE) + 2;
    char *fullpath = (char *)malloc(fullpathLen);
    if (fullpath == NULL)
    {
        printf("Failed to allocate memory for fullpath.");
        return 1;
    }

    strncat(fullpath, cwd, strlen(cwd));
    strncat(fullpath, "/", 1);
    strncat(fullpath, FIFO_FILE, strlen(FIFO_FILE));
    printf("fullpath with just cwd: %s\n", fullpath);

    free(fullpath);

    // Creating the special FIFO file
    umask(0);
    mkfifo(fullpath, S_IFIFO|0666);

    char writemessage[BUFF_MAX], readmessage[BUFF_MAX];
    while (1)
    {
        // open our special FIFO file with write only permissions
        file_descriptor = open(fullpath, O_CREAT|O_WRONLY);

        if (file_descriptor == -1)
        {
            printf("Something went wrong with open: %s\n", strerror(errno));
            return 1;
        }
        printf("Enter something that you would like to write.\n");

        // User's input
        fgets(writemessage, sizeof(writemessage), stdin);

        printf("Writemessage: %s\n", writemessage);
        // Write the user's input to the FIFO file
        status = write(file_descriptor, writemessage, strlen(writemessage)+1);
        if(status == -1)
        {

            printf("Something went wrong with the write: %d\n", errno);
            printf("Here is the error message: %s\n", strerror(errno));
        }
        close(file_descriptor);
        printf("Closing FIFO file after write...\n");

        // Read the special FIFO file
        file_descriptor = open(fullpath, O_RDONLY);

        read(file_descriptor, readmessage, sizeof(readmessage));
        
        // Print the message
        printf("User: %s\n", readmessage);

        close(file_descriptor);
    }

    return 0;

}
