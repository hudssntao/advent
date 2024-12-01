#include <stdio.h>
#include <stdlib.h>

struct ScoredInt {
    int number;
    int score;
};

int comp (const void *a, const void *b) {
    return *((int *)a) - *((int *)b);
}

int countSortedOccurences (const int number, const int *list, const int ARRAY_SIZE) {
    int occurences = 0;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (list[i] > number) {
            return occurences;
        }
        if (list[i] == number) {
            occurences++;
        }
    }

    return occurences;
}

int main() {
    FILE *ptr = fopen("./data/day_1.txt", "r");
    if (ptr == NULL) {
        printf("No such file");
        return 0;
    }

    int ARRAY_SIZE = 1000;

    int leftArray[ARRAY_SIZE];
    int rightArray[ARRAY_SIZE];

    int left;
    int right;

    int index = 0;

    while (fscanf(ptr, "%d %d", &left, &right) == 2) {
            leftArray[index] = left;
            rightArray[index] = right;
            index++;
    }

    qsort(&leftArray, ARRAY_SIZE, sizeof(leftArray[0]), comp);
    qsort(&rightArray, ARRAY_SIZE, sizeof(rightArray[0]), comp);

    
    // Day 1 Part 1 
    int diffSum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
       int diffWithoutAbs = leftArray[i] - rightArray[i];
       int diff = abs(diffWithoutAbs);
       diffSum += diff;
    }
    printf("Difference: %d\n", diffSum);
    
    // Day 1 Part 2
    struct ScoredInt prevScoredInt = {0, 0};
    int similarityScore = 0;
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (prevScoredInt.number == leftArray[i]) {
            similarityScore += prevScoredInt.score; 
            continue;
        }

        int occurences = countSortedOccurences(leftArray[i], rightArray ,ARRAY_SIZE);
        int score = occurences * leftArray[i];
        
        similarityScore += score;
        prevScoredInt = (struct ScoredInt){ leftArray[i], score };
    }
    printf("Similarity score: %d\n", similarityScore);

    return 0;
}
