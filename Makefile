cmp: cmp.c
	gcc -o cmp cmp.c


copy: copy.c
	gcc -o copy copy.c


codecA: codecA.h codecA.c
	gcc -o libcodecA.so -shared -fPIC codecA.c


codecB: codecB.h codecB.c
	gcc -o libcodecB.so -shared -fPIC codecB.c


encode: encode.c codecA codecB
	gcc encode.c -L . -l codecA -l codecB -o encode
	export LD_LIBRARY_PATH=.


decode: decode.c codecA codecB
	gcc decode.c -L . -l codecA -l codecB -o decode
	export LD_LIBRARY_PATH=.


testcodecA: codecA
	gcc Tests/Test_codecA.c -L . -l codecA -o Tests/Test_codecA
	export LD_LIBRARY_PATH=.
	./Tests/Test_codecA


clean:
	rm cmp copy libcodecA.so libcodecB.so encode decode Tests/Test_codecA
