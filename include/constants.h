#include <stdint.h>
#define BLOCK_SIZE 8
#define DOCS_BLOCK_SIZE 10

#define MU 2500.0
#define TOP_K 1000

extern int num_docs;
extern long total_terms;
extern int num_topics;

uint32_t* collection_tf;
uint8_t* tf;
uint8_t* doclengths_ordered;
uint8_t* doclengths_ordered_padding;
uint32_t* collection_tf_padding;
uint8_t* tf_padding;
uint8_t* doc_pos;
uint64_t* tweetids;
uint8_t* doclengths;
uint32_t* cf;
float* prestore_score_padding;
uint8_t* impact_score_8bits_padding;
uint32_t* impact_score_32bits_padding;