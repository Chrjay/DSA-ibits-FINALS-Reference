#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Follows 1 index basing
#define MAX 101

struct minHeap{
    int arr[MAX];
    int size;
};

// For swapping
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Top - down approach (Used in Extracting Root)
void down_heapify(struct minHeap *h, int i){
    int left = 2*i;
    int right = 2*i + 1;
    int smallest = i;

    if(left <= h->size && h->arr[left] < h->arr[smallest]){
        smallest = left;
    }

    if(right <= h->size && h->arr[right] < h->arr[smallest]){
        smallest = right;
    }

    if(smallest != i){
        swap(&h->arr[i], &h->arr[smallest]);
        down_heapify(h, smallest); 
    }
}

// Bottom - up apporach (Used in Insertion)
void up_heapify(struct minHeap *h, int i){
    int parent = i / 2;

    while(i > 1 && h->arr[parent] > h->arr[i]){
        swap(&h->arr[parent], &h->arr[i]);
        i = parent;
        parent = i / 2;
    }
}

// Insertion
void insert(struct minHeap *h, int value){
    if(h->size >= MAX - 1){
        printf("Heap Overflow!\n");
        return;
    }

    h->size++;
    h->arr[h->size] = value;
    up_heapify(h, h->size);
}
 
// Extraction / Deletion of Minimum
int extractRoot(struct minHeap *h){
    if(h->size == 0){
        printf("Heap is Empty!\n");
        return -1;
    }

    int root = h->arr[1];
    h->arr[1] = h->arr[h->size];
    h->size--;
    down_heapify(h, 1);

    return root;
}

// Display Heap
void display(struct minHeap *h){
    printf("[ ");
    for(int i = 1; i <= h->size; i++){
        printf("%d ", h->arr[i]);
    }
    printf("]\n");
}

int main(void){
    struct minHeap heap;
    heap.size = 0;
    bool running = true;
    int value, choice;

    printf("MIN HEAP\n");
    printf("What would you like to do?\n");
    printf("[1] Enter Value      [2] Extract \n");
    printf("[3] Display Heap     [4] Exit \n");

    while(running){
        printf("= ");
        scanf(" %d", &choice);

        switch(choice){
            case 1: 
                printf("Enter a value: ");
                scanf(" %d", &value);

                insert(&heap, value);
                printf("Value Added\n");
                break;
            case 2: 
                printf("Extracted Min: %d\n", extractRoot(&heap));
                break;
            case 3:
                printf("Min heap: ");
                display(&heap);
                break;
            case 4:
                printf("Exiting....\n");
                running = false;
                break;
            default:
                printf("Invalid Input!\n");
        }
    }

    printf("Final Min Heap: ");
    display(&heap);
    
}