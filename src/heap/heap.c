#include "heap.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

/*****************************************************************************/
/**************************** Funciones Útiles *******************************/
/*****************************************************************************/

/** Indica si un entero positivo no nulo es potencia de 2 */
bool is_power_of_2(int x)
{
  // Chequeamos que el input esté dentro del rango válido
  assert(x >= 0);
  return (x &(x - 1)) == 0;
}

/*****************************************************************************/
/**************************** Memory Management ******************************/
/*****************************************************************************/

/** Inicia un nodo como Heap con valor value */
Heap* heap_node_init(int value)
{
  Heap* heap = malloc(sizeof(Heap));
  heap -> value = value;
  heap -> left_child = NULL;
  heap -> right_child = NULL;
  heap -> parent = NULL;
  heap -> count = 1;
  heap -> height = 1;
  return heap;
}

/** Libera recursivamente la memoria asociada al heap */
void  heap_destroy(Heap* heap)
{
  if(heap)
  {
    heap_destroy(heap -> left_child);
    heap_destroy(heap -> right_child);
    free(heap);
  }
}

/*****************************************************************************/
/******************************** Insertion **********************************/
/*****************************************************************************/

/** Obtiene el nodo del cual se colgará la proxima inserción */
Heap* heap_insertion_parent       (Heap* heap)
{
  printf("Función no implementada: heap_insertion_parent()\n");
  abort();
}

/** Hace subir recursivamente la raiz hasta que esta bien ubicada */
void  heap_sift_up                (Heap* heap)
{
  printf("Función no implementada: heap_sift_up()\n");
  abort();
}

/** Inserta un nuevo elemento en el heap */
void  heap_insert                 (Heap* heap, int value)
{
  printf("Función no implementada: heap_insert()\n");
  abort();
}

/*****************************************************************************/
/******************************* Extraction **********************************/
/*****************************************************************************/

/** Obtiene el nodo de más abajo a la derecha */
Heap* heap_extraction_replacement (Heap* heap)
{
  printf("Función no implementada: heap_extraction_replacement()\n");
  abort();
}

/** Hace bajar recursivamente la raiz hasta que esta bien ubicada */
void  heap_sift_down              (Heap* heap)
{
  printf("Función no implementada: heap_sift_down()\n");
  abort();
}

/** Extrae el elemento más prioritario del heap */
int   heap_extract                (Heap* heap)
{
  printf("Función no implementada: heap_extract()\n");
  abort();
}