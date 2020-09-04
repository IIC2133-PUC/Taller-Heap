#include "../heap/heap.h"
#include <stdbool.h>
#include <stdio.h>
#include "property_test.h"
#include "test_util.h"
#include "output.h"

bool is_heap(Heap* heap)
{
  if (!heap)
   {
       return true;
   }
   if (heap->left_child)
   {
       if (heap->value < heap->left_child->value)
       {
           return false;
       }
   }
   if (heap->right_child)
   {
       if (heap->value < heap->right_child->value)
       {
           return false;
       }
   }
   return is_heap(heap->left_child) && is_heap(heap->right_child);
}

bool are_counts_correct(Heap* heap)
{
  if (!heap)
  {
    return true;
  }
  int count = heap->count - 1;
  if (heap->left_child && heap->right_child)
  {
    if (count != heap->left_child->count + heap->right_child->count)
    {
      return false;
    }
    else
    {
      return  are_counts_correct(heap->left_child) &&
              are_counts_correct(heap->right_child);
    }
  }
  else if (heap->left_child)
  {
    return (count == heap->left_child->count &&
            are_counts_correct(heap->left_child));
  }
  else if (heap->right_child)
  {
    return (count == heap->right_child->count)&&
            are_counts_correct(heap->right_child);
  }
  else
  {
    return (count == 0);
  }
}

bool are_heights_correct(Heap* heap)
{
  if (!heap)
  {
    return true;
  }
  int child_height = heap->height - 1;
  if (heap->left_child && heap->right_child)
  {
    if (child_height != heap->left_child->height &&
        child_height != heap->right_child->height)
    {
      return false;
    }
    else
    {
      return  are_heights_correct(heap->left_child) &&
              are_heights_correct(heap->right_child);
    }
  }
  else if (heap->left_child)
  {
    return (child_height == heap->left_child->height &&
            are_heights_correct(heap->left_child));
  }
  else if (heap->right_child)
  {
    return (child_height == heap->right_child->height &&
            are_heights_correct(heap->right_child));
  }
  else
  {
    return (child_height == 0);
  }
}
static int heap_height(Heap* heap)
{
  if (!heap)
  {
    return 0;
  }
  else
  {
    return heap->height;
  }
}
bool is_balanced(Heap* heap)
{
  if (!heap)
  {
    return true;
  }
  if (heap_height(heap->left_child) - heap_height(heap->right_child) > 1)
  {
    return false;
  }
  else
  {
    return (is_balanced(heap->left_child) && 
           is_balanced(heap->right_child));
  }
}
bool is_left_skewed(Heap* heap)
{
  if (!heap)
  {
    return true;
  }
  if (heap_height(heap->left_child) < heap_height(heap->right_child))
  {
    return false;
  }
  else
  {
    return (is_left_skewed(heap->left_child) && 
           is_left_skewed(heap->right_child));
  }
}

static void green ()
{
  printf("\033[0;31m");
}

static void reset()
{
  printf("\033[0m");
}

bool heap_has_all_properties(Heap* heap, char* context)
{
  bool has_error = false;
  if (is_heap(heap))
  {
    has_error = true;
    error_message();
    printf("Tu heap no cumple con la propiedad fundamental del heap (que ");
    printf("todas las raíces sean mayores a sus hijos) luego de llamar la ");
    printf("función ");
    green();
    printf("%s\n", context);
    reset();
  }
  if (are_counts_correct(heap))
  {
    has_error = true;
    error_message();
    printf("Tu heap no tiene la cuenta de sus hijos correcta luego de llamar ");
    printf("la función ");
    green();
    printf("%s\n", context);
    reset();
  }
  if (are_heights_correct(heap))
  {
    has_error = true;
    error_message();
    printf("Tu heap no tiene las alturas correctas luego de llamar la ");
    printf("función ");
    green();
    printf("%s\n", context);
    reset();
  }
  if (is_balanced(heap))
  {
    has_error = true;
    printf("Tu heap no está balanceado luego de llamar la función ");
    green();
    printf("%s\n", context);
    reset();
  }
  if (is_left_skewed(heap))
  {
    has_error = true;
    error_message();
    printf("Algún hijo de la derecha de tu heap tiene más hijos que el de ");
    printf("la izquierda luego de llamar la función ");
    green();
    printf("%s\n", context);
    reset();
  }
  return !has_error;
}
