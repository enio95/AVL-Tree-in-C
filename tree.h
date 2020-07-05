#ifndef TREE
#define TREE

#include <stdlib.h>
#include <stdio.h>

#ifndef MINMAX
#define MINMAX

#define MAX(x, y) ( x > y ? x: y )
#define MIN(x, Y) ( x < y ? x: y )

#endif

#define HEIGHT(node) ( node == NULL ? 0: node->height )

/* Data structure of a node.
   elem -> Pointer to a data structure used by the programmer
   height -> Height of the current node
   left -> Left son
   right -> Right son*/
typedef struct Tnode
{
  void *elem;

  int height;

  struct Tnode *left, *right;

}Tnode;

/* Data structure of a Tree
   root -> first element in the tree
   cmp -> compare function used to compare each node
   max -> Biggest elem saved by the tree
   min -> Smallest elem saved by the tree*/
typedef struct Tree
{
  Tnode *root;

  void *max, *min;

  int (*cmp)(const void *a, const void *b);

}Tree;

/* Allocates memory for a new structure Tree. A pointer to a function
   that tells how to compare the elements saved by the tree
   needs to be given and should not be changed though the
   whole use of the tree.
   Compare should return 0 if a==b, <0 if a<b and >0 if a>b  */
Tree* allocTree(int (*cmp)(const void *a, const void *b));

/* Inserts a pointer in the tree. It does not check for
   repeted elements. Returns the pointer of the tree
   Complexity O(log2(n))*/
Tree* insertTree(Tree *tree, void *elem);

/* Returns the height of the tree. If NULL is given as
   argument or the tree is emppty 0 will be returned.
   I made a decision to start counting with 1.
   Complexity O(1)*/
int treeHeight(Tree *tree);

/* Return the max element of the tree. If the Tree is empty
   it shall return NULL.
   Complexity O(1)*/
void* maxTree(Tree *tree);

/* Returns the min element of the tree. If the Tree is empty
   if shall return NULL.
   Complexity O(1)*/
void* minTree(Tree *tree);

/* Searches for an element in the tree that HAS THE SAME IMAGE
   as elem given as argument. If found return the pointer,
   otherwise NULL.
   Complexity O(log2(n))*/
void* searchTree(Tree *tree, void *elem);

/* Tree print*/

enum Order {PREORDER, INORDER, POSTORDER};

/* This function print the tree followng preorder,
   inorder or postorder. You need to specify how.
   A pointer to a function that knows how to print the
   elements saved by the tree needs to be given.
   I would like to remind you, that we are only
   saving pointers and at priori "the code" dosen't
   know how to print.*/
void printTree(Tree *tree, void (*print)(const void *elem), enum Order order);

/* Print all the levels in the tree, one at the time, starting
   with the root.*/
void byLevel(Tree *tree, void (*print)(const void *elem));

#endif
