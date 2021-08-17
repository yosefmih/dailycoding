#include <stdio.h>
#include <stdlib.h>

typedef __int32_t int32_t;

void checkErrorArrays(int32_t *expected, int32_t *result, int32_t length, int32_t *failedCounter) {
    for (int32_t i = 0; i < length; i++) {
        if (expected[i] != result [i]) {
            printf("expected and result differ at index %d\n", i);
            (*failedCounter)++;
            return;
        }
    }
}

void sort_squared(int32_t *list, int length) {
    int32_t inflection_point = -1; 
    for (int32_t i = 0; i < length; ++i) {
        if (list[i] < 0) {
            inflection_point = i;
        } 
        list[i] = list[i]*list[i];
    }
    int32_t *temp = (int32_t*)malloc(4*inflection_point);
    for (int32_t i = inflection_point; i >= 0; --i) {
        temp[inflection_point-i] = list[i];
    }

    int32_t i = 0, j = inflection_point+1, ind = 0;
    while (i <= inflection_point  && j < length) {
        if (temp[i] >= list[j]) {
            list[ind] = list[j];
            j++;
        } else {
            list[ind] = temp[i];
            i++;
        }
        ind++;
    }

    while (i <= inflection_point) {
        list[ind] = temp[i];
        ind++;
        i++;
    }

    free(temp);
}


void test() {
    int32_t failedCounter = 0;
    int32_t input[] = {-9, -2, 0, 2, 3};
    int32_t expected_output[] = {0, 4, 4, 9, 81};
    sort_squared(input, 5);
    checkErrorArrays(expected_output, input, 5, &failedCounter);
    if (failedCounter != 0) {
        printf("Failed %d tests\n", failedCounter);
    } else {
        printf("PASSED ALL TESTS!\n");
    }
}

int main() {
    test();
    return 0;
}