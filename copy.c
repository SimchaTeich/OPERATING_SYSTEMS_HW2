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

int flagIsOn(int argc, char** argv, const char* flag);
int stringsAreEquals(const char* str1, const char* str2);


int main(int argc, char** argv)
{
    if (argc < MIN_PARAMETERS)
    {
        printf("%s\n", USAGE);
        return 1;
    }

    verbose = flagIsOn(argc, argv, VERBOSE_FLAG);
    force = flagIsOn(argc, argv, FORCE_FLAG);

    // check (delete it later..)
    printf("verbose is %s\n", verbose ? "on" : "off");
    printf("force is %s\n", force ? "on" : "off");

    return 0;
}


/*
check if at least one argument is a flag.
input: argc and argv main parameters, and flag.
output: 1 if flag was found, else 0.
*/
int flagIsOn(int argc, char** argv, const char* flag)
{
    if (argc == NUM_OF_PARAMS_WITH_ONE_FLAGS)
    {
        return stringsAreEquals(argv[3], flag);
    }
    else if(argc == NUM_OF_PARAMS_WITH_TWO_FLAGS)
    {
        return (stringsAreEquals(argv[3], flag) || stringsAreEquals(argv[4], flag));
    }

    return FALSE;
}


/*
check if two strings (char*) are equals
input: two char*
output: 1 if strings are equals, else 0.
*/
int stringsAreEquals(const char* str1, const char* str2)
{
    if(strlen(str1) == strlen(str2) &&
    strcmp(str1, str2) == 0)
    {
        return TRUE;
    }

    return FALSE;
}
