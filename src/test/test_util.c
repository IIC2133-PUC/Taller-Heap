#include "test_util.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h> 
#include <math.h>

bool heap_equals(Heap* heap1, Heap* heap2)
{
  if(heap1 && heap2 && heap1->value == heap2->value)
  {
    return heap_equals(heap1->left_child, heap2->left_child)
        && heap_equals(heap1->right_child, heap2->right_child);
  }
  if(!heap1 && !heap2)
  {
    return true;
  }
  return false;
}

static int get_height(int n)
{
  int temp = n + 1;
  int height = 0;
  while (temp)
  {
    height++;
    temp /= 2;
  }
  return height;
}

static int get_steps(int n)
{
  return get_height(n) - 1;
}

static Heap* create_node(int n, int index)
{
  Heap* out = malloc(sizeof(Heap));
  out->left_child = NULL;
  out->right_child = NULL;
  out->parent = NULL;
  out->value = n;
  out->count=1;
  out->height=get_height(index);
  return out;
}

static int left_or_right(int n, int steps)
{
  return !((n+1)>>(steps - 1) == ((n+1)>>steps)*2);
}

static void update_height(Heap* heap)
{
  if(!heap) return;
  int left_height = heap->left_child ? heap->left_child->height : 0;
  int right_height = heap->right_child ? heap->right_child->height : 0;

  heap->height = fmax(left_height, right_height) + 1; 
  update_height(heap->parent);
}

static void increase_count(Heap* heap) 
{
  if(!heap) return;
  heap -> count +=1;
  if (heap -> parent)
  {
    increase_count(heap -> parent);
  } 
}

Heap* heap_from_file(FILE* file)
{
  Heap* out = NULL; 
  Heap* current_node;
  Heap* new_node;
  int amount = 0;
  int value = 0;
  // printf("Inside heap from file\n");
  fscanf(file, "%d", &amount) ?: abort();
  for (int i = 0; i < amount; i++)
  {
    fscanf(file, "%d", &value)?: abort();
    new_node = create_node(value, i);
    if (i==0)
    {
      out = new_node;
    }
    else
    {
      current_node = out;
      for (int step = get_steps(i); step > 1; step--)
      {
        if (left_or_right(i, step)) // i: index, step: #step
        {
          current_node = current_node->right_child;
        }
        else
        {
          current_node = current_node->left_child;
        }
      }
      new_node->parent = current_node;
      if (left_or_right(i, 1))
      {
        current_node->right_child = new_node;
      }
      else
      {
        current_node->left_child = new_node;
      }
      increase_count(new_node->parent);
      update_height(new_node);
    }
  }
  return out;
}

Heap* random_heap(int n){
    // Crea un heap de tamaño n de manera aleatoria
    
    int max_size = n*n;

    Heap* heap = heap_node_init(rand() % max_size);

    // int numbers[n];
    for(int i=1; i < n; i++){
        // if(i == 0){
        //     Heap* heap = heap_node_init(rand() % max_size);
        // }
        // else{
        //     heap_insert(heap, rand() % max_size);
        // }
        heap_insert(heap, rand() % max_size);
    }
    return heap;
}


void heap_to_file(Heap* heap, FILE* out) 
{ 
  int size = heap -> count;
  int array[size + 1];
  array[0] = size;
  Heap* curr_heap = heap;
  for (int i = 1; i < size + 1; i++) {
      for (int steps = get_steps(i-1); steps > 0; steps--){
          if (left_or_right(i-1, steps)) {
              curr_heap = curr_heap -> right_child;
          }
          else
          {
              curr_heap = curr_heap -> left_child;
          }
      }
      array[i] = curr_heap -> value;
      curr_heap = heap;
  } 
  for (int i = 0; i < size + 1; i++){
      /*printf("%i\n", array[i]);*/
      ! (i == size) ? fprintf(out, "%i ", array[i]): fprintf(out, "%i", array[i]);
  }
  fprintf(out, "\n");
}
