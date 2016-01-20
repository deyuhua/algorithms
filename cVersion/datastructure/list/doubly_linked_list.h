/*
 * Auhtor: deyuhua, email: deyuhua@gmail.com

 * Doulby_linked_list contain there fields.
 * (1).One is a pointer that hold address of user defined data, in order to provide
 * high level abstraction, but increase complexity of functions. 
 * (2).The other one is also a pointer that hold address of prior node of linked list.
 * (3).Last one is is alse a pointer that hold address of next node of linked list.
 */

#include "../../include/common.h"

/*
 * define structure of singly_linked list.
 */
struct _node{
    void * data; //hold address of user defined data
    struct _node * prior;
    struct _node * next;
};

typedef struct _node list;

/*
 * initialize singly_linked list with a head node, and assign data field with NULL,
 * means no data associate with data field.
 */
list * list_initialize ()
{
    list * head;
    head = (list *) smalloc (sizeof (list));
    head->data = NULL;
    head->prior = NULL;
    head->next = NULL;
    return head;
}

/*
 * list destory function, free all node in list with sfree(means saftly free), include head node.
 */
void list_destory (list * head)
{
    list * cur = head;
    for (cur=head; head!=NULL; head=cur->next, sfree(cur->data), sfree(cur), cur=head);
}

/*
 * sometime we just want to free node of list, but not user data. for example, multi list share
 * same user define data, we just want to free node of list.this function same as list_destory
 */
void list_free (list * head)
{
    list * cur = head;
    for (cur=head; head!=NULL; head=cur->next, sfree(cur), cur=head);
}

/*
 * if given list is empty(menas it noly contain head node), return true, else return false.
 */
bool list_isempty (list * head)
{
    return head->next ? false : true;
}

/*
 * insert a node with given index into list, zero means insert node at head of list,
 * if index >= length of list, insert node at tail of list
 */
void list_insert (list * head, int index, void * data)
{
    list * cur = head;
    list * key = (list *) smalloc (sizeof (list));
    
    for (; index!=0&&cur->next!=NULL; index--, cur=cur->next);
    
    key->data = data;
    key->prior = cur;
    key->next = cur->next;
    cur->next = key;
    if (key->next){
        key->next->prior = key;
    }
}

/*
 * delete a node with given index from list, zero means delete first node from list,
 * if index >= length of list, delete tail node of list
 */
void  list_delete (list *head, int index)
{
    list * pre = head;
    list * cur = pre->next;

    if (list_isempty (head)) return ; //empty list, do nothing.
    for (; index!=0&&cur->next!=NULL; index--, pre=cur, cur=cur->next);
    
    pre->next = cur->next;
    if (cur->next){
        cur->next->prior = pre;
    } //if not tail node, then change prior pointer of next node to prior node.
    sfree ( cur->data); //saftly free user defined data
    sfree (cur); //saftly free given node ar tail node of list
}

/*
 * return address of node with given index, return value is node type pointer.
 */
list * list_index (list * head, int index)
{
    list * cur = head->next;
    for (; index!=0&&cur->next!=NULL; cur=cur->next);
    return cur;
}

/*
 * return prior node of given node, if given node is first node of list or not in list,
 * just return NULL.
 */
list * list_prior (list * head, list * cur)
{
    return cur==NULL||cur==head->next ? NULL : cur->prior;
}

/*
 * return next node of given node, if given node is at tail of list or not find int list,
 * just return NULL;
 */
list * list_next (list * head, list *cur)
{
    return cur ? cur->next : NULL; //if cur is NULL, just return NULL;
}

/*
 * sample function, return length of list
 */
int list_length (list * head)
{
    int count = 0;
    list * cur= head;
    for (; cur->next!=NULL; cur=cur->next, count++);
    return count;
}

/*
 * filter is a useful function, select node that match user defined.
 */
list * list_filter (list * head, bool (*select) (list * key))
{
    list * cur = head->next;
    list * new = list_initialize ();
    for (; cur!=NULL; cur=cur->next){
        if (select (cur)){
            list_insert (new, list_length (new), cur->data);
        }
    }
    return new;
}

/*
 * reverse list.
 */
list * list_reverse (list * head)
{
    list * cur = head->next;
    list * new = list_initialize ();
    for (; cur!=NULL; cur=cur->next){
        list_insert (new, 0, cur->data);
    }
    return new;
}

/*
 * most useful function is list map, just lisk python or lisp,map function iterate all node,
 * then take some user defined action to every node. such as scale.
 */
void list_map (list * head, void (*action) (list * key))
{
    list * cur = head->next;
    for (; cur!=NULL; action(cur), cur=cur->next);
}
