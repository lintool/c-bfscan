/*
 * AUTHOR:  René Kijewski  (rene.<surname>@fu-berlin.de)
 * LICENSE: MIT
 */

#include <stdlib.h>

#include "hashmap.h"

#define INT_CMP(left, right) *left==*right ? 0 : 1
#define INT_HASH(entry) *entry

struct entry_int {
	int num;
	int value;
};

#define ENTRY_CMP(left, right) left->num == right->num ? 0 : 1
#define ENTRY_HASH(entry) entry->num

DEFINE_HASHMAP(intHashMap, struct entry_int)
DECLARE_HASHMAP(intHashMap, ENTRY_CMP, ENTRY_HASH, free, realloc)