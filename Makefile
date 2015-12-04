all: GenerateStats Scan1 Scan2 AVXScan1 AVXScan2 Scan1_multithread_interquery Scan1_multithread_intraquery Scan2_multithread_interquery Scan2_multithread_intraquery AVXScan1_multithread_interquery AVXScan1_multithread_intraquery AVXScan2_multithread_interquery AVXScan2_multithread_intraquery

GenerateStats: GenerateStats.c
	gcc -O3 -w -std=gnu99 -lm GenerateStats.c -o GenerateStats

Scan1: Scan1.c
	gcc -O3 -w -std=gnu99 -lm Scan1.c -o Scan1

Scan2: Scan2.c
	gcc -O3 -w -std=gnu99 -lm Scan2.c -o Scan2

AVXScan1: AVXScan1.c
	gcc -O3 -w -std=gnu99 -lm -msse4.1 -mavx2 AVXScan1.c -o AVXScan1

AVXScan2: AVXScan2.c
	gcc -O3 -w -std=gnu99 -lm -msse4.1 -mavx2 AVXScan2.c -o AVXScan2

Scan1_multithread_interquery: Scan1_multithread_interquery.c
	gcc -O3 -w -std=gnu99 -lm -lpthread Scan1_multithread_interquery.c -o Scan1_multithread_interquery

Scan1_multithread_intraquery: Scan1_multithread_intraquery.c
	gcc -O3 -w -std=gnu99 -lm -lpthread Scan1_multithread_intraquery.c -o Scan1_multithread_intraquery

Scan2_multithread_interquery: Scan2_multithread_interquery.c
	gcc -O3 -w -std=gnu99 -lm -lpthread Scan2_multithread_interquery.c -o Scan2_multithread_interquery

Scan2_multithread_intraquery: Scan2_multithread_intraquery.c
	gcc -O3 -w -std=gnu99 -lm -lpthread Scan2_multithread_intraquery.c -o Scan2_multithread_intraquery

AVXScan1_multithread_interquery: AVXScan1_multithread_interquery.c
	gcc -O3 -w -std=gnu99 -lm -msse4.1 -mavx2 -lpthread AVXScan1_multithread_interquery.c -o AVXScan1_multithread_interquery

AVXScan1_multithread_intraquery: AVXScan1_multithread_intraquery.c
	gcc -O3 -w -std=gnu99 -lm -msse4.1 -mavx2 -lpthread AVXScan1_multithread_intraquery.c -o AVXScan1_multithread_intraquery

AVXScan2_multithread_interquery: AVXScan2_multithread_interquery.c
	gcc -O3 -w -std=gnu99 -lm -msse4.1 -mavx2 -lpthread AVXScan2_multithread_interquery.c -o AVXScan2_multithread_interquery

AVXScan2_multithread_intraquery: AVXScan2_multithread_intraquery.c
	gcc -O3 -w -std=gnu99 -lm -msse4.1 -mavx2 -lpthread AVXScan2_multithread_intraquery.c -o AVXScan2_multithread_intraquery

clean:
	$(RM) GenerateStats Scan1 Scan2 AVXScan1 AVXScan2 Scan1_multithread_interquery Scan1_multithread_intraquery Scan2_multithread_interquery Scan2_multithread_intraquery AVXScan1_multithread_interquery AVXScan1_multithread_intraquery AVXScan2_multithread_interquery AVXScan2_multithread_intraquery