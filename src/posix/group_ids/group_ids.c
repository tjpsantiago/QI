#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int i, n, groups[NGROUPS];
    if ( (n = getgroups(NGROUPS, &groups[0])) == -1 )
    {
        fprintf(stderr, "Unable to discover the group-ids for this account\n");
    }
    else
    {
        fprintf(stdout, "Group-ids for this account are: ");
        for (i=0; i < n; i++)
            fprintf(stdout, (i+1 == n) ? "%d\n" : "%d ", groups[i]);
    }
    return 0;
}
