#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int arr[1000];
    int size;
} MinHeap;

void min_heap_swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void min_heapify_up(MinHeap *h, int i) {
    while (i && h->arr[(i-1)/2] > h->arr[i]) {
        min_heap_swap(&h->arr[i], &h->arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

void min_heapify_down(MinHeap *h, int i) {
    int smallest = i;
    int l = 2*i+1;
    int r = 2*i+2;
    if (l < h->size && h->arr[l] < h->arr[smallest]) smallest = l;
    if (r < h->size && h->arr[r] < h->arr[smallest]) smallest = r;
    if (smallest != i) {
        min_heap_swap(&h->arr[i], &h->arr[smallest]);
        min_heapify_down(h, smallest);
    }
}

void min_heap_insert(MinHeap *h, int val) {
    h->arr[h->size] = val;
    min_heapify_up(h, h->size);
    h->size++;
}

int min_heap_extract(MinHeap *h) {
    if (h->size == 0) return -1;
    int root = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    min_heapify_down(h, 0);
    return root;
}

int main() {
    MinHeap h = {.size = 0};
    min_heap_insert(&h, 3);
    min_heap_insert(&h, 2);
    min_heap_insert(&h, 15);
    min_heap_insert(&h, 5);
    min_heap_insert(&h, 4);
    
    printf("%d\n", min_heap_extract(&h));
    printf("%d\n", min_heap_extract(&h));
    return 0;
}
