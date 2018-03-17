#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern char **environ;

int main()
{
    char str[20], Variable[20], Value[20];
    char *getenv();
    char **t;

    fprintf(stdout, "CURRENT ENVIRONMENT VARIABLES\n");
    for (t = environ; *t != NULL; t++)
        fprintf(stdout, "%s\n", *t);

    fprintf(stdout, "\nSpecify a variable name ? > ");
    fgets(Variable, 20 , stdin);
    fprintf(stdout, "The variable value is %s\n", getenv(Variable));
    fprintf(stdout, "Specify a new value ? > ");
    fgets(Value, 20, stdin);
    strcpy(str,Variable); strcat(str,"="); strcat(str,Value); putenv(str);
    fprintf(stdout, "The variable value is %s\n", getenv(Variable));

    return 0;
}
