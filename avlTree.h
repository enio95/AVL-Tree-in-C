#ifndef AVLTREE
#define AVLTREE

#include <stdio.h>
#include <stdlib.h>

/*================START: IMPORTANT NOTE================*/
/* Be carefull with the compare function used to insert and delete elements.
   Whatever compare you chose, be consistent in the output.
   Its recommended that the compare function behaves like the following examples:
   compare(a, b) < 0 if a < b
   compare(a, b) > 0 if a > b
   compare(a, b) == 0 if a == b

   PS: Sory for my bad english! Its not my first language.*/
/*================END: IMPORTANT NOTE================*/

/* START: Macro for min and max. */
#ifndef MINMAX
#define MINMAX

#define MAX(x, y) ( x > y ? x: y )
#define MIN(x, Y) ( x < y ? x: y )

#endif
/* END: Macro for min and max. */

/* START: AVL Tree data structure.
   pointer -> Pointer to a data structure given by the programmer.
   left/right -> left and right branches.
   Height -> Height of the node
   dif -> Difference of the height between the right and left sons*/
typedef struct Anode
{
  void *pointer;

  int height, dif;

  struct Anode *left, *right;

}Anode, Atree;
/* END: AVL Tree data structure. */

/* START: Allocates memory for a new AVL Tree and returns its
   pointer, on fail returns NULL.*/
Atree* allocAtree();
/* END: */

/* START: Insert a pointer in the tree. It does not check for
   repeted elements. Returns the pointer of the tree.
   A pointer to a function that KNOWS how to compare the pointers
   saved in the tree has to be given and its responsability of the
   programmer to make sure the correct function is passed.*/
Atree* insertAtree(Atree *tree, void *pointer, int (*cmp)(const void *a, const void *b));
/* END: */

/* START: Searches for an element in the tree that HAS THE SAME IMAGE as the pointer
   passed in the arguments. On success return the pointer saved, on fail return NULL.*/
void* searchAtree(Atree *tree, void *pointer, int (*cmp)(const void *a, const void *b));
/* END: */

/* START: Returns the height of the tree. We start counting at zero
   meaning that if a NULL pointer was passed or the tree is empty
   it shall return -1.*/
int heightAtree(Atree *tree);
/* END: */

/* START: Return the height of the Tree. This function is similar to
   heightAtree/1 but its more costly */
int heightAtree1(Atree *tree);
/* END: */

/* START: Print an AVL tree by level. A pointer to a function that
   knows how to print needs to be defined and passed by the
   programmer*/
void printAtree(Atree *tree, void (*print)(const void *pointer));
/* END: */

/* STAR: Return the pointer at the left most part of the tree.
   On fail return NULL. */
void* leftMostAtree(Atree *tree);
/* END: */

/* START: Return the pointer at the right most part of the tree.
   On fail return NULL.*/
void* rightMostAtree(Atree *tree);
/* END: */

/* START: Returns the min element of the tree. Please read the note
   in the begining about the compare function used to build the tree,
   to make sure it actually gives the minimum. On fail return NULL. */
void* minAtree(Atree *tree);
/* END: */

/* START: Returns the max element of the tree. Please read the note
   in the begining about the compare function used to build the tree,
   to make sure it actually gives the minimum. On fail return NULL. */
void* maxAtree(Atree *tree);

/* START: Delete the first element found in the tree that HAS THE SAME IMAGE
   as the pointer passed in the arguments. This function does not free memory
   allocated in the pointer and is resposibility of the programmer to do so.
   This function does not return the pointer removed, in order to avoid
   having a memory leak its recomended to first search for the element to
   remove and then remove it by calling this function followed by a free(). */
Atree* deleteAtree(Atree *tree, void *pointer, int (*cmp)(const void *a, const void *b));
/* END: */

/* START: Delete the first element found in the tree that HAS THE SAME IMAGE
   as the pointer passed in the arguments. This function free memory saved by the
   pointer removed, but a function that know how to free the memory allocated needs
   to be given.*/
Atree* deleteAtree1(Atree *tree, void *pointer, int (*cmp)(const void *a, const void *b), void (*freeP)(void *a));
/* END: */

/* START: Function frees memory allocated for the tree and for every pointer saved.
   A function on how to free each pointer need to be defined and passed as
   argument by the porgrammer.*/
void freeAtree(Atree *tree, void (*freeP)(void *a));
/* END: */

/* START: Check if the AVL tree is sorted. On fail, a print message is printed*/
void checkSorted(Atree *tree, int (*cmp)(const void *a, const void *b));
/* END: */

/* START: Check if the AVL tree is Balanced. On fail, a print message is printed*/
void checkBalanced(Atree *tree);
/* END: */

#endif
