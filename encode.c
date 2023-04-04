#include <stdio.h>
#include <string.h>
#include <unistd.h> // not working in windous! this is for _exit(1)
#include "codecA.h"
#include "codecB.h"

#define USAGE "usage: encode <codec> <message>"
#define NUM_OF_ARGS 3
#define CODEC_A "codecA"
#define CODEC_B "codecB"
#define TRUE 1
#define FALSE !TRUE

void printUsage();
int stringsAreEquals(const char* str1, const char* str2);


int main(int argc, char** argv)
{
    char* codec = NULL;
    char* msg = NULL;

    if(argc != NUM_OF_ARGS)
    {
        printUsage();
        return 1;
    }

    // get the main parameters.
    codec = argv[1];
    msg = argv[2];

    // run code A on message
    if(stringsAreEquals(codec, CODEC_A))
    {
        codecA(msg);
        printf("%s\n", msg);
    }
    // run code B on message
    else if(stringsAreEquals(codec, CODEC_B))
    {
        encode(msg);
        printf("%s\n", msg);
    }
    else
    {
        printUsage();
        return 1;
    }
    
    return 0;
}


/*
print the usage of this program
*/
void printUsage()
{
    printf("%s\n", USAGE);
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
