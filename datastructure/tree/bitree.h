/*
 * Auhtor: deyuhua, email: deyuhua@gmail.com

 * Bitree contain there fileds.
 * (1).A pointer that point to parent of node;
 * (2).Data field hold address of user data.
 * (3).A pointer that point to right child of node;
 * (4).A pointer that point to left child of node;
 */

#include "../queue/queue_by_list.h"
//#include "../queue/queue_by_array.h"

/*
 * define structure binary tree
 */
struct _treenode {
    struct _treenode * p; //point to parent of node;
    void * data; //hold address of user data;
    struct _treenode * right; //point to right of node;
    struct _treenode * left; //point to left of node.
};
typedef struct _treenode bitree;

//define size of binary tree
static int size_tree;

/*
 * initialize binary tree, assign size of tree with zero;
 * return NULL, in order to initialize root pointer.
 */
bitree * bitree_initialize ()
{
    size_tree = 0;
    return NULL;
}

/*
 * depth-first tree traversal, preorder, inorder and post order
 */
/*
 * preorder tree walk pseudocode code
 * preorder_tree_walk (x)
 *     if x != NIL
 *        access (x)
 *        preorder_tree_walk (x.left)
 *        preorder_tree_walk (x.right)
 * "access" is function pointer  point to a function that user-defined
 * method how to access node. 
 */
void bitree_preorder (bitree * node, void (*access) (bitree * key))
{
    if (node){
        access (node);
        bitree_preorder (node->left, access);
        bitree_preorder (node->right, access);
    }
}

/*
 * inorder tree walk pseudocode code
 * inorder_tree_walk (x)
 *     if x != NIL
 *        inorder_tree_walk (x.left)
 *        access (x) 
 *        inorder_tree_walk (x.right)
 * "access" is function pointer  point to a function that user-defined
 * method how to access node. 
 */
void bitree_inorder (bitree * node, void (*access) (bitree * key))
{
    if (node){
        bitree_inorder (node->left, access);
        access (node);        
        bitree_inorder (node->right, access);
    }
}

/*
 * postorder tree walk pseudocode code
 * postorder_tree_walk (x)
 *     if x != NIL
 *        postorder_tree_walk (x.left)
 *        postorder_tree_walk (x.right)
 *        access (x)  
 * "access" is function pointer  point to a function that user-defined
 * method how to access node. 
 */
void bitree_postorder (bitree * node, void (*access) (bitree * key))
{
    if (node){
        bitree_postorder (node->left, access);
        bitree_postorder (node->right, access);
        access (node);                
    }
}

/*
 * breadth-first tree traversal
 */
/*
 * levelorder tree walk pseudocode code
 * levelorder_tree_walk (root)
 *      queue = empty queue
 *      enque (root)
 *      while queue is not empty do
 *            node = dequeue()
 *            access (node)
 *            if node.left != NIL then
 *                 enqueue (node.left)
 *            if node.right != NIL then
 *                 enqueue (node.right)
 * "access" is function pointer  point to a function that user-defined
 * method how to access node. 
 */
void bitree_levelorder (bitree * root, void (*access) (bitree *key))
{
    bitree * node;
    queue * linkage, * head;

    if (!root) return ; // if root is NULL, just return;
    
    head = queue_initialize ();
    queue_en (head, root);
    
    while (!queue_isempty (head)){
        linkage = queue_de (head);
        node = (bitree *)(linkage->data);
        
        sfree (linkage);  //saftly free node of queue
        
        access (node);
        if (node->left){
            queue_en (head, node->left);
        }
        if (node->right){
            queue_en (head, node->right);
        }
    }
    queue_destory (head);
}

/*
 * method that free node of tree and user-defined data
 */
void sfree_node (bitree * node)
{
    sfree (node->data); //free user-defined data
    sfree (node); //free node of binary tree
}

/*
 * destory binary tree
 */
void bitree_destory (bitree * root)
{
    bitree_postorder (root, sfree_node);
    size_tree = 0;
}

/*
 * return parent of given node, if no parent, then return NULL
 */
bitree * bitree_parent (bitree * node)
{
    return node ? node->p : NULL;
}

/*
 * return left child of given node, if no left child, then return NULL
 */
bitree * bitree_left (bitree * node)
{
    return node ? node->left : NULL;
}

/*
 * return right child of given node, if no right child, then return NULL
 */
bitree * bitree_right (bitree * node)
{
    return node ? node->right : NULL;
}

/*
 * if given node is left child, then return true, return flase when node is null,
 * or node.p is null(root node), or node isn't left child
 */
bool bitree_isleft (bitree * node)
{
    return node && node->p && node==node->p->left ? true : false;
}

/*
 * if given node is right child, then return true, return flase when node is null,
 * or node.p is null(root node), or node isn't right child
 */
bool bitree_isright (bitree * node)
{
    return node && node->p && node==node->p->right ? true : false;
}

/*
 * return minimum node of binary tree
 */
bitree * bitree_minimum (bitree * root)
{
    bitree * key;
    for (key=root; key && key->left; key=key->left);
    return key;
}

/*
 * return maximum node of binary tree
 */
bitree * bitree_maximum (bitree * root)
{
    bitree * key;
    for (key=root; key && key->right; key=key->right);
    return key;
}

/*
 * return size of binary tree
 */
int bitree_size ()
{
    return size_tree;
}

/*
 * if given is root of binary tree, then return true, else return false
*/
bool bitree_isroot (bitree * node)
{
    return node && !node->p ? true : false;
}

/*
 * if given is leaf of binary tree, then return true, else return false
 */
bool bitree_isleaf (bitree * node)
{
    return node && !node->left && !node->right ? true : false;
}

/*
 * insert a node into binary tree
 * cmp is a function pointer, compair function return valu
 * < return -1, == return 0, > return 1
 */
bitree * bitree_insert (bitree * root, void * data,
                    int (*cmp) (bitree * key, bitree * node))
{
    bitree * node, * tmp, * key;
    
    key = (bitree *) smalloc (sizeof (bitree));
    key->data = data;
    key->left = key->right = NULL; //insert as a leaf or root

    for (node=NULL, tmp=root; tmp!=NULL; ){
        node = tmp;
        tmp = cmp (key, node) < 0 ? node->left : node->right;
    } //find a best position, in order to insert new node.
    
    key->p = node;
    if (node){
        if (cmp (key, node)<0){
            node->left = key;
        }else{
            node->right = key;
        }
    }else{
        root = key; //tree is empty. insert new node as root
    }
    size_tree ++;
    return root;
}

/*
 * delete a node from binary tree
 */
/*
 * In order to move subtrees around within the binary search tree, we define a
 * subroutine transplant, replace node u with node v.
*/
bitree * transplant (bitree * root, bitree * node_u, bitree * node_v)
{
    if (node_u->p==NULL){ //root node
        root = node_v;
    }else if (bitree_isleft (node_u)){
        node_u->p->left = node_v;
    }else{
        node_u->p->right = node_v;
    }
    if (node_v!=NULL){
        node_v->p = node_u->p;
    }
    return root;
}

bitree * bitree_delete (bitree * root, bitree * node)
{
    bitree * tmp;
    
    if (!node) return root; //if node is NULL, do nothing
    
    if (node->left==NULL){
        root = transplant (root, node, node->right);
    }else if (node->right==NULL){
        root = transplant (root, node, node->left);
    }else{
        tmp = bitree_minimum (node->right);
        if (tmp->p!=node){
            root = transplant (root, tmp, tmp->right);
            tmp->right = node->right;
            tmp->right->p = tmp;
        }
        root = transplant (root, node, tmp);
        tmp->left = node->left;
        node->left->p = node;
    }
    sfree (node->data);
    sfree (node);     //free given node
    size_tree --;
    return root; //delete node successful, then return root;
}
