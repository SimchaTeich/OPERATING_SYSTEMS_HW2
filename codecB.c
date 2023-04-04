#include "codecB.h"
#include <string.h>
#include <stdio.h>


void codecB(char *str)
{
   int length = strlen(str);
    //  each character in the string add 3 and if its out of range 
    for (int i = 0; i < length; i++) 
    {
        // Add 3 to the ASCII value of the current character
        // we calculate with modulo didnt be out of range 
        str[i] = (str[i] + 3)%256;
    }
}