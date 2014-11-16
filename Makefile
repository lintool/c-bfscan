all: bfscan_pos_v1 bfscan_pos_v2 bfscan_pos_v3 bfscan_tf_v1 bfscan_tf_v2 bfscan_tf_v3 bfscan_tf_v4 bfscan_tf_v5 raw_scan raw_scan_24bit

bfscan_pos_v1: bfscan_pos_v1.c
	gcc -O3 -Wall bfscan_pos_v1.c heap.c data.c func_arr.c -o bfscan_pos_v1

bfscan_pos_v2: bfscan_pos_v2.c
	gcc -O3 -Wall bfscan_pos_v2.c heap.c data.c func_arr.c -o bfscan_pos_v2

bfscan_pos_v3: bfscan_pos_v3.c
	gcc -O3 -Wall bfscan_pos_v3.c heap.c data.c func_arr.c -o bfscan_pos_v3

bfscan_tf_v1: bfscan_tf_v1.c
	gcc -O3 -Wall bfscan_tf_v1.c heap.c data.c func_arr.c -o bfscan_tf_v1

bfscan_tf_v2: bfscan_tf_v2.c
	gcc -O3 -Wall bfscan_tf_v2.c heap.c data.c func_arr.c -o bfscan_tf_v2

bfscan_tf_v3: bfscan_tf_v3.c
	gcc -O3 -Wall bfscan_tf_v3.c heap.c data.c func_arr.c -o bfscan_tf_v3

bfscan_tf_v4: bfscan_tf_v4.c
	gcc -O3 -Wall bfscan_tf_v4.c heap.c data.c func_arr.c -o bfscan_tf_v4

bfscan_tf_v5: bfscan_tf_v5.c
	gcc -O3 -Wall bfscan_tf_v5.c heap.c data.c func_arr.c -o bfscan_tf_v5

raw_scan: raw_scan.c
	gcc -O3 -Wall raw_scan.c data.c -o raw_scan

raw_scan_24bit: raw_scan_24bit.c
	gcc -O3 -Wall raw_scan_24bit.c data.c -o raw_scan_24bit