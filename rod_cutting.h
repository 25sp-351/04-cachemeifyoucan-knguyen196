#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"
#define MAX_SIZE 10

// This function finds the best cut for a given rod length and calculates the
// highest price obtainable. A pointer (*bestCut) is used to store the length of
// the most optimal cut.
int findbestCut(int rodLength, int lengths[], int price[], int count,
                int *bestCut) {

    if (rodLength == 0)
        return 0;
    cacheValue *cachedValue = findCacheValue(rodLength);
    if (cachedValue) {
        *bestCut = cachedValue->bestCut;
        return cachedValue->bestPrice;
    }

    int bestPrice = 0;
    *bestCut      = 0;

    for (int ix = 0; ix < count; ix++) {
        if (lengths[ix] <= rodLength) {
            int tempbestCut = 0;
            int currentPrice =
                price[ix] + findbestCut(rodLength - lengths[ix], lengths, price,
                                        count, &tempbestCut);
            if (currentPrice > bestPrice) {
                bestPrice = currentPrice;
                *bestCut  = lengths[ix];
            }
        }
    }
    if (*bestCut > 0)
        insertCacheValue(rodLength, bestPrice, *bestCut);

    return bestPrice;
}

// Reads user input for the rod length and available cut length with their
// prices, stores values in arrays.
void getInput(int *rodLength, int lengths[], int price[], int *count) {

    printf("Enter the length of the rod: ");
    scanf_s("%d", rodLength);

    if (*rodLength < 0) {
        printf("Invalid rod length.\n");
        exit(1);
    }

    printf(
        "Please enter the length and price of a cut in the format <length> "
        "<price>.\n");
    printf("One per line. Ctrl + D to stop.\n");

    while (*count < MAX_SIZE &&
           scanf_s("%d %d", &lengths[*count], &price[*count]) == 2) {
        (*count)++;
    }
}

// Computes the optimal cuts for the maximum profit
int computeOptimalCuts(int rodLength, int lengths[], int price[], int count,
                       int cutCount[], int *leftoverLength) {

    *leftoverLength = rodLength;
    int totalPrice  = 0;

    while (*leftoverLength > 0) {

        int bestCut = 0;
        findbestCut(*leftoverLength, lengths, price, count, &bestCut);

        if (bestCut == 0)
            break;

        for (int ix = 0; ix < count; ix++) {
            if (lengths[ix] == bestCut) {
                cutCount[ix]++;
                totalPrice += price[ix];
                break;
            }
        }

        *leftoverLength -= bestCut;
    }
    return totalPrice;
}

// Prints the final cutting results with n amount of cuts @ size
void printResults(int lengths[], int price[], int cutCount[], int count,
                  int leftoverLength, int totalPrice) {

    printf("Cuts made:\n");
    for (int ix = 0; ix < count; ix++) {
        if (cutCount[ix] > 0) {
            printf("%d @ %d = %d\n", cutCount[ix], lengths[ix],
                   cutCount[ix] * price[ix]);
        }
    }

    printf("Remainder: %d\n", leftoverLength);
    printf("Total price: %d\n", totalPrice);
}
