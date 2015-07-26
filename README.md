System design
--------------
There are four different strategies you can run: Scan1, Scan2, AVXScan1, AVXScan2 and each has a multithreading version.
* Scan1(Scan1.c): use nested for loops
* Scan2(Scan2.c): unroll the for loops that check the query terms
* AVXScan1(AVXScan1.c): add SSE, AVX2 to Scan2
* AVXScan2(AVXScan2.c): unroll for loop for looping docs based on AVXScan1

The multithreading versions are just the files that have the term "multithread" in it and all the files are self-explanatory.

Getting Started
--------------
You can clone the repo with the following command:

```
$ git clone git://github.com/lintool/c-bfscan.git
``` 

Once you've cloned the repository, change directory into `twitter-tools-core` and build the package with Maven:

```
$ cd c-bfscan/twitter-tools-core
$ mvn clean package appassembler:assemble
```

Build the index on the data collection:

```
$ sh target/appassembler/bin/IndexStatuses -collection {collectionPath} -index {indexPath}
```

Generate document pool, where the dataPath is the path that stores the document pool.

```
$ sh target/appassembler/bin/GenerateStatistics -collection {collectionPath} -index {indexPath} -output {dataPath}
```

Convert TREC query to the query that can be fed to c-bfscan, note that outputFile is the new format of the query and needs to be a .h file:

```
$ sh target/appassembler/bin/GenerateQuery -index {indexPath} -query {queryPath} -output {outputPath/newQuery.h}
```

Go back to the main repository:

```
$ cd ..
```

To run system Scan1:

```
$ gcc -O3 -w Scan1.c heap.c data.c -o Scan1 -include {newQuery.h}
$ ./Scan1 {dataPath}
```

To run AVXScan1 and AVXScan2, make sure that your computer supports AVX2 instructions.

To run system AVXScan1:

```
$ gcc -O3 -w -msse4.1 -mavx2 AVXScan1.c heap.c data.c -o AVXScan1 -include {newQuery.h}
$ ./AVXScan1 {dataPath}
```