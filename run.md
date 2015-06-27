# Run the experiment
#### System designs
There are four different strategies you can run: Scan1, Scan1_pos, Scan2, Scan2_pos, AVXScan1, AVXScan2 and each has a multithreading version.
* Scan1(Scan1.c): use nested for loops
* Scan1_pos(Scan1_pos.c): Scan1 with no precomputed tfs
* Scan2(Scan2.c): unroll the for loops that check the query terms
* Scan2_pos(Scan2_pos.c): Scan2 with no precomputed tfs
* AVXScan1(AVXScan1.c): add SSE, AVX2 to Scan2
* AVXScan2(AVXScan2.c): unroll for loop for looping docs based on AVXScan1

The multithreading versions are just the files that have the term "multithread" in it and all the files are self-explanatory.
#### How to run
All the data you need is already there, and the explanation of all the data files are down below. So just follow the instructions below to get the experiment started.

First of all, log in to streeling and run the following to enable AVX2
```sh
$ ssh streeling
$ scl enable devtoolset-3 bash
```

To run a single threaded system, take Scan1 as an example:
```sh
$ make Scan1
$ ./Scan1
```

To run a multithreading system, take Scan1_multithread_interquery as an example:
```sh
$ make Scan1_multithread_interquery
$ ./Scan1_multithread_interquery 2
```
Here 2 specifies how many threads that are assigned.

####Run results
Output results include:
* top 1000 results returned for the 49 topics
* the total running time, throughput and time per query. 

In the multithreading setting, results are given 3 times and the total running time, throughput and time per query are the average over 3 times.

#Data
####path
```sh
/fs/clip-twitter/ylwang/bfscan-statistics/All/
```
####Explanation
All the document vectors are appended together as a single 1D array and is stored in all_terms_ordered.txt
* all_terms.txt: term ids in the order they appear in the documents
* all_terms_ordered.txt: unique term ids for each document
* all_terms_tf.txt: tf score correspoinding to all_terms_ordered.txt
* doc_id.txt: document ids
* doc_length.txt: document's original length
* doc_length_ordered.txt: document's length if only considering the unique terms
* cf_table.txt: cf score for all termids from 0 to 14327748(14327749 unique terms in total)
