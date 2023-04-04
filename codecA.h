#define TRUE 1
#define FALSE !TRUE


/*
convert all lower case to upper case,
and all upper case to lower case.
input: string as char*
*/
void codecA(char* str);


/*
checks if char is lower case
input: char
iutput: 1 if yes, else 0.
*/
int islower(char c);


/*
convert char to be lower case
input: char
output: same char in lower case
*/
char lower(char c);


/*
convert char to be upper case
input: char
output: same char in upper case
*/
char upper(char c);
