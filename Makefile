all: bfscan1

bfscan1: bfscan1.c
	gcc -O3 bfscan1.c heap.c -o bfscan1

