all:
	$(CC) src/*.c -o corescript
	valgrind ./corescript example/test.core
