System Design
--------------
There are four different strategies you can run: Scan1, Scan2, AVXScan1, AVXScan2 and each has a multithreading version.
* Scan1(Scan1.c): use nested for loops
* Scan2(Scan2.c): unroll the for loops that check the query terms
* AVXScan1(AVXScan1.c): add SSE, AVX2 to Scan2
* AVXScan2(AVXScan2.c): unroll for loop for looping docs based on AVXScan1

The multithreading versions are just the files that have the term "multithread" in it and all the files are self-explanatory.

Getting Started
--------------
1. You can clone the repo with the following command:

	```
	$ git clone git://github.com/lintool/c-bfscan.git
	``` 

2. Once you've cloned the repository, change directory into `twitter-tools-core` and build the package with Maven:

	```
	$ cd c-bfscan/twitter-tools-core
	$ mvn clean package appassembler:assemble
	```

3. Build the index on the data collection:

	```
	$ sh target/appassembler/bin/IndexStatuses -collection {collectionPath} -index {indexPath} -optimize
	```

4. Generate document pool, where the dataPath is the path that stores the document pool.

	```
	$ sh target/appassembler/bin/GenerateStatistics -collection {collectionPath} -index {indexPath} -output {dataPath}
	```

5. To format the efficiency topics (here we provide an efficiency file in /data/ folder) to TREC query format and get the top N topics:

	```
	$ sh target/appassembler/bin/FormatQuery -input ../data/05.efficiency_topics -top {N} -output {queryPath}
	```
6. Convert TREC query to the query that can be fed to c-bfscan, note that outputFile is the new format of the query and needs to be a .h file:

	```
	$ sh target/appassembler/bin/GenerateQuery -index {indexPath} -query {queryPath} -output {newQuery.h}
	```

7. Go back to the main repository:

	```
	$ cd ..
	```

8. To run different systems:

	Scan1:
	
	```
	$ gcc -O3 -w -lm Scan1.c -o Scan1 -include {newQuery.h}
	$ ./Scan1 {dataPath}
	```
	
	Scan2:
	
	```
	$ gcc -O3 -w -lm Scan2.c -o Scan2 -include {newQuery.h}
	$ ./Scan2 {dataPath}
	```
	To run AVXScan1 and AVXScan2, make sure that your computer supports AVX2 instructions.
	
	AVXScan1:
	
	```
	$ gcc -O3 -w -lm -msse4.1 -mavx2 AVXScan1.c -o AVXScan1 -include {newQuery.h}
	$ ./AVXScan1 {dataPath}
	```
	
	AVXScan2:
	
	```
	$ gcc -O3 -w -lm -msse4.1 -mavx2 AVXScan2.c -o AVXScan2 -include {newQuery.h}
	$ ./AVXScan2 {dataPath}
	```
	
	Scan1_multithread_interquery:
	
	```
	$ gcc -O3 -w -lm Scan1_multithread_interquery.c -o Scan1_multithread_interquery -lpthread -include {newQuery.h}
	$ ./Scan1_multithread_interquery {dataPath} {numThreads}
	```
	
	Scan1_multithread_intraquery:
	
	```
	$ gcc -O3 -w -lm -lm Scan1_multithread_intraquery.c -o Scan1_multithread_intraquery -lpthread -include {newQuery.h} -include {dataPath/termindexes.h}
	$ ./Scan1_multithread_intraquery {dataPath} {numThreads}
	```
	
	Scan2_multithread_interquery:
	
	```
	$ gcc -O3 -w -lm Scan2_multithread_interquery.c -o Scan2_multithread_interquery -lpthread -include {newQuery.h}
	$ ./Scan2_multithread_interquery {dataPath} {numThreads}
	```
	
	Scan2_multithread_intraquery:
	
	```
	$ gcc -O3 -w -lm Scan2_multithread_intraquery.c -o Scan2_multithread_intraquery -lpthread -include {newQuery.h} -include {dataPath/termindexes.h}
	$ ./Scan2_multithread_intraquery {dataPath} {numThreads}
	```
	
	AVXScan1_multithread_interquery:
	
	```
	$ gcc -O3 -w -lm -msse4.1 -mavx2 AVXScan1_multithread_interquery.c -o AVXScan1_multithread_interquery -lpthread -include {newQuery.h}
	$ ./AVXScan1_multithread_interquery {dataPath} {numThreads}
	```
	
	AVXScan1_multithread_intraquery:
	
	```
	$ gcc -O3 -w -lm -msse4.1 -mavx2 AVXScan1_multithread_intraquery.c -o AVXScan1_multithread_intraquery -lpthread -include {newQuery.h} -include {dataPath/termindexes_padding.h}
	$ ./AVXScan1_multithread_intraquery {dataPath} {numThreads}
	```
	
	AVXScan2_multithread_interquery:
	
	```
	$ gcc -O3 -w -lm -msse4.1 -mavx2 AVXScan2_multithread_interquery.c -o AVXScan2_multithread_interquery -lpthread -include {newQuery.h}
	$ ./AVXScan2_multithread_interquery {dataPath} {numThreads}
	```
	
	AVXScan2_multithread_intraquery:
	
	```
	$ gcc -O3 -w -lm -msse4.1 -mavx2 AVXScan2_multithread_intraquery.c -o AVXScan2_multithread_intraquery -lpthread -include {newQuery.h} -include {dataPath/termindexes_padding.h}
	$ ./AVXScan2_multithread_intraquery {dataPath} {numThreads}
	```
