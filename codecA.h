#define TRUE 1
#define FALSE !TRUE


/*
convert all lower case to upper case,
and all upper case to lower case.
input: string as char*
*/
void encode(char* str);


/*
actualy do the same as encode(),
so it call it with param str...
input: string as char*
*/
void decode(char* str);


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
