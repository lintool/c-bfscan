#define COLLECTION_SIZE 152775841//191160334
#define NUM_DOCS 15175674
#define NUM_TERMS 14327804
#define TOTAL_TERMS 203452768
#define DOC_LENGTH 49

#define MU 2500.0
#define TOP_K 1000

int collection[COLLECTION_SIZE];
short tf[COLLECTION_SIZE];
long tweetids[NUM_DOCS];
short doclengths[NUM_DOCS];
short df[NUM_TERMS];
int cf[NUM_TERMS];

double (*array_fun[DOC_LENGTH])(int* collection, short* tf, int *base, int *querytermid, double *prob, double *plus);