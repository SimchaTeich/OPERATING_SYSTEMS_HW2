cmp: cmp.c
	clang-14 -o cmp cmp.c

copy: copy.c
	clang-14 -o copy copy.c

clean:
	rm cmp copy
