# OPERATING_SYSTEMS_HW2
## Home Work 2 - Shell
### The task is made of 3 parts: files operations, dynamic libraries, and basic shell
# Part A:
small programs, that fills like a regular CMD tools.
Tool 1: “cmp”


the tool will compare two files, and return “0” if they are equal, and “1” if not (return an INT).
The tool will support -v flag for verbose output. By this we mean that the tool will print “equal” or
“distinct”, in addition to returning the int value.
The toll will support -i flag, that mean “ignore case” so “AAA” and “aaa” meaning equals
usage: cmp <file1> <file2> -v
output: equal
Tool 2: “copy”, the tool will copy a file to another place and/or name.
The tool will return “0” on success, or “1” on failure (return an INT)
The tool will create a new file, if it does not exist, but it will not overwrite a file if it do exist.
the tool will support -v flag, that will output “success” if the file is copied, or “target file exist” if this is
the case, or “general failure” on some other problem (in addition to the returned INT value).
The tool will support -f flag (that means force), that allows to overwrite the target file
usage copy <file1> <file2> -v
output: success
note: if the must-have parameters are missing (the file names) return 1, and print a usage explanation
and the optional flags

# Part B :
coding library. We have two codding methods.
Method a, named codecA: covert all lower case chars to upper case, and all upper case to lower case.
All other chars will remain unchanged.
Method b, named codecB: convert all chars to the 3-rd next char (adding a number of 3 to the ascii
val).
The libraries should support “encode” and “decode” methods.
Note: the libraries should be “reversable”, meaning that if one does “encode” and then “decode, he will
get the original string
1) Write 2 different shared libraries , each implementing it’s algorithm
2) Write a two tools, named encode and decode, to utilize the libraries. The tools will get some text and
convert it according to selected library.
Usage : encode/decode <codec> <message>
output: encoded/decoded string
example: “encode codecA aaaBBB” will return “AAAbbb”
example: “decode codecB EEEddd” will return “BBBaaa”
# Part C :
 a shell program named stshell (st for students).
The features are:
1) able to run CMD tools that exist on system (by fork + exec + wait)
2) able to stop running tool by pressing Ctrl+c, but not killing the shell itself (by signal handler)
3) able to redirect output with “>” and “>>”, and allow piping with “|”, at least for 2 following
pipes. For example command like this should be supported “ls -l | grep aaa | wc”
4) able to stop itself by “exit” command
