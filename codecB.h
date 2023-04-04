#define TRUE 1
#define FALSE !TRUE
#define ENCODE 1
#define DECODE 2


/*
 convert all chars to the 3-rd next char
 (adding a number of 3 to the ascii val)
*/
void codecB(char * str, int operation);


void encode(char* str);

void decode(char* str);


