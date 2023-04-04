#include <stdio.h>

#define USAGE "usage: <file1> <file2> [-v] [-f]"
#define MIN_PARAMETERS 3 // ./copy <file1> <file2>


int main(int argc, char** argv)
{
    if (argc < MIN_PARAMETERS)
    {
        printf("%s\n", USAGE);
    }

    return 0;
}