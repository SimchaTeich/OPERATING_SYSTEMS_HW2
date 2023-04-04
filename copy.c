#include <stdio.h>
#include <string.h>

#define USAGE "usage: <file1> <file2> [-v] [-f]"
#define VERBOSE_FLAG "-v"
#define FORCE_FLAG "-f"
#define MIN_PARAMETERS 3 // ./copy <file1> <file2>
#define TRUE 1
#define FALSE !TRUE

// globals
int verbose = FALSE;
int force = FALSE;


int verboseIsOn(const char* flag);


int main(int argc, char** argv)
{
    if (argc < MIN_PARAMETERS)
    {
        printf("%s\n", USAGE);
        return 1;
    }

    if(argc > MIN_PARAMETERS)
    {
        verbose = verboseIsOn(argv[3]);
        printf("verbose is %s\n", verbose ? "on" : "off");
    }
    return 0;
}


/*
check if char* is the '-v' flag
input: flag from main parameters.
output: 1 if it '-v', else 0.
*/
int verboseIsOn(const char* flag)
{
    if(strlen(VERBOSE_FLAG) == strlen(flag) &&
    strcmp(VERBOSE_FLAG, flag) == 0)
    {
        return TRUE;
    }

    return FALSE;
}