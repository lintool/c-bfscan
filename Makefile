all: bfscan1 bfscan2 bfscan3

bfscan1: bfscan1.c
	gcc -O3 -Wall bfscan1.c heap.c data.c -o bfscan1

bfscan2: bfscan2.c
	gcc -O3 -Wall bfscan2.c heap.c data.c -o bfscan2

bfscan3: bfscan3.c
	gcc -O3 -Wall bfscan3.c heap.c data.c -o bfscan3
