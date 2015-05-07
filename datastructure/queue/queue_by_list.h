/*
 * Auhtor: deyuhua, email: deyuhua@gmail.com
 * Implement queue with list, just encapsulate function of list, resue is important
 * in coding. so get start.
 */

#include "../list/singly_linked_list.h"
/*
 * list have same interface, so you use either singly_linked_list or doubly_linked_list.
 * it's don't matter.
 */
//#include "../list/doubly_linked_list.h"

/*
 * define structure of queue
 */
typedef struct _node queue;

//define a pointer that point to tail node of queue
static queue * tail = NULL;

/*
 * initialize queue with a head node, same as list.
 */
queue * queue_initialize ()
{
    tail = list_initialize ();
    return tail;
}

/*
 * queue destory function, same as list
 */
void queue_destory (queue * head)
{
    list_destory (head);
    tail = NULL; //queue not exist, so tail is NULL.
}

/*
 * free all elements in queue
 */
void queue_clear (queue  * head)
{
    queue * key;
    while (head->next!=NULL){
        key = head->next;
        head->next =key->next;
        sfree (key->data);
        sfree (key);
    } //free all nodo except head node
    tail = head; //reassign tail 
}

/*
 * if queue is empty, return true, else fals
 */
bool queue_isempty (queue * head)
{
    return list_isempty (head);
}

/*
 * return length of queue
 */
int queue_length (queue * head)
{
    return list_length (head);
}

/*
 * return head elment in queue
 */
queue * queue_head (queue * head)
{
    return head->next;
}

/*
 * add element into queue at tail of queue
 */
void queue_en (queue * head, void * data)
{
    queue * key = (queue *) smalloc (sizeof (queue));
    key->data = data;
    key->next = NULL;
    tail->next = key;
    tail = key;   //tail point to new element.
}

/*
 * delete a node from head of queue, and return head element
 */
queue * queue_de (queue * head)
{
    queue * top = head->next;
    tail = head->next==tail ? head : tail;
    //if queue is empty, then return NULL
    head->next = (top ? top->next : NULL);  
    return top;
}

/*
 * travel queue,  and visit all element in queue
 */
void queue_travel (queue * head, void (*action) (queue * elem))
{
    list_map (head, action);
}
