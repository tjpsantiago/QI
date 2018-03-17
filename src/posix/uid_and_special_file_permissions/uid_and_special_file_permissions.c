#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/fcntl.h>
#include <unistd.h>

void info(char * message, int uid);

int main(int argc, char **argv)
{
    struct stat inodedata;
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s char (char = e or r)\n", argv[0]);
        exit(1);
    }

    /* create file, grant owner full access and get its details */
    close(open("TestFile",O_CREAT,0644));
    chmod("TestFile",0700);
    stat("TestFile",&inodedata);
    fprintf(stdout, "\nUID of the owner of TestFile is %d\n", inodedata.st_uid);
    system("ls -l TestFile");

    switch (argv[1][0])
    {
        case 'e':
            info("Set real & effective UID to effective UID", geteuid());
            break;
        case 'r':
            info("Set real & effective UID to real UID", getuid());
            break;
        default :
            fprintf(stderr, "invalid arguments \n" "valid arguments are:- e or r\n");
            break;
    }
    return 0;
}

/* List UID info after setuid change and then attempt to access file */
void info(char * message, int uid)
{
    int fd;
    if (setuid(uid) == -1)
    {
        fprintf(stderr, "Unable to set new user identifier\n");
    }
    else
    {
        fprintf(stdout, "\n%s\n", message);
        fprintf(stdout, "UID = %d and effective UID = %d\n", getuid(), geteuid());
        fprintf(stdout, "\nOpening TestFile - ");

        if ((fd=open("TestFile", O_RDONLY))== -1)
            fprintf(stderr, "Not allowed to open file\n");
        else
            close(fd); fprintf(stdout, "Closed TestFile\n");
    }
}
