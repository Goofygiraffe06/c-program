#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int l, int r) {
    int pivot = arr[r];
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[r]);
    return i + 1;
}

int quickselect(int arr[], int l, int r, int k) {
    if (l == r) return arr[l];
    int pi = partition(arr, l, r);
    if (k == pi) return arr[k];
    if (k < pi) return quickselect(arr, l, pi-1, k);
    return quickselect(arr, pi+1, r, k);
}

int kth_smallest(int arr[], int n, int k) {
    return quickselect(arr, 0, n-1, k-1);
}

int kth_largest(int arr[], int n, int k) {
    return quickselect(arr, 0, n-1, n-k);
}

int main() {
    int arr[] = {7, 10, 4, 3, 20, 15};
    int n = 6;
    int k = 3;
    
    printf("Kth smallest: %d\n", kth_smallest(arr, n, k));
    
    int arr2[] = {7, 10, 4, 3, 20, 15};
    printf("Kth largest: %d\n", kth_largest(arr2, n, k));
    return 0;
}
