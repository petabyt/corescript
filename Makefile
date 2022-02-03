FILES=$(wildcard src/*.c)

corescript: $(FILES)
	$(CC) $(FILES) -o corescript

test:
	./corescript example/test.core
