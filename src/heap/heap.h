#pragma once

struct heap;
typedef struct heap Heap;

/** Un max heap implementado como árbol */
typedef struct heap
{
  /** Puntero al hijo izquierdo */
  Heap* left_child;
  /** Puntero al hijo derecho */
  Heap* right_child;
  /** Puntero al padre del nodo */
  Heap* parent;
  /** Prioridad del nodo */
  int value;
  /** Cantidad de elementos en el (sub)heap, incluye la raíz */
  int count;
  /** Altura del (sub)heap, incluyendo la raíz **/
  int height;
} Heap;

/*****************************************************************************/
/**************************** Memory Management ******************************/
/*****************************************************************************/

/** Inicia un nodo como Heap con valor value */
Heap* heap_node_init              (int value);
/** Libera recursivamente la memoria asociada al heap */
void  heap_destroy                (Heap* heap);

/*****************************************************************************/
/******************************** Insertion **********************************/
/*****************************************************************************/

/** Obtiene el nodo del cual se colgará la proxima inserción */
Heap* heap_insertion_parent       (Heap* heap);
/** Hace subir recursivamente la raiz hasta que esta bien ubicada */
void  heap_sift_up                (Heap* heap);
/** Inserta un nuevo elemento en el heap */
void  heap_insert                 (Heap* heap, int value);

/*****************************************************************************/
/******************************* Extraction **********************************/
/*****************************************************************************/

/** Obtiene el nodo de más abajo a la derecha */
Heap* heap_extraction_replacement (Heap* heap);
/** Hace bajar recursivamente la raiz hasta que esta bien ubicada */
void  heap_sift_down              (Heap* heap);
/** Extrae el elemento más prioritario del heap */
int   heap_extract                (Heap* heap);
