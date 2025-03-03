#include <stdio.h>

#include "rod_cutting.h"

#define MAX_SIZE 10

int main() {
    int rodLength;
    int lengths[MAX_SIZE], price[MAX_SIZE], count = 0;
    int cutCount[MAX_SIZE] = {0};

    getInput(&rodLength, lengths, price, &count);

    int leftoverLength = rodLength;
    int totalPrice     = computeOptimalCuts(rodLength, lengths, price, count,
                                            cutCount, &leftoverLength);

    printResults(lengths, price, cutCount, count, leftoverLength, totalPrice);

    return 0;
}
