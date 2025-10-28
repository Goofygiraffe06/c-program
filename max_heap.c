#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int arr[1000];
    int size;
} MaxHeap;

void max_heap_swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void max_heapify_up(MaxHeap *h, int i) {
    while (i && h->arr[(i-1)/2] < h->arr[i]) {
        max_heap_swap(&h->arr[i], &h->arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

void max_heapify_down(MaxHeap *h, int i) {
    int largest = i;
    int l = 2*i+1;
    int r = 2*i+2;
    if (l < h->size && h->arr[l] > h->arr[largest]) largest = l;
    if (r < h->size && h->arr[r] > h->arr[largest]) largest = r;
    if (largest != i) {
        max_heap_swap(&h->arr[i], &h->arr[largest]);
        max_heapify_down(h, largest);
    }
}

void max_heap_insert(MaxHeap *h, int val) {
    h->arr[h->size] = val;
    max_heapify_up(h, h->size);
    h->size++;
}

int max_heap_extract(MaxHeap *h) {
    if (h->size == 0) return -1;
    int root = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    max_heapify_down(h, 0);
    return root;
}

int main() {
    MaxHeap h = {.size = 0};
    max_heap_insert(&h, 3);
    max_heap_insert(&h, 2);
    max_heap_insert(&h, 15);
    max_heap_insert(&h, 5);
    max_heap_insert(&h, 4);
    
    printf("%d\n", max_heap_extract(&h));
    printf("%d\n", max_heap_extract(&h));
    return 0;
}
