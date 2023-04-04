cmp: cmp.c
	clang-14 -o cmp cmp.c

copy: copy.c
	clang-14 -o copy copy.c

codecA: codecA.h codecA.c
	clang-14 -o libcodecA.so -shared -fPIC codecA.c

test: codecA
	clang-14 Tests/Test_codecA.c -L . -l codecA -o Tests/Test_codecA
	export LD_LIBRARY_PATH=.
	./Tests/Test_codecA

clean:
	rm cmp copy libcodecA.so Tests/Test_codecA
