#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#define GETOUT(message, value) { perror(message); exit(value); }

int main(int argc, char *argv[])
{
    char *ctime();
    /* generates time string from output of time() */
    struct stat statdata; /* Inode structure definition */
    char s[127];

    if (argc != 2)
    {
        sprintf(s, "Usage: %s filename", argv[0]); GETOUT(s,1);
    }

    if (stat(argv[1], &statdata) == -1)
    {
        sprintf(s,"Unable to obtain the status of %s", argv[1]);
        GETOUT(s,2);
    }

    fprintf(stdout, "\nFile %s is a ", argv[1]);
    switch (statdata.st_mode & S_IFMT)
    {
        case S_IFREG : fprintf(stdout, "Regular file \n"); break;
        case S_IFDIR : fprintf(stdout, "Directory file \n"); break;
        case S_IFCHR : fprintf(stdout, "Character special file \n");break;
        case S_IFBLK : fprintf(stdout, "Block special file \n"); break;
    }

    fprintf(stdout, "\nuser-id %d, ", statdata.st_uid);
    fprintf(stdout, "group-id %d, ", statdata.st_gid);
    fprintf(stdout, "permissions %o, ", statdata.st_mode);
    fprintf(stdout, "link(s) %d \n", (int)statdata.st_nlink);
    fprintf(stdout, "size %d (bytes), ", (int)statdata.st_size);
    fprintf(stdout, "%d (blocks), ", (int)statdata.st_blocks);
    fprintf(stdout, "Inode # %d \n\n", (int)statdata.st_ino);
    fprintf(stdout, "Time %s data was last read or modified:-\t%s",
        argv[1], ctime(&statdata.st_atime));
    fprintf(stdout, "Time %s data was last read or modified:-\t%s",
        argv[1], ctime(&statdata.st_atime));
    fprintf(stdout, "Time %s data was last modified:-\t\t%s",
        argv[1], ctime(&statdata.st_mtime));
    fprintf(stdout, "Time %s status was last changed:-\t\t%s",
        argv[1], ctime(&statdata.st_ctime));
    fprintf(stdout, "\nRead permission ");
    fprintf(stdout, (access(argv[1], R_OK) == 0) ? "granted\n" : "denied\n");
    fprintf(stdout, "Write permission ");
    fprintf(stdout, (access(argv[1], W_OK) == 0) ? "granted\n" : "denied\n");
    fprintf(stdout, "eXecute/search permission ");
    fprintf(stdout, (access(argv[1], X_OK) == 0) ? "granted\n" : "denied\n");
    return 0;
}
