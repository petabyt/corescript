gcc -Wall	standard/main.c\
	parser/parser.c\
	runtime/runtime.c\
	runtime/functions.c\
	math/math.c\
	interpreter.c\
	-o corescript

./corescript example/test.core
