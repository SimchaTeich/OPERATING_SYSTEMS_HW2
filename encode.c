#include <dlfcn.h>   // dlopen
#include <stdio.h>
#include <string.h>
#include <unistd.h>  // not working in windous! this is for _exit(1)


#define USAGE "usage: encode <codec> <message>"
#define NUM_OF_ARGS 3
#define TRUE 1
#define FALSE !TRUE

void printUsage();

void (*encode)(char *);


/*
load dynamicly the correct libary,
and then take the function encode from there.
input: name of libary, "codecA" or "codecB" only.
*/
int init_library(char* libname)
{
    void *hdl = NULL;

    if(strlen(libname, "codecA") == 0)
    {
        *hdl = dlopen("libcodecA.so", RTLD_LAZY);
    }
    else ifstrlen(libname, "codecB") == 0
    {
        *hdl = dlopen("libcodecB.so", RTLD_LAZY);
    }

	if (NULL == hdl)
		return FALSE;
	encode = (void(*)(char *))dlsym(hdl,"encode");
	if (NULL == encode)
		return FALSE;
	return TRUE;
}



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

    if(init_library(codec))
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
