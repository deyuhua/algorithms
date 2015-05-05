/*
 * Auhtor: deyuhua, email: deyuhua@gmail.com
 * Implement stack with array. 
 */

#include "../../include/common.h"
#define INIT_SIZE 256 //init size of stack 

/*
 * define structure of stack, that only contain one field that hold
 * address of user defined data
 */
struct _node{
    void * data;  //hold user defined data.
};
typedef struct _node stack;

static int top_stack = -1; // top of stack.
static int size_stack = 0; //size of stack.

/*
 * stack implemented with array must have initialize size, INIT_SIZE = 16;
 */
stack * stack_initialize ()
{
    stack * head = (stack *) smalloc (INIT_SIZE * sizeof (stack));
    top_stack = 0;
    size_stack = INIT_SIZE;
    return head;
}

/*
 * destory stack, and reassign top_stack with -1
 */
void stack_destory (stack * head)
{
    int key;
    for (key=0; key<top_stack; sfree(head[key].data), key++);
    sfree (head);
    top_stack = -1;
    size_stack = 0;
}

/*
 * clear stack is easily, just reassign top_stack with 0;
 */
void stack_clear (stack  * head)
{
    int key;
    for (key=0; key<top_stack; sfree (head[key].data), key++);
    top_stack = 0;
}

/*
 * if stack is empty, return true, else fals
 */
bool stack_isempty (stack * head)
{
    return top_stack ? false : true;
}

/*
 * return length of stack
 */
int stack_length (stack * head)
{
    return top_stack;
}

/*
 * return top elment in stack
 */
stack * stack_top (stack * head)
{
    return stack_isempty(head) ? NULL : &(head[top_stack-1]);
}

/*
 * one of most important function is push that add an element into stack
 */
void stack_push (stack * head,  void * elem)
{
    if (top_stack >= size_stack){
        perror("stack full\n");
        return ;
    }
    head[top_stack++].data = elem;
}

/*
 * same as push, pop is important in all stack operations, that delete an
 * from stack
 */
stack * stack_pop (stack * head)
{
    stack * top;
    if (stack_isempty (head)) return NULL;
    top = (stack *) smalloc (sizeof (stack));
    top->data = head[top_stack-1].data;
    head[-- top_stack].data = NULL;
    return top;
}

/*
 * travel stack,  and visit all element in stack
 */
void stack_travel (stack * head, void (*action) (stack * elem))
{
    int key;
    for (key=0; key<top_stack; action(&(head[key])), key++);
}
