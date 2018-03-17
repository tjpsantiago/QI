#include <sys/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#define GETOUT(message, value) { perror(message); exit(value); }

int main()
{
    char filename[40], *fnptr=filename;
    int fd, pid, ppid;
    system("ps lg | tail");

    /* list processes running on terminal */
    pid=getpid(); ppid=getppid();

    /* get process id's */
    fprintf(stdout, "\nThe current process ID is %d", pid);
    fprintf(stdout, " and its parent process ID is %d\n\n", ppid);
    sprintf(fnptr, "/tmp/unique%d", pid);
    /* make file name */
    if ((fd=open(fnptr, O_CREAT, 0644)) <0)
    {
        GETOUT("unable to create temporary file\n", 1)
    }
    else
    {
        fprintf(stdout, "Opened file %s\n", fnptr);
        system("ls -l /tmp | grep unique");
        close(fd);
        unlink(fnptr);
        fprintf(stdout, "\nClosed and deleted file %s\n", fnptr);
    }
    return 0;
}
