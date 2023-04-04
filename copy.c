#include <stdio.h>
#include <string.h>

#define USAGE "usage: <file1> <file2> [-v] [-f]"
#define VERBOSE_FLAG "-v"
#define FORCE_FLAG "-f"
#define MIN_PARAMETERS 3 // ./copy <file1> <file2>
#define NUM_OF_PARAMS_WITH_ONE_FLAGS 4
#define NUM_OF_PARAMS_WITH_TWO_FLAGS 5
#define TRUE 1
#define FALSE !TRUE

// globals
int verbose = FALSE;
int force = FALSE;


int verboseFlagIsOn(int argc, char** argv);
int forceFlagIsOn(int argc, char** argv);
int isVerboseFlag(const char* flag);
int isForceFlag(const char* flag);


int main(int argc, char** argv)
{
    if (argc < MIN_PARAMETERS)
    {
        printf("%s\n", USAGE);
        return 1;
    }

    verbose = verboseFlagIsOn(argc, argv);
    force = forceFlagIsOn(argc, argv);

    // check (delete it later..)
    printf("verbose is %s\n", verbose ? "on" : "off");
    printf("force is %s\n", force ? "on" : "off");

    return 0;
}


/*
check if at least one argument
is the verbose flag
input: argc and argv main parameters.
output: 1 if '-v' is there, else 0.
*/
int verboseFlagIsOn(int argc, char** argv)
{
    if (argc == NUM_OF_PARAMS_WITH_ONE_FLAGS)
    {
        return isVerboseFlag(argv[3]);
    }
    else if(argc == NUM_OF_PARAMS_WITH_TWO_FLAGS)
    {
        return (isVerboseFlag(argv[3]) || isVerboseFlag(argv[4]));
    }

    return FALSE;
}


/*
check if at least one argument
is the force flag
input: argc and argv main parameters.
output: 1 if '-f' is there, else 0.
*/
int forceFlagIsOn(int argc, char** argv)
{
    if (argc == NUM_OF_PARAMS_WITH_ONE_FLAGS)
    {
        return isForceFlag(argv[3]);
    }
    else if(argc == NUM_OF_PARAMS_WITH_TWO_FLAGS)
    {
        return (isForceFlag(argv[3]) || isForceFlag(argv[4]));
    }

    return FALSE;
}


/*
check if char* is the '-v' flag.
input: flag from main parameters.
output: 1 if it '-v', else 0.
*/
int isVerboseFlag(const char* flag)
{
    if(strlen(VERBOSE_FLAG) == strlen(flag) &&
    strcmp(VERBOSE_FLAG, flag) == 0)
    {
        return TRUE;
    }

    return FALSE;
}


/*
check if char* is the '-f' flag.
input: flag from main parameters.
output: 1 if it '-f', else 0.
*/
int isForceFlag(const char* flag)
{
    if(strlen(FORCE_FLAG) == strlen(flag) &&
    strcmp(FORCE_FLAG, flag) == 0)
    {
        return TRUE;
    }

    return FALSE;
}