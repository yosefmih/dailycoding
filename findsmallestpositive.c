#include <stdio.h>
#include <stdlib.h>


int absVal(int num) {
    return (num >= 0)? num : -num;
}

// printer for debugging purposes
void printArray(int *input, size_t size) {
    for (int *i = input; i < input + size; ++i) {
        printf("%d, ", *i);
    }
    printf("\n");
}

int collectPositive(int *input, size_t size) {
    size_t j = 0;
    for (size_t i = 0; i < size; ++i) {
         if (input[i] <= 0) {
             // swap elements at i and j
             input[i] ^= input[j];
             input[j] ^= input[i];
             input[i] ^= input[j];
             j++;
         }
    }
    return j;
}

int findMinMissingPositive(int *input, size_t size) {
    int numOfNonPositives = collectPositive(input, size);
    for (size_t i = numOfNonPositives; i < size; ++i) {
        size_t updateIndex = absVal(input[i]) - 1 + numOfNonPositives;
        if (updateIndex < size && input[updateIndex] > 0) {
            input[updateIndex] = -input[updateIndex];
        }
    }

    for (size_t j = numOfNonPositives; j < size; j++) {
        if (input[j] > 0) {
            return j + 1;
        }
    }

    return size - numOfNonPositives + 1;
}



void test() {
    int failed = 0; 

    int array_one[3] = {1, 2, 0};
    int expected_one = 3;
    int output_one = findMinMissingPositive(array_one, 3);
    if (output_one != expected_one) {
        printf("Small array, expected %d but got %d\n", expected_one, output_one);
        failed++;
    }

    (failed == 0)? printf("PASSED ALL TESTS!\n") : printf("Failed %d tests\n", failed);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        test();
        return 0;
    } 

    int input[argc-1];
    for (size_t i = 1; i < argc; ++i) {
        input[i-1] = atoi(argv[i]);
    }
    printf("The smallest missing positive number for the given array is %d\n", findMinMissingPositive(input, argc-1));
}