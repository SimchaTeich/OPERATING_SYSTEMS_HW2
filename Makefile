cmp: cmp.c
	clang-14 -o cmp cmp.c

copy: copy.c
	clang-14 -o copy copy.c

codecA: codecA.h codecA.c
	clang-14 -o libcodecA.so -shared -fPIC codecA.c

clean:
	rm cmp copy libcodecA.so
