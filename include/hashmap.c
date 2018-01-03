/*
 * AUTHOR:  René Kijewski  (rene.<surname>@fu-berlin.de)
 * LICENSE: MIT
 */

#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

// http://www.cse.yorku.ca/~oz/hash.html
uint64_t djb2(char *str) {
	unsigned long hash = 5381;
	char c;
	while( (c = *str++) ) {
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

struct entry {
	char *line;
	int value;
};

#define ENTRY_CMP(left, right) strcmp(left->line, right->line)
#define ENTRY_HASH(entry) djb2(entry->line)

DEFINE_HASHMAP(hashMap, struct entry)
DECLARE_HASHMAP(hashMap, ENTRY_CMP, ENTRY_HASH, free, realloc)