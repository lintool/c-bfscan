#include <stdint.h>
#define BLOCK_SIZE 8
#define DOCS_BLOCK_SIZE 6

#define MU 2500.0
#define TOP_K 1000

long num_docs;
long total_terms;
int num_topics;
// extern termindexes;
// extern termindexes_padding;

uint32_t * collection_tf;
uint8_t * tf;
uint32_t * collection_tf_padding;
uint8_t * tf_padding;
uint8_t * doclengths;
uint8_t * doclengths_ordered;
uint8_t * doclengths_ordered_padding;
uint64_t * tweetids;
uint32_t * cf;
uint32_t * base;
uint32_t * base_padding;
uint8_t * doc_pos;
int **topics;
int **termindexes;
// long topics_time[];
