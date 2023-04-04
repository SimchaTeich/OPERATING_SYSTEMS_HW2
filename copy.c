#include <stdio.h>
#include <string.h>
#include <unistd.h> // not working in windous! this is for access().

#define USAGE "usage: <file1> <file2> [-v] [-f]"
#define SUCCESS_MSG "success"
#define TERGET_ERROR_MSG "target file exist"
#define GENERAL_ERROR_MSG "general failure"
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

// functions
int flagIsOn(int argc, char** argv, const char* flag);
int stringsAreEquals(const char* str1, const char* str2);
int fileIsExist(char* filename);
int copyFile(char* src_filename, char* dst_filename);


int main(int argc, char** argv)
{
    char* src_filename = NULL;
    char* dst_filename = NULL;

    if (argc < MIN_PARAMETERS)
    {
        printf("%s\n", USAGE);
        return 1;
    }

    src_filename = argv[1];
    dst_filename = argv[2];

    // update globals about the flag status.
    verbose = flagIsOn(argc, argv, VERBOSE_FLAG);
    force = flagIsOn(argc, argv, FORCE_FLAG);

    // exit if destination file is not exist and
    // if force flag is off.
    if(fileIsExist(dst_filename) && !force)
    {
        if(verbose){ printf("%s\n", TERGET_ERROR_MSG); }
        return 1;
    }

    // copy src file to dst file.
    copyFile(src_filename, dst_filename);


    if (verbose) { printf("%s\n", SUCCESS_MSG); }
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


/*
check if file is exist.
input: file name as char*
output: 1 for yes, else 0.

https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c
*/
int fileIsExist(char* filename)
{
    return access(filename, F_OK) == 0 ? TRUE : FALSE; 
}


/*
copy content of src file to dst file (binary mode)
input: two file names as char*
output: 0 for success, else 1
*/
int copyFile(char* src_filename, char* dst_filename)
{
    size_t file_size = 0;
    char byte[1] = {0};

    // open src file
    FILE* src_file = fopen(src_filename, "rb");
    if(src_file == NULL)
    {
        if(verbose){ printf("%s\n", GENERAL_ERROR_MSG); }
        _exit(1);
    }

    // open dst file
    FILE* dst_file = fopen(dst_filename, "wb");
    if(dst_file == NULL)
    {
        fclose(src_file);
        if(verbose){ printf("%s\n", GENERAL_ERROR_MSG); }
        _exit(1);
    }

    // get the file size;
    fseek(src_file, 0, SEEK_END);
    file_size = ftell(src_file);
    fseek(src_file, 0, SEEK_SET);

    // copy the file.
    for(size_t i = 0; i < file_size; i++)
    {
        fread(byte, sizeof(char), 1, src_file);
        fwrite(byte, sizeof(char), 1, dst_file);
    }

    fclose(src_file);
    fclose(dst_file);

    return 0;
}