/*
 * Auhtor: deyuhua, email: deyuhua@gmail.com
 */

#include "../queue/queue_by_list.h"
//#include "../queue/queue_by_array.h"

/*
 * define structure binary tree
 */
struct _treenode {
    struct _treenode * p; //point to parent of node;
    void * key; 
    void * info; 
    struct _treenode * right; //point to right of node;
    struct _treenode * left; //point to left of node.
};
typedef struct _treenode bitree;

/*
 * define structure of tree
 */
struct _tree {
    int size_tree;  //keep size of tree
    bitree * root;  //head of binary tree
};
typedef struct _tree tree;

/*
 * initialize binary tree, assign size of tree with zero;
 */
tree * bitree_initialize ()
{
    //allocate tree info 
    tree * t = (tree *) smalloc (sizeof (tree));
    // allocte head of tree
    t->root = (bitree *) smalloc (sizeof (bitree));
    t->root->left = t->root->right = t->root->p = NULL;
    //    t->root->data = NULL;
    t->root->key = t->root->info = NULL;
    //assign size of tree with zero
    t->size_tree = 0;
    
    return t;
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
        
        sfree (linkage); 
        
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
    sfree (node->key);
    sfree (node->info);
    sfree (node); //free node of binary tree
}

/*
 * destory binary tree
 */
void bitree_destory (tree * t)
{
    bitree_postorder (t->root->left, sfree_node);
    sfree (t);  //free tree node
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
    return node && node==node->p->left ? true : false;
}

/*
 * if given node is right child, then return true, return flase when node is null,
 * or node.p is null(root node), or node isn't right child
 */
bool bitree_isright (bitree * node)
{
    return node && node==node->p->right ? true : false;
}

/*
 * return minimum node of binary tree
 */
bitree * bitree_minimum (bitree * subroot)
{
    bitree * key = subroot;
    while (key&&key->left){
        key = key->left;
    }
    return key;
}

/*
 * return maximum node of binary tree
 */
bitree * bitree_maximum(bitree * subroot)
{
    bitree * key;
    while (key&&key->right){
        key = key->right;
    }
    return key;
}

/*
 * insert a node into binary tree
 * cmp is a function pointer, compair function return valu
 * < return -1, == return 0, > return 1
 */
void bitree_insert (tree * t, void * key, void * info,
                    int (*cmp) (void *, void *))
{
    bitree * node, * tmp, * new;
    
    new = (bitree *) smalloc (sizeof (bitree));
    new->key = key;
    new->info = info;
    new->left = new->right = NULL; //insert as a leaf or root

    for (node=NULL, tmp=t->root->left; tmp!=NULL; ){
        node = tmp;
        tmp = cmp (new->key, node->key) < 0 ? node->left : node->right;
    } //find a best position, in order to insert new node.
    
    new->p = node;
    if (node){
        if (cmp (new->key, node->key)<0){
            node->left = new;
        }else{
            node->right = new;
        }
    }else{
        t->root->left = new; //tree is empty. insert new node as root
    }
    t->size_tree ++;
}

/*
 * delete a node from binary tree
 */
/*
 * In order to move subtrees around within the binary search tree, we define a
 * subroutine transplant, replace node u with node v.
*/
void transplant (tree * t, bitree * node_u, bitree * node_v)
{
    if (node_u==t->root->left){ //root node
        t->root->left = node_v;
    }else if (bitree_isleft (node_u)){
        node_u->p->left = node_v;
    }else{
        node_u->p->right = node_v;
    }
    if (node_v!=NULL){
        node_v->p = node_u->p;
    }
}

bitree * bitree_delete (tree * t, bitree * node)
{
    bitree * tmp;
    
    if (t->size_tree==0) return NULL; 

    if (node->left==NULL){ //case one
        transplant (t, node, node->right);
    }else if (node->right==NULL){  //case two
        transplant (t, node, node->left);
    }else{  //case there
        tmp = bitree_minimum (node->right);
        if (tmp->p!=node){
            transplant (t, tmp, tmp->right);
            tmp->right = node->right;
            tmp->right->p = tmp;
        }
        transplant (t, node, tmp);
        tmp->left = node->left;
        node->left->p = node;
    }
    t->size_tree --;
    return node;
}
