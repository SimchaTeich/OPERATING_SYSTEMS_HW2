default: cmp copy encode decode stshell

cmp: cmp.c
	gcc -o cmp cmp.c


copy: copy.c
	gcc -o copy copy.c


codecA: codecA.h codecA.c
	gcc -o libcodecA.so -shared -fPIC codecA.c


codecB: codecB.h codecB.c
	gcc -o libcodecB.so -shared -fPIC codecB.c


encode: encode.c codecA codecB
	#gcc encode.c -L. -l codecA -l codecB -o encode
	#export LD_LIBRARY_PATH=.
	gcc -Wall -Werror -L. -Wl,-rpath,. encode.c -ldl -o encode


decode: decode.c codecA codecB
	#gcc decode.c -L. -l codecA -l codecB -o decode
	#export LD_LIBRARY_PATH=.
	gcc -Wall -Werror -L. -Wl,-rpath,. decode.c -ldl -o decode


stshell: stshell.c
	gcc -o stshell stshell.c


clean:
	rm cmp copy libcodecA.so libcodecB.so encode decode stshell
