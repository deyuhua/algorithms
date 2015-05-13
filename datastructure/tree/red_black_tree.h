/*
 * Auhtor: deyuhua, email: deyuhua@gmail.com
 */

#include "../queue/queue_by_list.h"
//#include "../queue/queue_by_array.h"

//define color node of red-black tree
typedef enum {red=0, black} color;

/*
 * define structure red-black node
 */
struct _treenode {
    struct _treenode * p; //point to parent of node;
    void * key;
    void * info;
    struct _treenode * right; //point to right of node;
    struct _treenode * left; //point to left of node.
    color c;  //mark node with red or black
};
typedef struct _treenode rbtree;

static rbtree * NIL;

/*
 * define structure of tree
 */
struct _tree{
    int size_tree;  //keep size of tree
    rbtree * root; //head of red-black tree;
    rbtree * nil; //nil node of tree
};
typedef struct _tree tree;

/*
 * initialize red-black tree, assign size of tree with zero;
 */
tree * rbtree_initialize ()
{
    rbtree * tmp;
    tree *  t = (tree *) smalloc (sizeof (tree));
    //assign size of tree with zero
    t->size_tree = 0;
    //alloc nil node
    tmp = t->nil = (rbtree *) smalloc (sizeof (rbtree));
    t->nil->left = t->nil->right = t->nil->p = tmp;
    t->nil->key = t->nil->info = NULL;
    t->nil->c = black;    //color of nil node is black, as leaf.
    NIL = t->nil;   //global NIL
    //alloc t of tree
    t->root = (rbtree *) smalloc (sizeof (rbtree));
    t->root->left = t->root->right = t->root->p = NIL;
    t->root->key = t->root->info = NULL;
    t->root->c = black;  //color of head is black, as head.

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
void rbtree_preorder (rbtree * node, void (*access) (rbtree * key))
{
    if (node!=NIL){
        access (node);
        rbtree_preorder (node->left, access);
        rbtree_preorder (node->right, access);
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
void rbtree_inorder (rbtree * node, void (*access) (rbtree * key))
{
    if (node!=NIL){
        rbtree_inorder (node->left, access);
        access (node);
        rbtree_inorder (node->right, access);
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
void rbtree_postorder (rbtree * node, void (*access) (rbtree * key))
{
    if (node!=NIL){
        rbtree_postorder (node->left, access);
        rbtree_postorder (node->right, access);
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
void rbtree_levelorder (rbtree * root, void (*access) (rbtree *key))
{
    rbtree * node;
    queue * linkage, * head;

    //    if (!rbtree_size ()) return ; // if root is NULL, just return;
    
    head = queue_initialize ();
    if (root!=NIL){
        queue_en (head, root);
    }
    
    while (!queue_isempty (head)){
        linkage = queue_de (head);
        node = (rbtree *)(linkage->data);
        
        sfree (linkage);  //saftly free node of queue
        access (node);
        
        if (node->left!=NIL){
            queue_en (head, node->left);
        }
        if (node->right!=NIL){
            queue_en (head, node->right);
        }
    }
    queue_destory (head);
}

/*
 * method that free node of tree and user-defined data
 */
void sfree_node (rbtree * node)
{
    if (node!=NIL){
        sfree (node->key); //free user-defined data
        sfree (node->info);
        sfree (node); //free node of red-black tree
    }
}

/*
 * destory red-black tree
 */
void rbtree_destory (tree * t)
{
    if (t->size_tree!=0){
        rbtree_postorder (t->root->left, sfree_node);
    }
    //free tree node
    sfree (t->nil);  //free nil node of tree
    sfree (t->root);  //free root node of tree
    sfree (t); //free tree node
}

/*
 * if given node is left child, then return true, return flase when node is null,
 * or node.p is null(root node), or node isn't left child
 */
bool rbtree_isleft (rbtree * node)
{
    return node==node->p->left ? true : false;
}

/*
 * if given node is right child, then return true, return flase when node is null,
 * or node.p is null(root node), or node isn't right child
 */
bool rbtree_isright (rbtree * node)
{
    return node==node->p->right ? true : false;
}

/*
 * return minimum node of red-black tree
 */
rbtree * rbtree_minimum (rbtree * subroot)    
{
    rbtree * node = subroot;
    while (node->left!=NIL){
        node = node->left;
    }
    return node;
}

/*
 * return maximum node of red-black tree
 */
rbtree * rbtree_maximum (rbtree * subroot)
{
    rbtree * node = subroot;
    while (node->right!=NIL){
        node = node->right;
    }
    return node;
}

/*
 * if given is root of red-black tree, then return true, else return false
 */
bool rbtree_isroot (rbtree * node)
{
    return node->p==NIL ? true : false;
}

/*
 * if given node is red, then return true, else return false
 */
bool node_isred (rbtree * node)
{
    return node->c==red ? true : false;
}

/*
 * if given node is black, then return true, else return false
 */
bool node_isblack (rbtree * node)
{
    return node->c==black ? true : false;
}

/*
 * rotation change the pointer structure through rotation, which is a
 * local operation in a search tree that preserves the binary-search-tree property
 */
//rotation right to left
void  left_rotation (tree * t, rbtree * node_x)
{
    rbtree * node_y = node_x->right;
    
    node_x->right = node_y->left;
    if (node_y->left!=NIL){
        node_y->left->p = node_x;
    }
    
    node_y->p = node_x->p;
    
    if (node_x->p==NIL){
        t->root->left = node_y;
    }else if (rbtree_isleft (node_x)){
        node_x->p->left = node_y;
    }else{
        node_x->p->right = node_y;
    }
    
    node_y->left = node_x;
    node_x->p = node_y;
}

//rotation left to right
void right_rotation (tree * t, rbtree * node_x)
{
    rbtree * node_y = node_x->left;

    node_x->left = node_y->right;
    if (node_y->right!=NIL){
        node_y->right->p = node_x;
    }
    
    node_y->p = node_x->p;
    
    if (node_x->p==NIL){
        t->root->left = node_y;
    }else if (rbtree_isleft (node_x)){
        node_x->p->left = node_y;
    }else{
        node_x->p->right = node_y;
    }
    
    node_y->right = node_x;
    node_x->p = node_y;
}

void insert_fixup (tree * t, rbtree * node)
{
    rbtree * key;
    while (node->p&&node_isred (node->p)){
        if (rbtree_isleft (node->p)){
            key = node->p->p->right;
            //case 1
            if (node_isred(key)){
                node->p->c = black;
                key->c = black;
                node->p->p->c = red;
                node = node->p->p;
            }else{
                //case 2
                if (rbtree_isright (node)){
                    node = node->p;
                    left_rotation (t, node);
                }
                //case 3
                node->p->c = black;
                node->p->p->c = red;
                right_rotation (t, node->p->p);
            }
        }else{
            key = node->p->p->left;
            //case 1
            if (node_isred(key)){
                node->p->c = black;
                key->c = black;
                node->p->p->c = red;
                node = node->p->p;
            }else{
                //case 2
                if (rbtree_isleft (node)){
                    node = node->p;
                    right_rotation (t, node);
                }
                //case 3
                node->p->c = black;
                node->p->p->c = red;
                left_rotation (t, node->p->p);
            }
        }
    }
    t->root->left->c = black;
}

void rbtree_insert (tree * t, void * key, void * info,
                    int (*cmp) (void * , void * ))
{
    rbtree * node, * tmp, * new;
    
    new = (rbtree *) smalloc (sizeof (rbtree));
    new->key = key;
    new->info = info;
    new->c = red;
    new->left = new->right = NIL; //insert as a leaf or root

    node = NIL;
    tmp = t->root->left;
    while (tmp!=NIL){
        node = tmp;
        tmp = cmp (new->key, node->key) < 0 ? node->left : node->right;
    } //find a best position, in order to insert new node.
    
    new->p = node;
    if (node==NIL){
        t->root->left = new;
    }else if (cmp (new->key, node->key)<0){
        node->left = new;
    }else{
        node->right = new;
    }
    t->size_tree ++;
    insert_fixup (t, new);
}

/*
 * delete a node from red-black tree
 */
/*
 * In order to move subtrees around within the red-black search tree, we define a
 * subroutine transplant, replace node u with node v.
 */
void transplant (tree * t, rbtree * node_u, rbtree * node_v)
{
    if (node_u==t->root->left){
        t->root->left = node_v;
    }else if (rbtree_isleft (node_u)){
        node_u->p->left = node_v;
    }else{
        node_u->p->right = node_v;
    }
    //change node_v's parent when node_v is not NIL
    if (node_v!=NIL){
        node_v->p = node_u->p;
    }
}

void delete_fixup (tree * t, rbtree * node_fixup)
{
    rbtree * w;
    rbtree * root = t->root->left;
    while (node_fixup!=root&&node_isblack (node_fixup)){
        if (rbtree_isleft (node_fixup)){
            w = node_fixup->p->right;
            //case 1
            if (node_isred (w)){
                w->c = black;
                node_fixup->p->c = red;
                left_rotation (t, node_fixup->p);
                w = node_fixup->p->right;
            }
            //case 2
            if (node_isblack (w->right) && node_isblack (w->left)){
                w->c = red;
                node_fixup = node_fixup->p;
            }else{
                //case 3
                if (node_isblack (w->right)){
                    w->left->c = black;
                    w->c = red;
                    right_rotation (t, w);
                    w = node_fixup->p->right;
                }
                //case 4
                w->c = node_fixup->p->c;
                node_fixup->p->c = black;
                w->right->c = black;
                left_rotation (t, node_fixup->p);
                node_fixup = root; //this is exit to while loop
            }
        }else{
            w = node_fixup->p->left;
            //case 1
            if (node_isred (w)){
                w->c = black;
                node_fixup->p->c = red;
                right_rotation (t, node_fixup->p);
                w = node_fixup->p->left;
            }
            //case 2
            if (node_isblack (w->left) && node_isblack (w->right)){
                w->c = red;
                node_fixup = node_fixup->p;
            }else{
                //case 3
                if (node_isblack (w->left)){
                    w->right->c = black;
                    w->c = red;
                    left_rotation (t, w);
                    w = node_fixup->p->left;
                }
                //case 4
                w->c = node_fixup->p->c;
                node_fixup->p->c = black;
                w->left->c = black;
                right_rotation (t, node_fixup->p);
                node_fixup = root;  //this is to exit while loop
            }
        }
    }
    node_fixup->c = black;
}

void rbtree_delete (tree * t, rbtree * node)
{
    rbtree * rep = node;
    rbtree * node_fixup;  //hold node that need to fixup;
    
    if (t->size_tree==0) return ; //if tree is empty, just return 

    color node_original_color = rep->c;
    
    if (node->left==NIL){
        node_fixup = node->right;
        transplant (t, node, node->right);
    }else if (node->right==NIL){
        node_fixup = node->left;
        transplant (t, node, node->left);
    }else{
        rep = rbtree_minimum (node->right);
        node_original_color = rep->c;
        node_fixup = rep->right;
        if (rep->p==node){
                node_fixup->p = rep;
        }else{
            transplant (t, rep, rep->right);
            rep->right = node->right;
            rep->right->p = rep;
        }
        transplant (t, node, rep);
        rep->left = node->left;
        rep->left->p = rep;
        rep->c = node->c;
        if (node_original_color == black){
            delete_fixup (t, node_fixup);
        }
    }
    if (node!=NIL){
        sfree_node (node);
        t->size_tree --;
    }
    t->root->left->c = black;
    t->nil->c = black;
}
