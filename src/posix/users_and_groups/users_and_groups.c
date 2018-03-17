#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#define GETOUT(message, value) { perror(message); exit(value);}

int main()
{
    char s[80];
    struct passwd userinfo;
    struct passwd *p = &userinfo, *getpwuid();
    struct group groupinfo;
    struct group *g = &groupinfo, *getgrgid();
    char *strcat(), *strcpy();
    if ((p=getpwuid(getuid())) == NULL)
        GETOUT("Can not access password file",1);
    if ((g=getgrgid(getgid())) == NULL)
        GETOUT("Can not access group file", 2);
    sprintf(s, "USER NAME:%s\tREAL NAME:%s\tGROUP NAME:%s\n", p->pw_name, p->pw_gecos, g->gr_name);
    fprintf(stdout, "%s", s);

    return 0;
}
