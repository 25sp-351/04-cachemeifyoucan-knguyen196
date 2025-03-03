#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CACHE_SIZE 4

typedef struct cacheValue {
    int rodLength;
    int bestPrice;
    int bestCut;
    int count;
    struct cacheValue *next;
} cacheValue;

typedef struct cachePolicy {
    cacheValue *head;
    int size;
} cachePolicy;

extern cachePolicy cache;

cacheValue *findCacheValue(int rodLength);
void insertCacheValue(int rodLength, int bestPrice, int bestCut);
void initCache();
int findbestCut(int rodLength, int lengths[], int price[], int count,
                int *bestCut);

#endif
