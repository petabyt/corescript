CC := cc

all:
	$(CC) src/*.c -o corescript
	./corescript example/test.core
