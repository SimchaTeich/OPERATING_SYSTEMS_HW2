/*
- Created by Sari on 04/04/2023.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int compare_tow_Icase_BFiles(FILE *f1, FILE *f2);
int compare_tow_Vcase_BFiles(FILE *f1, FILE *f2);
int flagIsOn(int argc, char **argv, const char *flag);
int stringsAreEquals(const char *str1, const char *str2);
int two_cases(int v, int i);

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
            exit(1); // FAIL
        }
        file1 = fopen(argv[2], "rb");
        if (file1 == NULL)
        {
            printf("\n Error in opening file or file doesnt exist%s %d", argv[2], 1);
            fclose(file1);
            exit(1); // FAIL
        }

        // update globals about the flag status.
        verbose = flagIsOn(argc, argv, VERBOSE_FLAG);
        ignore = flagIsOn(argc, argv, IGNORE_FLAG);

        if (two_cases(ignore, verbose) == 1)
        {
            if (compare_tow_Icase_BFiles(file, file1) == 1)
            {
                printf("\n equal \n");
                return 1;
            }
            else
            {
                printf("\n distinct \n");
                return 0;
            }
        }

        if (verbose)
        {
            if (compare_tow_Vcase_BFiles(file, file1) == 1)
            {
                printf("\n equal\n");
                return 1;
            }
            else
            {
                printf("\n distinct\n");
                return 0;
            }
        }
        if (ignore)
        {
            if (compare_tow_Icase_BFiles(file, file1) == 1)
            {
                printf("\n equal \n");
                return 1;
            }
            else
            {
                printf("\n distinct \n");
                return 0;
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
        // just need define "-i"
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
        if (ch0 == ch1)
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
check if two strings (char*) are equals
input: two char*
output: 1 if strings are equals, else 0.
*/
int stringsAreEquals(const char *str1, const char *str2)
{
    if (strlen(str1) == strlen(str2) &&
        strcmp(str1, str2) == 0)
    {
        return TRUE;
    }

    return FALSE;
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

// to define the case e have two pararmiters (i, v)
int two_cases(int v, int i)
{

    int result = v + i;
    if (result == 2)
    {
        return 1;
    }
    return 0;
}
