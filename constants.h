#define COLLECTION_POS_SIZE 203429861//179482307   
#define COLLECTION_TF_SIZE 162603674//139011595
#define NUM_DOCS 16141812
#define NUM_TERMS 14327749//218647
#define TOTAL_TERMS 203429861
#define DOC_UNIQUE_TERM_LENGTH 50
#define BLOCK_SIZE 4

#define MU 2500.0
#define TOP_K 1000
#define NUM_TOPICS 49
#define DATA_PATH "../../Data/All/"

#include "include/simdcomp.h"

int collection_pos[COLLECTION_POS_SIZE];
int collection_tf[COLLECTION_TF_SIZE];
uint32_t * collection_tf_simd;
uint8_t * buffer_tf_input;
unsigned char collection_24bit[3 * COLLECTION_POS_SIZE];
unsigned char tf[COLLECTION_TF_SIZE];
unsigned char * tf_simd;
unsigned char doclengths[NUM_DOCS];
unsigned char doclengths_ordered[NUM_DOCS];
unsigned char doclengths_ordered_simd[NUM_DOCS];
long tweetids[NUM_DOCS];
int cf[NUM_TERMS];

double (*array_fun[DOC_UNIQUE_TERM_LENGTH])(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus);
double (*array_fun_direct[NUM_DOCS])(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus);
