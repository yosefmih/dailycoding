#include <stdio.h>
#include <stdlib.h>

typedef __uint32_t uint32_t;

struct BitArray {
    uint32_t *array;
    uint32_t size; 
};

typedef struct BitArray BitArray;

BitArray *init(uint32_t size) {
    BitArray *bitArray = (BitArray *)calloc(1, sizeof(BitArray)); 
    uint32_t sizeOfArray = size/32 + (size % 32 == 0)? 0 : 1;
    bitArray->array = (uint32_t *)calloc(sizeOfArray, 4);
    return bitArray;
}

void set(BitArray *bitArray, uint32_t index, uint32_t val) {
    uint32_t arrayIndex = index/32;
    uint32_t bitMask = 1 << (index % 32);
    if (val == 0) {
        bitArray->array[arrayIndex] &= ~bitMask;
    } else {
        bitArray->array[arrayIndex] |= bitMask;
    }
}

uint32_t get(BitArray *bitArray, uint32_t index) {
    uint32_t arrayIndex = index/32;
    uint32_t bitMask = 1 << (index % 32);
    return (bitArray->array[arrayIndex] & bitMask) >> (index % 32);
}

void checkError(int expected, int output, uint32_t *failed) {
    if (expected != output) {
        printf("Expected %d but got %d\n", expected, output);
        (*failed)++;
    }
}

void test() {
    uint32_t failed = 0;

    BitArray *bitArray = init(10);
    set(bitArray, 4, 1);
    set(bitArray, 7, 1);
    checkError(1, get(bitArray, 4), &failed);
    checkError(1, get(bitArray, 7), &failed);
    checkError(0, get(bitArray, 23), &failed);
    free(bitArray);

    bitArray = init(40);
    set(bitArray, 10, 1);
    set(bitArray, 34, 1);
    checkError(1, get(bitArray, 10), &failed);
    checkError(1, get(bitArray, 34), &failed);
    checkError(0, get(bitArray, 4), &failed);
    free(bitArray);

    if (failed != 0) {
        printf("Failed %d tests\n", failed);
    } else {
        printf("PASSED ALL TESTS!\n");
    }
}

int main(int argc, char *argv[]) {
    test();
    return 0;
}