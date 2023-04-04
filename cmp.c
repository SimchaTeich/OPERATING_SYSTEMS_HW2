/*
- Created by Sari on 04/04/2023.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define USAGE "usage: <file1> <file2> [-v] [-i]"
#define MIN_PARAMETERS 3 // ./copy <file1> <file2>
#define VERBOSE_FLAG "-v"
#define IGNORE_FLAG "-i"
#define TRUE 1
#define FALSE !TRUE
#define NUM_OF_PARAMS_WITH_ONE_FLAGS 4
#define NUM_OF_PARAMS_WITH_TWO_FLAGS 5
// globals
int verbose = FALSE;
int ignore = FALSE;
// function in use
int ignoreCase(char a, char b);
int compare_tow_BFiles(FILE *f1, FILE *f2);

int main(int argc, char *argv[])
{
    FILE *file;
    FILE *file1;
    if (argc < MIN_PARAMETERS)
    {
        printf("%s\n", USAGE);
    }
    // we began with right parameters
    else
    {
        // <filename1> <filename2>
        // argv[1]     argv[2]
        file = fopen(argv[1], "rb");
        if (file == NULL)
        {
            printf("\n Error in opening file or file doesnt exist%s %d", argv[1], 1);
            fclose(file);
            _exist(1); // FAIL
        }
        file1 = fopen(argv[2], "rb");
        if (file1 == NULL)
        {
            printf("\n Error in opening file or file doesnt exist%s %d", argv[2], 1);
            fclose(file1);
            _exist(1); // FAIL
        }

        // update globals about the flag status.
        verbose = flagIsOn(argc, argv, VERBOSE_FLAG);
        ignore = flagIsOn(argc, argv, IGNORE_FLAG);
        if (verbose)
        {
            if (compare_tow_Vcase_BFiles(file, file1) == 1)
            {
                printf("\n equal %d", 1);
            }
            else
            {
                printf("\n distinct %d", 0);
            }
        }
        if (ignore)
        {
            if (compare_tow_Icase_BFiles(file, file1) == 1)
            {
                printf("\n equal %d", 1);
            }
            else
            {
                printf("\n distinct %d", 0);
            }
        }
    }
    return 0;
}
/*
 * “ignore case” so “AAA” and “aaa” meaning equals
 */
int ignoreCase(char a, char b)
{
    // extract ascii value
    int ascii_a = (int)a;
    int ascii_b = (int)b;
    // the range define the upper and lower case
    int value = abs(ascii_a - ascii_b);
    if (value == 32)
    {
        return 1;
    }
    return -1;
}

int compare_tow_Icase_BFiles(FILE *f1, FILE *f2)
{
    char ch0, ch1;
    int check;

    while (((ch0 = fgetc(f1)) != EOF) && ((ch1 = fgetc(f2)) != EOF))
    {
        // in this condition need to think again if can to use "ignoreCase"
        // just need define "-i" flag or don't care about this
        if ((ch0 == ch1) || (ignoreCase(ch0, ch1) == 1))
        {
            // if equal just continue until arrive to end of file
            check = 1;
            continue;
        }
        else
        {
            // if not equal shut down and stop while loop
            fseek(f1, -1, SEEK_CUR);
            check = 0;
            break;
        }
    }
    fclose(f1);
    fclose(f2);
    return check;
}
int compare_tow_Vcase_BFiles(FILE *f1, FILE *f2)
{
    char ch0, ch1;
    int check;

    while (((ch0 = fgetc(f1)) != EOF) && ((ch1 = fgetc(f2)) != EOF))
    {
        if ((ch0 == ch1))
        {
            // if equal just continue until arrive to end of file
            check = 1;
            continue;
        }
        else
        {
            // if not equal shut down and stop while loop
            fseek(f1, -1, SEEK_CUR);
            check = 0;
            break;
        }
    }
    fclose(f1);
    fclose(f2);
    return check;
}
/*
check if at least one argument is a flag.
input: argc and argv main parameters, and flag.
output: 1 if flag was found, else 0.
*/
int flagIsOn(int argc, char **argv, const char *flag)
{
    if (argc == NUM_OF_PARAMS_WITH_ONE_FLAGS)
    {
        return stringsAreEquals(argv[3], flag);
    }
    else if (argc == NUM_OF_PARAMS_WITH_TWO_FLAGS)
    {
        return (stringsAreEquals(argv[3], flag) || stringsAreEquals(argv[4], flag));
    }

    return FALSE;
}