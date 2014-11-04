#define COLLECTION_SIZE 191160334
#define NUM_DOCS 15175674
#define NUM_TERMS 14327804

#define MU 2500
#define TOP_K 1000

int collection[COLLECTION_SIZE];
long tweetids[NUM_DOCS];
short doclengths[NUM_DOCS];
short df[NUM_TERMS];
