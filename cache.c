#include "cache.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cachePolicy cache;

// Initializes the cache by setting head to NULL and size to 0.
void initCache() {
    cache.head = NULL;
    cache.size = 0;
}

// Searches for a given rod length in the cache and returns the cache value. If
// found updates the cahche based on the policy LRU or LFU
cacheValue *findCacheValue(int rodLength) {
    cacheValue *prev = NULL, *current = cache.head;

    while (current) {
        if (current->rodLength == rodLength) {
            printf("[CACHE HIT] Found rod length %d in cache.\n", rodLength);

#ifdef LRU
            if (prev) {
                prev->next    = current->next;
                current->next = cache.head;
                cache.head    = current;
                printf("[LRU UPDATE] Moved rod length %d to the front.\n",
                       rodLength);
            }
#elif defined(LFU)
            current->count++;
            printf("[LFU UPDATE] Increased count for rod length %d to %d.\n",
                   rodLength, current->count);
#endif

            return current;
        }
        prev    = current;
        current = current->next;
    }

    printf("[CACHE MISS] Rod length %d not found in cache.\n", rodLength);
    return NULL;
}

// Inserts a new value into the cache, evicts an existing value if cache is full
// uses LRU or LFU policy
void insertCacheValue(int rodLength, int bestPrice, int bestCut) {
    if (cache.size >= CACHE_SIZE) {
        cacheValue *prev = NULL, *current = cache.head, *evict = cache.head,
                   *evictPrev = NULL;

#ifdef LRU
        while (current->next) {
            prev    = current;
            current = current->next;
        }
        evict     = current;
        evictPrev = prev;
#elif defined(LFU)
        int minCount = current->count;
        while (current) {
            if (current->count < minCount) {
                evict     = current;
                evictPrev = prev;
                minCount  = current->count;
            }
            prev    = current;
            current = current->next;
        }
#endif

        printf("[CACHE EVICT] Removing rod length %d from cache.\n",
               evict->rodLength);

        if (evictPrev)
            evictPrev->next = evict->next;
        else
            cache.head = evict->next;
        free(evict);
        cache.size--;
    }

    cacheValue *newCacheValue = (cacheValue *)malloc(sizeof(cacheValue));
    if (!newCacheValue) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    newCacheValue->rodLength = rodLength;
    newCacheValue->bestPrice = bestPrice;
    newCacheValue->bestCut   = bestCut;
    newCacheValue->count     = 1;
    newCacheValue->next      = cache.head;
    cache.head               = newCacheValue;
    cache.size++;

    printf("[CACHE INSERT] Added rod length %d to cache with price %d.\n",
           rodLength, bestPrice);
}
