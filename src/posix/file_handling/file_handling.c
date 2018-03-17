#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define GETOUT(message, value) { perror(message); exit(value); }
void main(int argc, char** argv)
{
    FILE *fHandle;
    char c;
    char s[127];

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s -option file (option = r, w, a) \n", argv[0]);
        exit(1);
    }

    switch (argv[1][1])
    {
        /* open file for reading */
        case 'r':
        {
            if ( (fHandle = fopen(argv[2], "r")) == NULL)
            {
                sprintf(s, "%s - read error ", argv[0]); GETOUT(s, 2);
            }

            /* close the file */
            if (fclose(fHandle) == EOF)
                GETOUT("error closing file ", 5);

            break;
        }

        /* open file for writing */
        case 'w':
        {
            if ( (fHandle = fopen(argv[2], "w")) == NULL)
            {
                sprintf(s, "%s - write error ", argv[0]); GETOUT(s, 3);
            }

            /* close the file */
            if (fclose(fHandle) == EOF)
                GETOUT("error closing file ", 5);

            break;
        }

        /* open file for appending */
        case 'a':
        {
            if ( (fHandle = fopen(argv[2], "a")) == NULL)
            {
                sprintf(s, "%s - append error ", argv[0]); GETOUT(s, 4);
            }
            fputs("Enter text (terminate with ^D) \n", stdout);

            while ( (c=getc(stdin)) != EOF)
                putc(c, fHandle);

            /* close the file */
            if (fclose(fHandle) == EOF)
                GETOUT("error closing file ", 5);

            /* print contents of file to show append worked */
            fHandle = fopen(argv[2], "r");
            while ( (c=getc(fHandle)) != EOF)
                if (islower(c)) putc(toupper(c), stdout); else putc(c, stdout);

            fclose(fHandle);
            break;
        }

        /* by default, throw an error */
        default:
            fprintf(stderr, "valid options are r, w and a \n");
            exit(5);
    }
    exit(0);
}
