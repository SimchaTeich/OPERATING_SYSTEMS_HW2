/*
- Created by Sari on 04/04/2023.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define USAGE "usage: <file1> <file2> [-v] [-i]"
#define MIN_PARAMETERS 3 // ./copy <file1> <file2>

int ignoreCase(char a,char b);
int compare_tow_BFiles(FILE *f1,FILE *f2 );

int main(int argc ,char *argv[])
{

    int result;
    File* file;
    File* file1;
    if (argc<MIN_PARAMETERS)
    {
        printf("%s\n", USAGE);
    }
     //we began with right parameters
    else
    {
        // <filename1> <filename2> flag
        // argv[0]     argv[1]
        file = fopen(argv[0],"r");
        if (file == NULL) {
            printf("\nError in opening file or file doesnt exist %s", argv[0]);
            return;
        }
        file1 = fopen(argv[1], "r");
        if (file1 == NULL) {
            printf("\nError in opening file or file doesnt exist %s", argv[1]);
            return;
        }
        if ((file != NULL) && (file1 != NULL)) {
            // 1 -> equals /(-1) -> not equal
            result = compare_tow_BFiles(file, file1);
        }
    }
return EXIT_SUCCESS;
}
int ignoreCase(char a,char b)
{
    // extract ascii value
    int ascii_a = (int)a;
    int ascii_b = (int)b;
    // the range define the upper and lower case
    int value =abs(ascii_a-ascii_b);
    if(value==32)
    {
        return 1;
    }
        return -1;
}

int compare_tow_BFiles(FILE* f1,FILE* f2 )
{
   char ch0,ch1;
   int check;

    while ((ch0=fgetc(f1))!=EOF)  && (ch1=fgetc(f2))!=EOF))
    {
        // in this condition need to think again if can to use "ignoreCase"
       // just need define "-i" flag or don't care about this
            if((ch0==ch1) || (ignoreCase(ch0, ch1)==1))
            {
                // if equal just continue until arrive to end of file
                check= 1;
                continue;
            }
            else
            {
                // if not equal shut down and stop while loop
                fseek(f1,-1,SEEK_CUR);
                check =0;
                break;
            }
    }
    return check;
}