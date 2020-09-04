#include "function_test.h"
#include "test_util.h"
#include "property_test.h"
#include "output.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void heap_print(Heap* heap)
{
  if (!heap)
  {
    return;
  }
  else
  {
    printf("%i:{", heap->value);
    heap_print(heap->left_child);
    printf(",");
    heap_print(heap->right_child);
    printf("}");
  }
}

bool test_insertion_parent()
{
  FILE* file = fopen("src/test/cases/insertion_parent.txt", "r");
  int n_kases;
  fscanf(file, "%d", &n_kases)?: abort();
  for(int kase = 1; kase <= n_kases; kase++)
  {
    Heap* heap = heap_from_file(file);
    Heap* expected = heap_from_file(file);
    Heap* obtained = heap_insertion_parent(heap);
    if(!heap_equals(expected, obtained))
    {
      heap_destroy(heap);
      heap_destroy(expected);
      fclose(file);      
      return false;
    }
    heap_destroy(heap);
    heap_destroy(expected);
  }
  fclose(file);
  return true;
}

bool test_extraction_replacement()
{
  FILE* file = fopen("src/test/cases/extraction_replacement.txt", "r");
  int n_kases;
  fscanf(file, "%d", &n_kases)?: abort();
  for(int kase = 1; kase <= n_kases; kase++)
  {
    Heap* heap = heap_from_file(file);
    Heap* expected = heap_from_file(file);
    Heap* obtained = heap_extraction_replacement(heap);
    if(!heap_equals(expected, obtained))
    {
      heap_destroy(heap);
      heap_destroy(expected);
      fclose(file);      
      return false;
    }
    heap_destroy(heap);
    heap_destroy(expected);
  }
  fclose(file);
  return true;
}

bool test_sift_up()
{
  FILE* file = fopen("src/test/cases/sift_up.txt", "r");
  int n_kases;
  fscanf(file, "%d", &n_kases)?: abort();
  for(int kase = 1; kase <= n_kases; kase++)
  {
    Heap* heap = heap_from_file(file);
    int depth;
    fscanf(file, "%d", &depth)?: abort();
    Heap* node = heap;
    for(int d = 0; d < depth; d++)
    {
      int side;
      fscanf(file, "%d", &side)?: abort();
      node = side ? node->right_child : node->left_child; 
    }
    Heap* expected = heap_from_file(file);
    heap_sift_up(node);
    if(!heap_has_all_properties(heap, "heap_sift_up()") || !heap_equals(expected, heap))
    {
      heap_destroy(heap);
      heap_destroy(expected);
      fclose(file);      
      return false;
    }
    heap_destroy(heap);
    heap_destroy(expected);
  }
  fclose(file);
  return true;
}

bool test_sift_down()
{
  FILE* file = fopen("src/test/cases/sift_down.txt", "r");
  int n_kases;
  fscanf(file, "%d", &n_kases)?: abort();
  for(int kase = 1; kase <= n_kases; kase++)
  {
    Heap* heap = heap_from_file(file);
    Heap* expected = heap_from_file(file);
    heap_sift_down(heap);
    if(!heap_has_all_properties(heap, "heap_sift_down()") || !heap_equals(expected, heap))
    {
      heap_destroy(heap);
      heap_destroy(expected);
      fclose(file);      
      return false;
    }
    heap_destroy(heap);
    heap_destroy(expected);
  }
  fclose(file);
  return true;
}

bool test_insert()
{
  FILE* file = fopen("src/test/cases/insert.txt", "r");
  int n_kases;
  fscanf(file, "%d", &n_kases)?: abort();
  for(int kase = 1; kase <= n_kases; kase++)
  {
    Heap* heap = heap_from_file(file);
    int value;
    fscanf(file, "%d", &value)?: abort();
    Heap* expected = heap_from_file(file);
    heap_insert(heap, value);
    if(!heap_has_all_properties(heap, "heap_insert()") || !heap_equals(expected, heap))
    {
      heap_destroy(heap);
      heap_destroy(expected);
      fclose(file);      
      return false;
    }
    heap_destroy(heap);
    heap_destroy(expected);
  }
  fclose(file);
  return true;
}

bool test_extract()
{
  FILE* file = fopen("src/test/cases/extract.txt", "r");
  int n_kases;
  fscanf(file, "%d", &n_kases)?: abort();
  for(int kase = 1; kase <= n_kases; kase++)
  {
    Heap* heap = heap_from_file(file);
    int expected;
    fscanf(file, "%d", &expected)?: abort();
    Heap* expected_heap = heap_from_file(file);
    int obtained = heap_extract(heap);
    if(!heap_has_all_properties(heap, "heap_extract()") || obtained != expected || !heap_equals(heap, expected_heap))
    {
      heap_destroy(heap);
      heap_destroy(expected_heap);
      fclose(file);      
      return false;
    }
    heap_destroy(heap);
    heap_destroy(expected_heap);
  }
  fclose(file);
  return true;
}


int int_compare(const void *p, const void *q)  
{ 
  const int* l = p; 
  const int* r = q;  
  return (*l - *r); 
} 


bool test_all()
{
  int N = 100000;
  int A[N];
  for(int i = 0; i < N; i++)
  {
    A[i] = rand();
  }
  
  Heap* heap = heap_node_init(A[0]);

  for(int i = 1; i < N; i++)
  {
    heap_insert(heap, A[i]);
  }

  int B[N];

  for(int i = N-1; i >= 1; i--)
  {
    B[i] = heap_extract(heap);
  }

  B[0] = heap->value;

  free(heap);

  qsort(A, N, sizeof(int), int_compare);

  for(int i = 0; i < N; i++)
  {
    if(A[i] != B[i])
    {
      return false;
    }
  }

  return true;
}

static void green ()
{
  printf("\033[0;32m");
}

static void reset()
{
  printf("\033[0m");
}

void function_fail(const char* function)
{
  error_message();
  printf("Tu función ");
  green();
  printf("%s", function);
  reset();
  printf(" no está funcionando correctamente\n\n");
}

void run_all_tests()
{
  bool error = false;
  if(!test_insertion_parent())
  {
    function_fail("heap_insertion_parent()");
    error = true;
  }
  if(!test_sift_up())
  {
    error = true;
    function_fail("heap_sift_up()");
  }
  if(!test_insert())
  {
    error = true;
    function_fail("heap_insert()");
  }
  if(!test_extraction_replacement())
  {
    error = true;
    function_fail("heap_extraction_replacement()");
  }
  if(!test_sift_down())
  {
    error = true;
    function_fail("heap_sift_down()");
  }
  if(!test_extract())
  {
    error = true;
    function_fail("heap_extract()");
  }
  if(!test_all())
  {
    error = true;
    error_message();
    printf("Tu heap no está funcionando correctamente\n");
  }
  if(!error)
  {
    congratulations();
  }
}
