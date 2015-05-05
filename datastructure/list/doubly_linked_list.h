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

typedef struct _node node;

/*
 * initialize singly_linked list with a head node, and assign data field with NULL,
 * means no data associate with data field.
 */
node * list_initialize ()
{
    node * head;
    head = (node *) smalloc (sizeof (node));
    head->data = NULL;
    head->prior = NULL;
    head->next = NULL;
    return head;
}

/*
 * list destory function, free all node in list with sfree(means saftly free), include head node.
 */
void list_destory (node * head)
{
    node * cur = head;
    for (cur=head; head!=NULL; head=cur->next, sfree(cur->data), sfree(cur), cur=head);
}

/*
 * sometime we just want to free node of list, but not user data. for example, multi list share
 * same user define data, we just want to free node of list.this function same as list_destory
 */
void list_free (node * head)
{
    node * cur = head;
    for (cur=head; head!=NULL; head=cur->next, sfree(cur), cur=head);
}

/*
 * if given list is empty(menas it noly contain head node), return true, else return false.
 */
bool list_isempty (node * head)
{
    return head->next ? false : true;
}

/*
 * insert a node with given index into list, zero means insert node at head of list,
 * if index >= length of list, insert node at tail of list
 */
void list_insert (node * head, int index, void * data)
{
    node * cur = head;
    node * key = (node *) smalloc (sizeof (node));
    
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
void  list_delete (node *head, int index)
{
    node * pre = head;
    node * cur = pre->next;
    
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
node * list_index (node * head, int index)
{
    node * cur = head->next;
    for (; index!=0&&cur->next!=NULL; cur=cur->next);
    return cur;
}

/*
 * return prior node of given node, if given node is first node of list or not in list,
 * just return NULL.
 */
node * list_prior (node * head, node * cur)
{
    return cur==NULL||cur==head->next ? NULL : cur->prior;
}

/*
 * return next node of given node, if given node is at tail of list or not find int list,
 * just return NULL;
 */
node * list_next (node * head, node *cur)
{
    return cur ? cur->next : NULL; //if cur is NULL, just return NULL;
}

/*
 * sample function, return length of list
 */
int list_length (node * head)
{
    int count = 0;
    node * cur= head;
    for (; cur->next!=NULL; cur=cur->next, count++);
    return count;
}

/*
 * filter is a useful function, select node that match user defined.
 */
node * list_filter (node * head, bool (*select) (node * key))
{
    node * cur = head->next;
    node * new = list_initialize ();
    node * tail = new;
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
node * list_reverse (node * head)
{
    node * cur = head->next;
    node * new = list_initialize ();
    for (; cur!=NULL; cur=cur->next){
        list_insert (new, 0, cur->data);
    }
    return new;
}

/*
 * most useful function is list map, just lisk python or lisp,map function iterate all node,
 * then take some user defined action to every node. such as scale.
 */
void list_map (node * head, void (*action) (node * key))
{
    node * cur = head->next;
    for (; cur!=NULL; action(cur), cur=cur->next);
}
