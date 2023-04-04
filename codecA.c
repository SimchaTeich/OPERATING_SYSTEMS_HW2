#include "codecA.h"
#include <string.h>
#include <ctype.h> // islower


void codecA(char* str)
{
    size_t len = strlen(str);
    for(size_t i = 0; i < len; i++)
    {
        if(islower((int)str[i])){ str[i] = upper(str[i]); }
        else{ str[i] = lower(str[i]); }
    }
}


char lower(char c)
{
    if('A' <= c && c <= 'Z')
    {
        c += ('a' - 'A');
    }

    return c;
}


char upper(char c)
{
    if('a' <= c && c <= 'z')
    {
        c -= ('a' - 'A');
    }

    return c;
}
