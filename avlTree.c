#include "avlTree.h"

/*================LOCAL FUNCTIONS DECLARATION================*/

/* START: Alloc memory for a new node and returns its pointer,
   on fail returns NULL. Atention it should be resposibility of
   the programmer to safely dispose of the memory allocated in
   the pointer in case it fails to allocate a new node*/
static Anode* allocAnode(void *pointer);
/* END:*/

/* START: Returns the height of the node.*/
static int heightAnode(Anode *node);
/* END:*/

/* START: Return the differentce of the height beteween the left and
   right son. */
static int difAnode(Anode *node);
/* END:*/

/* START: Calculates nad updates the height and difference of a given node. */
static void hdAupdate(Anode *node);
/* END:*/

/* START: Balance the tree using height difference as a classificator
   for left or right rotations. */
static Anode *balanceAtree(Anode *node);
/* END:*/

/* START: Rotates a node to the left and updates the new height and dif. */
static Anode* leftRotate(Anode *node);

/* START: Rotates a node to the rightand updates the new height and dif. */
static Anode* rightRotate(Anode *node);

/* START: Searches for a node that contains a pointer that has the same
   image as the pointer given in the arguments. */
static Anode* searchAnode(Anode *node, void *pointer, int (*cmp)(const void *a, const void *b));
/* END:*/

/* START: Aux function for the printAtree/2. This function has the same concept as
   iterative deepening, meaning that we print every ponter at level 0 then at level 1
   and so on. Like iterative deepening the time complexety is dominated by the
   height of the tree. */
static void auxPrintAtree(Anode *node, int level, int cur, void (*print)(const void *pointer));
/* END:*/

/* START: Return the right most node of the tree. On fail return NULL.*/
static Anode* rightMostAnode(Anode *node);
/* END:*/

/* START: Returns the left most node of the tree. On fail return NULL. */
static Anode* leftMostAnode(Anode *node);
/* END:*/

/* START: Aux function of deleteAtree/3. This function is recursive in order to
   avoid having a list of nodes that will be affected by a deletion of a node. */
static Anode* auxDeleteAtree(Anode *node, void *pointer, int (*cmp)(const void *a, const void *b));
/* END:*/

/* START: Aux function of auxDeleteAtree/3. Basically we find the suitable node to
   replace the one we want to remove and then update the tree. */
static Anode* replaceAnode(Anode *node);
/* END:*/


/*================IMPLEMENTATION================*/
Atree* allocAtree()
{
  Atree *temp = (Atree*)calloc(1, sizeof(Atree));

  if ( temp == NULL )
    perror("allocAtree");

  else
    temp->height = -1;

  return temp;
}


static Anode* allocAnode(void *pointer)
{
  Anode *temp = (Anode*)calloc(1, sizeof(Anode));

  if ( temp == NULL )
    perror("allocAnode");

  else
    temp->pointer = pointer;

  return temp;
}


Atree* insertAtree(Anode *node, void *pointer, int (*cmp)(const void *a, const void *b))
{
  if ( node == NULL )
    node = allocAnode(pointer);

  else if ( node->height == -1 )
    {
      free(node);
      node = allocAnode(pointer);
    }

  else if ( cmp(node->pointer, pointer) <= 0 )
    node->right = insertAtree(node->right, pointer, cmp);

  else
    node->left = insertAtree(node->left, pointer, cmp);

  return balanceAtree(node);
}

int heightAtree(Atree *tree) { return heightAnode(tree); }

static int heightAnode(Anode *node) { return node == NULL ? -1: node->height; }

int heightAtree1(Atree *tree)
{
  if ( tree == NULL )
    return -1;

  else
    return MAX(heightAtree1(tree->left), heightAtree1(tree->right)) + 1;
}

static int difAnode(Anode *node) { return node == NULL ? 0: node->dif; }

static void hdAupdate(Anode *node)
{
  if ( node == NULL )
    return;

  int l = heightAnode(node->left), r = heightAnode(node->right);

  node->height = MAX(l, r) + 1;
  node->dif = l - r;
}

static Anode *balanceAtree(Anode *node)
{
  hdAupdate(node);

  if ( difAnode(node) > -2 && difAnode(node) < 2 )
    return node;

  else if ( difAnode(node) > 1 )
    {
      if ( difAnode(node->left) < 0 )
	node->left = leftRotate(node->left);

      return rightRotate(node);
    }

  else
    {
      if ( difAnode(node->right) > 0 )
	node->right = rightRotate(node->right);

      return leftRotate(node);
    }
}

static Anode* leftRotate(Anode *node)
{
  Anode *temp = node->right;

  node->right = temp->left;

  temp->left = node;

  hdAupdate(node);
  hdAupdate(temp);

  return temp;
}

static Anode* rightRotate(Anode *node)
{
  Anode *temp = node->left;

  node->left = temp->right;

  temp->right = node;

  hdAupdate(node);
  hdAupdate(temp);

  return temp;
}

static Anode* searchAnode(Anode *node, void *pointer, int (*cmp)(const void *a, const void *b))
{
  if ( node == NULL )
    return node;

  int cmpValue = cmp(node->pointer, pointer);

  if ( cmpValue < 0 )
    return searchAnode(node->right, pointer, cmp);

  else if ( cmpValue > 0 )
    return searchAnode(node->left, pointer, cmp);

  else
    return node;
}

void* searchAtree(Anode *node, void *pointer, int (*cmp)(const void *a, const void *b))
{
  Anode *temp = searchAnode(node, pointer, cmp);

  return temp == NULL ? NULL: temp->pointer;
}

void printAtree(Atree *tree, void (*print)(const void *pointer))
{
  printf("START:\n");

  for( int i=0; tree != NULL && i <= heightAtree(tree); i++ )
    {
      printf("LEVEL %d\n", i);

      auxPrintAtree(tree, i, 0, print);
    }

  printf("END:\n\n");
}

static void auxPrintAtree(Anode *node, int level, int cur, void (*print)(const void *pointer))
{
  if ( node == NULL )
    return;

  if ( cur == level )
    print(node->pointer);

  else
    {
      auxPrintAtree(node->left, level, ++cur, print);
      auxPrintAtree(node->right, level, cur, print);
    }
}

static Anode* leftMostAnode(Anode *node)
{
  if ( node == NULL )
    return NULL;

  else if ( node->left != NULL )
    return leftMostAnode(node->left);

  else
    return node;
}

static Anode* rightMostAnode(Anode *node)
{
  if ( node == NULL )
    return NULL;

  else if ( node->right != NULL )
    return rightMostAnode(node->right);

  else
    return node;
}

void* leftMostAtree(Anode *tree)
{
  Anode *temp = leftMostAnode(tree);

  return temp == NULL ? NULL : temp->pointer;
}

void* rightMostAtree(Anode *tree)
{
  Anode *temp = rightMostAnode(tree);

  return temp == NULL ? NULL : temp->pointer;
}

void* minAtree(Anode *tree) { return leftMostAtree(tree); }
void* maxAtree(Anode *tree) { return rightMostAtree(tree); }

Atree* deleteAtree(Atree *tree, void *pointer, int (*cmp)(const void *a, const void *b))
{
  if ( searchAtree(tree, pointer, cmp) == NULL )
    return tree;

  return balanceAtree(auxDeleteAtree(tree, pointer, cmp));
}

static Anode* auxDeleteAtree(Anode *node, void *pointer, int (*cmp)(const void *a, const void *b))
{
  int cmpValue = cmp(node->pointer, pointer);

  if ( cmpValue < 0 )
    node->right = auxDeleteAtree(node->right, pointer, cmp);

  else if ( cmpValue > 0 )
    node->left = auxDeleteAtree(node->left, pointer, cmp);

  /* Case where the current node contains the pointer to delete but has no right branch,
     in this case we simply substitute the current node by its left son. */
  else if ( node->right == NULL )
    {
      Anode *t0 = node;
      node = node->left;
      free(t0);
    }

  /* Case where the current node contains the pointer and has a right branch, in this case
     we call a function to replace the node. A little more work is required. */
  else
    {
      node->pointer = leftMostAtree(node->right);
      node->right = replaceAnode(node->right);
    }

  return balanceAtree(node);
}

static Anode* replaceAnode(Anode *node)
{
  if ( node->left == NULL )
    {
      Anode *t0 = node->right;
      free(node);
      node = t0;
    }

  else
    node->left = replaceAnode(node->left);

  return balanceAtree(node);
}

Atree* deleteAtree1(Atree *tree, void *pointer, int (*cmp)(const void *a, const void *b), void (*freeP)(void *a))
{
  void *t0 = searchAtree(tree, pointer, cmp);

  if ( t0 == NULL )
    return tree;

  freeP(t0);

  return balanceAtree(auxDeleteAtree(tree, pointer, cmp));
}

void checkSorted(Anode *node, int (*cmp)(const void *a, const void *b))
{
  if ( node == NULL )
    return;

  if ( node->left != NULL && cmp(node->pointer, node->left->pointer) >= 0 )
    return checkSorted(node->left, cmp);

  else if ( node->left != NULL )
    {
      printf("FAILED check sorted\n");
      exit(EXIT_FAILURE);
    }

  if ( node->right != NULL && cmp(node->pointer, node->right->pointer) <= 0 )
    return checkSorted(node->right, cmp);

  else if ( node->right != NULL )
    printf("FAILED check sorted\n");
}

void checkBalanced(Anode *node)
{
  if ( node == NULL )
    return;

  else
    {
      int h = heightAtree1(node);
      int d =  heightAtree1(node->left) - heightAtree1(node->right);

      if ( h != heightAtree(node) || d != difAnode(node) || d > 2 || d < -2 )
	printf("FAILED check balance\n");

      checkBalanced(node->left);
      checkBalanced(node->right);
    }
}
