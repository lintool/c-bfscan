The data locates at: /fs/clip-twitter/ylwang/bfscan-statistics/All/


**Positional representation**

The positional representation is simply a sequence of termids, one for each document position:

```
352
931
64
352
846
...
```

That is, term 352 appears in position 0, term 931 appears in position 1, etc.

**TF representation**

The TF representation requires two parallel arrays, and in essence "pre-aggregates" the TF within each document:

```
352  2
931  1
64   1
846  1
...
```

In other words, term 352 appears twice (i.e., has *tf* = 2).

**Implementation 1**

For each topic:

- Loop over all documents
- Loop over terms in document
- Loop over all query terms
- Compute score

**Implementation 2**

For each topic:

- Loop over all documents
- Loop over all query terms
- Loop over terms in document
- Compute score

Note that implementations 1 and 2 differ in the order of the document terms and query terms loop.

**Implementation 3**

For each topic:

- Loop over all documents
- Separate code path for queries of different lengths
- Loop over terms in document
- Compute score

**Implementation 4**

For each topic:

- Loop over all documents
- Separate code path for queries of different lengths
- Use a dispatch table to dispatch to a separate function to process documents of different lengths

**Implementation 5**

For each topic:

- Loop over an array of function pointers that points to functions that process documents of different lengths
- Separate code path for queries of different lengths


So we have:

- `bfscan_pos_v1`, `bfscan_pos_v2`, `bfscan_pos_v3`, `bfscan_pos_v4`, `bfscan_pos_v5`
- `bfscan_tf_v1`, `bfscan_tf_v2`, `bfscan_tf_v3`, `bfscan_tf_v4`, `bfscan_tf_v5`

All of these process a single query at a time (then we have separate versions that process different numbers of queries at a time).

**Performance**

Here we show the latency per query in milliseconds for two different implementations.

```
            v1   v2   v3   v4   v5
positional  815  630  430
tf          750  670  405  610  615
```

Baselines(milliseconds per query):

```
Lucene              200
raw_scan            240
raw_scan_24bits     350
```

