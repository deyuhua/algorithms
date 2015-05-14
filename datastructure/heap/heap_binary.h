/*
 * Auhtor: deyuhua, email: deyuhua@gmail.com
 */

#include "../../include/common.h"

/*
 * define structure of binary heap
 */
struct _heap{
    size_t heapsize;  //record how many element in heap
    size_t capacity;  //record capacity of current binary heap
    int * data;  
};
typedef struct _heap heap;

/*
 * initialize binary heap, assign heapsize with zero
 */
heap * heap_initialize (size_t size)
{
    heap * h = (heap *) smalloc (sizeof (heap));
    h->heapsize = 0;
    h->capacity = size;
    h->data = (int *) smalloc (sizeof (int) * size);
    return h;
}

/*
 * exchange two elemnet;
 */
void exchange (int * array, int i, int j)
{
    int  temp;
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

/*
 * maintain max heap property
 */
void max_heapify (heap * h , int i)
{
    int l, r, largest;
    int *array = h->data;
    l = i << 1;  //left child
    r = (i << 1) + 1; //right child
    if (l<h->heapsize&&array[l]>array[i]){
        largest = l;
    }else{
        largest = i;
    }
    if (r<h->heapsize&&array[r]>array[largest]){
        largest = r;
    }
    if (largest!=i){
        exchange (array, i, largest);
        max_heapify (h, largest);
    }
}

/*
 *build max heap
 */
void build_max_heap (heap * h)
{
    int i;
    for (i=h->heapsize/2; i>=0; max_heapify (h, i), i--);
}

/*
 * insert a new element into heap
 */
void heap_push (heap * h, int  elem)
{
    if (h->heapsize>=h->capacity){
        h->capacity <<= 1;
        h->data =
            (int *) srealloc (h->data, sizeof (int) * h->capacity);
    }
    h->data[h->heapsize++] = elem;
    build_max_heap (h);
}

/*
 * delete an element from heap
*/
void heap_pop (heap * h)
{
    if (h->heapsize<1){
        printf ("error, no elemnet in heap\n");
        return ;
    }
    exchange (h->data, 0, --(h->heapsize));
    build_max_heap (h);
}
