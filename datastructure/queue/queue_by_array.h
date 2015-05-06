/*
 * Auhtor: deyuhua, email: deyuhua@gmail.com
 * Implement queue with array. 
 */

#include "../../include/common.h"
#define INIT_SIZE 256 //init size of queue 

/*
 * define structure of queue, that only contain one field that hold
 * address of user defined data
 */
struct _node{
    void * data;  //hold user defined data.
};
typedef struct _node queue;

static int front;  //head of queue
static int rear;  //tail of queue

/*
 * queue implemented with array that must have initialize size
 * init size equal INIT_SIZE
 */
queue * queue_initialize ()
{
    queue * head = (queue *) smalloc (INIT_SIZE * sizeof (queue));
    front = rear = 0;
    return head;
}

/*
 * destory queue, and reassign top_queue with -1
 */
void queue_destory (queue * head)
{
    int key;
    //saftly free all user data
    for (key=0; key<INIT_SIZE; sfree (head[key].data), key++);
    sfree (head); //free queue
    front = rear = -1; 
}

/*
 * clear queue is easily, just reassign top_queue with 0;
 */
void queue_clear (queue  * head)
{
    int key;
    for (key=0; key<INIT_SIZE; sfree (head[key].data), key++);
    front = rear = 0;
}

/*
 * if queue is empty, return true, else fals
 */
bool queue_isempty (queue * head)
{
    return front==rear ? true : false;
}

/*
 * return length of queue
 */
int queue_length (queue * head)
{
    return front<=rear ? rear-front : rear-front+INIT_SIZE;
}

/*
 * return top elment in queue
 */
queue * queue_head (queue * head)
{
    return queue_isempty(head) ? NULL : &(head[front]);
}

/*
 * one of most important function is queue_en that add an element into queue
 */
void queue_en (queue * head,  void * elem)
{
    //number of element of queue when queue is full equal INIT_SIZE-1
    if (queue_length (head) < INIT_SIZE){ 
        head[rear%INIT_SIZE].data = elem;
        rear = (++rear) % INIT_SIZE;
    }
}

/*
 * same as queue_en, queue_de is important in all queue operations, that delete an
 * element from queue
 */
queue * queue_de (queue * head)
{
    queue * top;
    if (queue_isempty (head)) return NULL;
    top = (queue *) smalloc (sizeof (queue));
    top->data = head[front].data;
    head[front].data = NULL;
    front = (++ front) % INIT_SIZE;
    return top;
}

/*
 * travel queue,  and visit all element in queue
 */
void queue_travel (queue * head, void (*action) (queue * elem))
{
    int key;
    if (queue_isempty (head)) return;
    for (key=front; key!=rear; action(&(head[key])), key=(++key)%INIT_SIZE);    
}
