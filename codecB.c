#include "codecB.h"
#include <string.h>
#include <stdio.h>


void codecB(char * str, int operation)
{
    if(operation == ENCODE)
    {
        encode(str);
    }
    else if(operation == DECODE)
    {
        decode(str);
    }
}


void encode(char* str)
{
    size_t len = strlen(str);

    for(size_t i = 0; i < len; i++)
    {
        str[i] = (str[i] - CONTROL_CHARTACTERS + 3) % AVAILABLE_CHARS_FROM_KEYBOARD + CONTROL_CHARTACTERS;
    }
}


void decode(char* str)
{
    size_t len = strlen(str);

    for(size_t i = 0; i < len; i++)
    {
        str[i] = (str[i] - CONTROL_CHARTACTERS + 92) % AVAILABLE_CHARS_FROM_KEYBOARD + CONTROL_CHARTACTERS;
    }
}