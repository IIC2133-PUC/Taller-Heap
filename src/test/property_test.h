#pragma once
#include "../heap/heap.h"
#include <stdbool.h>

/** Revisa que un heap tiene todas las propiedades que deberia tener */
bool heap_has_all_properties(Heap* heap, char* context);

