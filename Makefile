FILES=$(wildcard src/*.c)

corescript: $(FILES)
	$(CC) $(FILES) -o corescript

test: corescript
	./corescript example/test.core
