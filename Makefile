all: Scan1 Scan2 AVXScan1 AVXScan2 AVXScan2_Impactscore Scan1_multithread_interquery Scan1_multithread_intraquery Scan2_multithread_interquery Scan2_multithread_intraquery AVXScan1_multithread_interquery AVXScan1_multithread_intraquery AVXScan2_multithread_interquery AVXScan2_multithread_intraquery AVXScan2_Impactscore_multithread_interquery AVXScan2_Impactscore_multithread_intraquery
	
Scan1: Scan1.c
	gcc -O3 -w Scan1.c heap.c data.c -lm -mcmodel=medium -o Scan1

Scan2: Scan2.c
	gcc -O3 -w Scan2.c heap.c data.c -lm -mcmodel=medium -o Scan2

AVXScan1: AVXScan1.c
	gcc -O3 -w -msse4.1 -mavx2 AVXScan1.c heap.c data.c -lm -mcmodel=medium -o AVXScan1

AVXScan2: AVXScan2.c
	gcc -O3 -w -msse4.1 -mavx2 AVXScan2.c heap.c data.c -lm -mcmodel=medium -o AVXScan2

AVXScan2_Impactscore: AVXScan2_Impactscore.c
	gcc -O3 -w -msse4.1 -mavx2 AVXScan2_Impactscore.c heap.c data.c -lm -mcmodel=medium -o AVXScan2_Impactscore

Scan1_multithread_interquery: Scan1_multithread_interquery.c
	gcc -O3 -w Scan1_multithread_interquery.c heap.c data.c threadpool.c -lm -mcmodel=medium -o Scan1_multithread_interquery -lpthread

Scan1_multithread_intraquery: Scan1_multithread_intraquery.c
	gcc -O3 -w Scan1_multithread_intraquery.c heap.c data.c threadpool.c -lm -mcmodel=medium -o Scan1_multithread_intraquery -lpthread

Scan2_multithread_interquery: Scan2_multithread_interquery.c
	gcc -O3 -w Scan2_multithread_interquery.c heap.c data.c threadpool.c -lm -mcmodel=medium -o Scan2_multithread_interquery -lpthread

Scan2_multithread_intraquery: Scan2_multithread_intraquery.c
	gcc -O3 -w Scan2_multithread_intraquery.c heap.c data.c threadpool.c -lm -mcmodel=medium -o Scan2_multithread_intraquery -lpthread

AVXScan1_multithread_interquery: AVXScan1_multithread_interquery.c
	gcc -O3 -w -msse4.1 -mavx2 AVXScan1_multithread_interquery.c heap.c data.c threadpool.c -lm -mcmodel=medium -o AVXScan1_multithread_interquery -lpthread

AVXScan1_multithread_intraquery: AVXScan1_multithread_intraquery.c
	gcc -O3 -w -msse4.1 -mavx2 AVXScan1_multithread_intraquery.c heap.c data.c threadpool.c -lm -mcmodel=medium -o AVXScan1_multithread_intraquery -lpthread

AVXScan2_multithread_interquery: AVXScan2_multithread_interquery.c
	gcc -O3 -w -msse4.1 -mavx2 AVXScan2_multithread_interquery.c heap.c data.c threadpool.c -lm -mcmodel=medium -o AVXScan2_multithread_interquery -lpthread

AVXScan2_multithread_intraquery: AVXScan2_multithread_intraquery.c
	gcc -O3 -w -msse4.1 -mavx2 AVXScan2_multithread_intraquery.c heap.c data.c threadpool.c -lm -mcmodel=medium -o AVXScan2_multithread_intraquery -lpthread

AVXScan2_Impactscore_multithread_interquery: AVXScan2_Impactscore_multithread_interquery.c
	gcc -O3 -w -msse4.1 -mavx2 AVXScan2_Impactscore_multithread_interquery.c heap.c data.c threadpool.c -lm -mcmodel=medium -o AVXScan2_Impactscore_multithread_interquery -lpthread

AVXScan2_Impactscore_multithread_intraquery: AVXScan2_Impactscore_multithread_intraquery.c
	gcc -O3 -w -msse4.1 -mavx2 AVXScan2_Impactscore_multithread_intraquery.c heap.c data.c threadpool.c -lm -mcmodel=medium -o AVXScan2_Impactscore_multithread_intraquery -lpthread