#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BubbleSort-P.h"

int main(void) {
    // clock variables
    clock_t start, end;
    double cpu_time_used;

    int nums[SIZE], nums1[SIZE / 2], nums2[SIZE / 2];
    srand(42);
    fillArray(nums, SIZE);

    start = clock();
    partition(nums, SIZE, nums1, nums2);

    bubbleSort(nums1, SIZE / 2);
    bubbleSort(nums2, SIZE / 24);
    
    merge(nums, SIZE, nums1, nums2);
    
    bubbleSort(nums, SIZE);
    end = clock();

    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Bubble sort took %f seconds.\n", cpu_time_used);

    printBubbleSort(nums, 10);

    return 0;
}

void fillArray(int *arr, int size) {
    for (int i = 0; i < size; i++ ) {
        arr[i] = rand() % 10000; // maxval = 10000
    }
}

void partition(int *nums, int size, int *nums1, int *nums2) {

    for (int i = 0; i < size / 2; i++) {
        nums1[i] = nums[i];
        nums2[i] = nums[i + size / 2];   
    }
}

void merge(int *nums, int size, int *nums1, int *nums2) {
    for (int i = 0; i < size / 2; i++) {
        nums[i] = nums1[i];
        nums[i + size / 2] = nums2[i];
    }
}

void bubbleSort(int *nums, int size) {
    // BubbleSort
    int temp = 0;

    for (int i = 0; i < size - 1; i++) {
        // u n-1-i bc after the last "round" the furtherst right is sorted, dont have to check that again
         for (int j = 0; j < size - 1 - i; j++) {
            // compare
            if (nums[j] >= nums[j + 1]) {
                // swap
                temp = nums[j]; 
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }
}

void printBubbleSort(int *nums, int size) {
    // Print Sorted Array
    printf("Sorted Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", nums[i]);  // tells printf how to interpet and format the argument
    }
    printf("\n");
}