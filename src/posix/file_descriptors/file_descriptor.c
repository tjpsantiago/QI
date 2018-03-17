#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // for chmod
#include <sys/file.h>
#include <sys/fcntl.h>
#include <unistd.h>

#define GETOUT(message, value) { perror(message); exit(value); }

int main() {
    int fd, c, buffer[128];
    chdir("/tmp");

    if (access("scribble", F_OK) == 0)
        unlink("scribble");

    if (access("scribblecopy", F_OK) == 0)
        unlink("scribblecopy");

    if (( fd = open("scribble", O_CREAT | O_RDWR, 0644 )) == -1)
        GETOUT("Unable to open scratch file ", 1);

    if (link("scribble", "scribblecopy") != 0)
        GETOUT("Unable to create link to scratch file", 2);

    chmod("scribble", 0700);
    chmod("scribblecopy", 0600);
    strcpy((char*)buffer, "Enter text (terminate with a ^D) \n");
    write(1, buffer, strlen((const char*)buffer));

    while ( (c = read(0, buffer, 127)) != 0)
        write(fd, buffer, c);
    lseek(fd, 3, 0);

    /* rewinds to 4th byte from start */
    write (fileno(stdout), buffer, read(fd, buffer, 127));
    close(fd);

    return 0;
}
