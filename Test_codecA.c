#include <stdio.h>
#include "codecA.h"

int main()
{
    char str[] = "abcd_1234567890@@@_EFGH";

    printf("str before codecA: %s\n", str);
    codecA(str);
    printf("str after codecA: %s\n", str);
    codecA(str);
    printf("str after codecA again: %s\n", str);

    return 0;
}