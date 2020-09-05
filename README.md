# corescript
Corescript written in C. Official CLI Program.
## Compilation:
```
tcc parser/parser.c runtime/runtime.c runtime/functions.c math/math.c interpreter.c -o corescript
```
Note that GCC and TCC both work.
## Usage
```
daniel@pc:~/Documents/CorescriptC$ ./corescript example/fib.core
0
1
1
2
3
5
8
13
21
34
55
89
```
