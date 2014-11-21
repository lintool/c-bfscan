#define COLLECTION_POS_SIZE 203429861
#define COLLECTION_TF_SIZE 162602853
#define NUM_DOCS 16141812
#define NUM_TERMS 14327804
#define TOTAL_TERMS 203452768
#define DOC_UNIQUE_TERM_LENGTH 50


#define MU 2500.0
#define TOP_K 1000
#define NUM_TOPICS 49
#define DATA_PATH "data/"

int collection_pos[COLLECTION_POS_SIZE];
int collection_tf[COLLECTION_TF_SIZE];
unsigned char collection_24bit[3 * COLLECTION_POS_SIZE];
unsigned char tf[COLLECTION_TF_SIZE];
unsigned char doclengths[NUM_DOCS];
unsigned char doclengths_ordered[NUM_DOCS];
long tweetids[NUM_DOCS];
int cf[NUM_TERMS];

double (*array_fun[DOC_UNIQUE_TERM_LENGTH])(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus);
double (*array_fun_direct[NUM_DOCS])(int* collection, unsigned char* tf, int base, int querytermid, double prob, double plus);