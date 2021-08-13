#include <stdio.h>
#include <stdlib.h>

int contains(int *array, int size, int elem) {
    for (int *i = array; i < array + size; i++) {
        if (*i == elem) {
            return 1;
        }
    }
    return 0;
}

int find_fixed_point_helper(int *array, int prefix, int size) {
    if (size <= 0) {
        return -1;
    }
    int mid = size/2;
    if (array[mid] == prefix + mid) {
        return prefix + mid;
    } else if (array[mid] > prefix + mid) {
        return find_fixed_point_helper(array, prefix, mid);
    } else {
        return find_fixed_point_helper(array + mid + 1, prefix + mid + 1, size - mid - 1);
    }
}

void printArray(int *array, int size) {
    for (int *i = array; i != array + size; i++) {
        printf("%d, ", *i);
    }
}

int find_fixed_point(int *array, int size) {
    return find_fixed_point_helper(array, 0, size);
}

// sorts the array 
void sort(int *array, int size) {
    int i, key, j;
    for (i = 1; i < size; ++i) {
        key = array[i];
        j = i-1;
        while (j >= 0 && array[j] > key) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = key;
    }
}

void checkError(int *array, int size, int expected, int result, int *failedCounter) {
    if (expected != result) {
        printArray(array, size);
        printf(" expected %d but got %d\n", expected, result);
        (*failedCounter)++;
    }
}

void initiate_array(int *array, int size, int setIndex) {
    int newNum; 
    for (int i = 0; i < size; i++) {
        if (i == setIndex) {
            array[i] = setIndex;
        } else if (i  < setIndex) {
            newNum = (rand() % setIndex) - 2*setIndex;
            while (newNum >= 0 || contains(array, i, newNum) == 1) {
                newNum = (rand() % setIndex) - 2*setIndex;
            }
            array[i] = newNum;
        } else {
            newNum = setIndex + 1 + rand();
            while (contains(array, i, newNum) == 1) {
                newNum = setIndex + 1 + rand();
            }
            array[i] = newNum;
        }
    }
    if (setIndex == -1) {
        sort(array, size);
    } else {
        sort(array, setIndex);
        sort(array + setIndex + 1, size - setIndex - 1);
    }
}

void test() {
    int array[6];
    int failed = 0;
    int result, expected;
    
    result = find_fixed_point(array, 0);
    expected = -1;
    checkError(array, 0, expected, result, &failed);

    array[0] = 0;
    expected = 0;
    result = find_fixed_point(array, 1);
    checkError(array, 1, expected, result, &failed);

    array[0] = -1;
    expected = -1;
    result = find_fixed_point(array, 1);
    checkError(array, 1, expected, result, &failed);

    array[0] = 10;
    expected = -1;
    result = find_fixed_point(array, 1);
    checkError(array, 1, expected, result, &failed);

    initiate_array(array, 5, 2);
    expected = 2;
    result = find_fixed_point(array, 5);
    checkError(array, 5,expected, result, &failed);

    initiate_array(array, 5, 1);
    expected = 1;
    result = find_fixed_point(array, 5);
    checkError(array, 5,expected, result, &failed);

    initiate_array(array, 5, 0);
    expected = 0;
    result = find_fixed_point(array, 5);
    checkError(array, 5,expected, result, &failed);

    initiate_array(array, 5, 3);
    expected = 3;
    result = find_fixed_point(array, 5);
    checkError(array, 5, expected, result, &failed);

    initiate_array(array, 5, 4);
    expected = 4;
    result = find_fixed_point(array, 5);
    checkError(array, 5,expected, result, &failed);

    initiate_array(array, 5, 2);
    expected = 2;
    result = find_fixed_point(array, 5);
    checkError(array, 5,expected, result, &failed);

    initiate_array(array, 5, -1);
    expected = -1;
    result = find_fixed_point(array, 5);
    checkError(array, 5, expected, result, &failed);

    initiate_array(array, 6, 1);
    expected = 1;
    result = find_fixed_point(array, 6);
    checkError(array, 6, expected, result, &failed);

    initiate_array(array, 6, 0);
    expected = 0;
    result = find_fixed_point(array, 6);
    checkError(array, 6, expected, result, &failed);

    initiate_array(array, 6, 3);
    expected = 3;
    result = find_fixed_point(array, 6);
    checkError(array, 6, expected, result, &failed);

    initiate_array(array, 6, 4);
    expected = 4;
    result = find_fixed_point(array, 6);
    checkError(array, 6, expected, result, &failed);

    initiate_array(array, 6, -1);
    expected = -1;
    result = find_fixed_point(array, 6);
    checkError(array, 6, expected, result, &failed);

    if (failed == 0) {
        printf("PASSED ALL TESTS\n");
    } else {
        printf("Failed %d tests\n", failed);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        test();
        return 0;
    } 

    int array[argc-1];
    for (int i = 1; i < argc; i++) {
        array[i-1] = atoi(argv[i]);
    }
    sort(array, argc-1);
    printf("find_fixed_point returned %d\n", find_fixed_point(array, argc-1));
}