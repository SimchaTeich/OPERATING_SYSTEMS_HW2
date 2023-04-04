cmp: cmp.c
	clang-14 -o cmp cmp.c


copy: copy.c
	clang-14 -o copy copy.c


codecA: codecA.h codecA.c
	clang-14 -o libcodecA.so -shared -fPIC codecA.c


codecB: codecB.h codecB.c
	clang-14 -o libcodecB.so -shared -fPIC codecB.c


encode: encode.c
	clang-14 encode.c -L . -l codecA codecB -o encode
	export LD_LIBRARY_PATH=.


decode: decode.c
	clang-14 decode.c -L . -l codecA codecB -o decode
	export LD_LIBRARY_PATH=.


testcodecA: codecA
	clang-14 Tests/Test_codecA.c -L . -l codecA -o Tests/Test_codecA
	export LD_LIBRARY_PATH=.
	./Tests/Test_codecA


clean:
	rm cmp copy libcodecA.so Tests/Test_codecA
