System Design
--------------
There are four different strategies you can run: Scan1, Scan2, AVXScan1, AVXScan2 and each has a multithreading version.
* Scan1(Scan1.c): use nested for loops
* Scan2(Scan2.c): unroll the for loops that check the query terms
* AVXScan1(AVXScan1.c): add SSE, AVX2 to Scan2
* AVXScan2(AVXScan2.c): unroll for loop for looping docs based on AVXScan1

The multithreading versions are just the files that have the term "multithread" in it and all the files are self-explanatory.

API Intro
--------------
Input Data:
* inputTextFile (pre-tokenized/stemmed and space-delimited):

    ```
    1 terms...
    2 terms...
    ...
    ```
* inputDocidsFile:

    ```
    1 docno1
    2 docno2
    ...
    ```
* queryFile (pre-tokenized/stemmed and space-delimited):

    ```
    1 terms
    2 terms
    ...
    ```

Output:  
* For each of the design, output is in the format of the following with 1000 results per topic:

    ``
    topic_id doc_id ranking score system_tag
    ``

Getting Started
--------------
1. You can clone the repo with the following command:

    ```
    $ git clone git://github.com/lintool/c-bfscan.git
    ``` 

2. Once you've cloned the repository, change directory into `c-bfscan` and compile all source files:

    ```
    $ cd c-bfscan
    $ make
    ```

3. Prepare the data introduced in the API section, and generate document pool, where the docpoolPath is the path that stores the document pool.

    ```
    $ ./GenerateStats {inputTextFile} {inputDocidsFile} {docpoolPath}
    ```

4. To run different systems:

    Scan1:
    
    ```
    $ ./Scan1 {docpoolPath} {queryFile}
    ```
    
    Scan2:
    
    ```
    $ ./Scan2 {docpoolPath} {queryFile}
    ```
    To run AVXScan1 and AVXScan2, make sure that your computer supports AVX2 instructions.
    
    AVXScan1:
    
    ```
    $ ./AVXScan1 {docpoolPath} {queryFile}
    ```
    
    AVXScan2:
    
    ```
    $ ./AVXScan2 {docpoolPath} {queryFile}
    ```
    
    Scan1_multithread_interquery:
    
    ```
    $ ./Scan1_multithread_interquery {docpoolPath} {queryFile} {numThreads}
    ```
    
    Scan1_multithread_intraquery:
    
    ```
    $ ./Scan1_multithread_intraquery {docpoolPath} {queryFile} {numThreads}
    ```
    
    Scan2_multithread_interquery:
    
    ```
    $ ./Scan2_multithread_interquery {docpoolPath} {queryFile} {numThreads}
    ```
    
    Scan2_multithread_intraquery:
    
    ```
    $ ./Scan2_multithread_intraquery {docpoolPath} {queryFile} {numThreads}
    ```
    
    AVXScan1_multithread_interquery:
    
    ```
    $ ./AVXScan1_multithread_interquery {docpoolPath} {queryFile} {numThreads}
    ```
    
    AVXScan1_multithread_intraquery:
    
    ```
    $ ./AVXScan1_multithread_intraquery {docpoolPath} {queryFile} {numThreads}
    ```
    
    AVXScan2_multithread_interquery:
    
    ```
    $ ./AVXScan2_multithread_interquery {docpoolPath} {queryFile} {numThreads}
    ```
    
    AVXScan2_multithread_intraquery:
    
    ```
    $ ./AVXScan2_multithread_intraquery {docpoolPath} {queryFile} {numThreads}
    ```
    
Notes
-----------
* Query evaluation uses Query Likelihood with Bayesian smoothing using Dirichlet priors.
* In this version of c-bfsan, topics are not associated with timestamp, so all the documents are scanned for each topic and there's no early termination.
* All multithreaded designs support up to 48 threads.
