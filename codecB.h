#define TRUE 1
#define FALSE !TRUE
#define ENCODE 1
#define DECODE 2
#define CONTROL_CHARTACTERS 32 //that chartacters they cant reach by desktop, we add it after
                              // calc thr modulu to pass control chartacters
#define AVAILABLE_CHARS_FROM_KEYBOARD 95 // 95+32-1= "126"- maximum range for ascii values 
                                        //  that can get by desktop.

/*
  main programe for encode/decode 
*/
void codecB(char * str, int operation);
/*
 convert all chars to the 3-rd next char
*/
void encode(char* str);
/*
convert all chars to the original appearance before encode char 
or convert all chars to the 3-rd back char
*/
void decode(char* str);


