# minimalist makefile
.SUFFIXES:
#
.SUFFIXES: .cpp .o .c .h

CFLAGS = -fPIC -std=c99 -O3 -march=native -Wall -Wextra -pedantic
LDFLAGS = -shared
LIBNAME=libsimdcomp.so.0.0.3
all: bfscan_pos_v1 bfscan_pos_v2 bfscan_pos_v3 bfscan_tf_v1 bfscan_tf_v2 bfscan_tf_v2_simd bfscan_tf_v2_multithread_interquery bfscan_tf_v2_multithread_intraquery bfscan_tf_v3_multithread_interquery bfscan_tf_v3_multithread_intraquery bfscan_tf_v3 bfscan_tf_v4 bfscan_tf_v5 raw_scan raw_scan_24bit

HEADERS=./include/simdbitpacking.h ./include/simdcomputil.h ./include/simdintegratedbitpacking.h ./include/simdcomp.h 
OBJECTS= simdbitpacking.o simdintegratedbitpacking.o simdcomputil.o 

$(LIBNAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(LIBNAME) $(OBJECTS)  $(LDFLAGS) 

simdcomputil.o: ./src/simdcomputil.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/simdcomputil.c -Iinclude  

simdbitpacking.o: ./src/simdbitpacking.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/simdbitpacking.c -Iinclude  

simdintegratedbitpacking.o: ./src/simdintegratedbitpacking.c  $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/simdintegratedbitpacking.c -Iinclude  
	
bfscan_pos_v1: bfscan_pos_v1.c
	gcc -O3 -Wall bfscan_pos_v1.c heap.c data.c -o bfscan_pos_v1 -Iinclude  $(OBJECTS)

bfscan_pos_v2: bfscan_pos_v2.c
	gcc -O3 -Wall bfscan_pos_v2.c heap.c data.c -o bfscan_pos_v2 -Iinclude  $(OBJECTS)

bfscan_pos_v3: bfscan_pos_v3.c
	gcc -O3 -Wall bfscan_pos_v3.c heap.c data.c -o bfscan_pos_v3 -Iinclude  $(OBJECTS)

bfscan_tf_v1: bfscan_tf_v1.c
	gcc -O3 -Wall bfscan_tf_v1.c heap.c data.c -o bfscan_tf_v1 -Iinclude  $(OBJECTS)

bfscan_tf_v2: bfscan_tf_v2.c
	gcc -O3 -Wall bfscan_tf_v2.c heap.c data.c -o bfscan_tf_v2 -Iinclude  $(OBJECTS)

bfscan_tf_v2_simd: bfscan_tf_v2_simd.c $(HEADERS) $(OBJECTS)
	$(CC) $(CFLAGS) heap.c data.c -o bfscan_tf_v2_simd ./bfscan_tf_v2_simd.c -Iinclude  $(OBJECTS)

bfscan_tf_v2_multithread_interquery: bfscan_tf_v2_multithread_interquery.c $(HEADERS) $(OBJECTS)
	$(CC) $(CFLAGS) heap.c data.c threadpool.c -o bfscan_tf_v2_multithread_interquery ./bfscan_tf_v2_multithread_interquery.c -Iinclude  $(OBJECTS)

bfscan_tf_v2_multithread_intraquery: bfscan_tf_v2_multithread_intraquery.c $(HEADERS) $(OBJECTS)
	$(CC) $(CFLAGS) heap.c data.c threadpool.c -o bfscan_tf_v2_multithread_intraquery ./bfscan_tf_v2_multithread_intraquery.c -Iinclude  $(OBJECTS)

bfscan_tf_v3: bfscan_tf_v3.c
	gcc -O3 -Wall bfscan_tf_v3.c heap.c data.c -o bfscan_tf_v3 -Iinclude  $(OBJECTS)

bfscan_tf_v3_multithread_interquery: bfscan_tf_v3_multithread_interquery.c $(HEADERS) $(OBJECTS)
	$(CC) $(CFLAGS) heap.c data.c threadpool.c -o bfscan_tf_v3_multithread_interquery ./bfscan_tf_v3_multithread_interquery.c -Iinclude  $(OBJECTS)

bfscan_tf_v3_multithread_intraquery: bfscan_tf_v3_multithread_intraquery.c $(HEADERS) $(OBJECTS)
	$(CC) $(CFLAGS) heap.c data.c threadpool.c -o bfscan_tf_v3_multithread_intraquery ./bfscan_tf_v3_multithread_intraquery.c -Iinclude  $(OBJECTS)

bfscan_tf_v4: bfscan_tf_v4.c
	gcc -O3 -Wall bfscan_tf_v4.c heap.c data.c func_arr.c -o bfscan_tf_v4 -Iinclude  $(OBJECTS)

bfscan_tf_v5: bfscan_tf_v5.c
	gcc -O3 -Wall bfscan_tf_v5.c heap.c data.c func_arr.c -o bfscan_tf_v5 -Iinclude  $(OBJECTS)

raw_scan: raw_scan.c
	gcc -O3 -Wall raw_scan.c data.c -o raw_scan -Iinclude  $(OBJECTS)

raw_scan_24bit: raw_scan_24bit.c
	gcc -O3 -Wall raw_scan_24bit.c data.c -o raw_scan_24bit -Iinclude  $(OBJECTS)