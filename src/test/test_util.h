#include "../heap/heap.h"
#include <stdbool.h>
#include <stdio.h>

bool heap_equals(Heap* heap1, Heap* heap2);
Heap* heap_from_file(FILE* file);
Heap* random_heap(int n);
void heap_to_file(Heap* heap, FILE* out);
