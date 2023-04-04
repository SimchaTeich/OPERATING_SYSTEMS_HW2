/*
- Created by Sari on 04/04/2023.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int ignorCase(char a,char b);


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

void compare_tow_BFiles(FILE *f1,FILE *f2 )
{
   char ch0,ch1;

    while ((ch0=fgetc(f1))!=EOF  && (ch1=fgetc(f2))!=EOF)
    {

    }



}