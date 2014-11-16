#define COLLECTION_POS_SIZE 191160334
#define COLLECTION_TF_SIZE 152775841
#define NUM_DOCS 15175674
#define NUM_TERMS 14327804
#define TOTAL_TERMS 203452768
#define DOC_LENGTH 49

#define MU 2500.0
#define TOP_K 1000

int collection_pos[COLLECTION_POS_SIZE];
int collection_tf[COLLECTION_TF_SIZE];
unsigned char collection_24bit[3 * COLLECTION_POS_SIZE];
short tf[COLLECTION_TF_SIZE];
long tweetids[NUM_DOCS];
short doclengths_ordered[NUM_DOCS];
short doclengths[NUM_DOCS];
int cf[NUM_TERMS];

double (*array_fun[DOC_LENGTH])(int* collection, short* tf, int base, int querytermid, double prob, double plus);
double (*array_fun_direct[NUM_DOCS])(int* collection, short* tf, int base, int querytermid, double prob, double plus);