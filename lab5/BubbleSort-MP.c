#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function declarations
void bubblesort(int *arr, int size);
void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);

// Main function
int main(void) {
    int SIZE = 100000;
    int nums[SIZE];

    clock_t start, end;
    double cpu_time_used;
    srand(42);

    // Fill array with random numbers
    for (int i = 0; i < SIZE; i++) {
        nums[i] = rand() % 10000;
    }

    start = clock();

    // Partition into two halves
    int nums1[SIZE / 2], nums2[SIZE / 2];
    
    for (int i = 0; i < SIZE / 2; i++) {
        nums1[i] = nums[i];
        nums2[i] = nums[i + SIZE / 2];
    }

    // Sort each half using Bubble Sort
    bubblesort(nums1, SIZE / 2);
    bubblesort(nums2, SIZE / 2);

    // Merge the two sorted halves
    for (int i = 0; i < SIZE / 2; i++) {
        nums[i] = nums1[i];
        nums[i + SIZE / 2] = nums2[i];
    }

    // Apply Merge Sort to the merged array
    mergeSort(nums, 0, SIZE - 1);

    end = clock();

    // Print elapsed time
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Sorting took %f seconds.\n", cpu_time_used);

    // Print first 10 sorted numbers
    for (int i = 0; i < 10; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}

// Bubble Sort function
void bubblesort(int *nums, int size) {
    int temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (nums[j] > nums[j + 1]) {
                temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    } 
}

// Merge function (for mergeSort)
void merge(int arr[], int left, int mid, int right) {
    int size1 = mid - left + 1;
    int size2 = right - mid;

    int leftArr[size1], rightArr[size2];

    // Copy data to temp arrays leftArr[] and rightArr[]
    for (int i = 0; i < size1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < size2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < size1 && j < size2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < size1)
        arr[k++] = leftArr[i++];
    while (j < size2)
        arr[k++] = rightArr[j++];
}

// Merge Sort function (recursive)
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}