/*
- Created by Sari on 04/04/2023.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int ignorCase(char a,char b);
int compare_tow_BFiles(FILE *f1,FILE *f2 )



int main(int argc ,char *argv[])
{







return EXIT_SUCCESS;
}
int ignorCase(char a,char b)
{
    int value =abs(a-b);
    if(value==32)
    {
        return 1;
    }
        return -1;
}

int compare_tow_BFiles(FILE *f1,FILE *f2 )
{
   char ch0,ch1;
   int check;

    while ((ch0=fgetc(f1))!=EOF  && (ch1=fgetc(f2))!=EOF)
    {
            if((ch0==ch1) || (ignorCase(ch0, ch1)==1))//here i don't know if there need
                                                            // of ignorCase option  check it
            {
                // if equal just continue until arrive to end of file
                check =1;
                continue;
            } else
            {
                // if not equal shut down and stop while loop
                fseek(f1,-1,SEEK_CUR);
                check =0;
                break;

            }
    }
    return check;
}