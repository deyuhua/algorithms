/*
 * Auhtor: deyuhua, email: deyuhua@gmail.com
 * Implement stack with list, just encapsulate function of list, resue is important
 * in coding. so get start.
 */

#include "../list/singly_linked_list.h"
/*
 * list have same interface, so you use either singly_linked_list or doubly_linked_list.
 * it's don't matter.
 */
//#include "../list/doubly_linked_list.h"

/*
 * define structure of stack
 */
typedef struct _node stack;

/*
 * initialize stack with a head node, same as list.
 */
stack * stack_initialize ()
{
    return list_initialize ();
}

/*
 * stack destory function, same as list
 */
stack * stack_destory (stack * head)
{
    list_destory (head); 
}

/*
 * free all elements in stack
 */
stack * stack_clear (stack  * head)
{
    list_free (head);
}

/*
 * if stack is empty, return true, else fals
 */
bool stack_isempty (stack * head)
{
    return list_isempty (head);
}

/*
 * return length of stack
 */
int stack_length (stack * head)
{
    return list_length (head);
}

/*
 * return top elment in stack
 */
stack * stack_top (stack * head)
{
    return head->next;
}

/*
 * one of most important function is push that add an element into stack
 */
void stack_push (stack * head,  void * elem)
{
    list_insert (head, 0, elem);
}

/*
 * same as push, pop is important in all stack operations, that delete an
 * from stack
 */
stack * stack_pop (stack * head)
{
    stack * top = head->next;
    head->next = (top ? top->next : top);
    return top;
}

/*
 * travel stack,  and visit all element in stack
 */
stack * stack_travel (stack * head, void (*action) (stack * elem))
{
    list_map (head, action);
}
