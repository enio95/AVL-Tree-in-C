#include "tree.h"

/*======================LOCAL FUNCTIONS========================*/

/* Allocates memory for a new node and returns its pointer.
   The new data structure will save the address given in
   as argument, elem. There is no need for other functions
   to call allocTnode. Only insert should*/
static Tnode* allocTnode(void *elem);

/* balanceTree should only be used in insert and delete.
   It balances a tree depending of the subraction of
   the height of its sons. Cheks conditions in the if
   statements to know more about which rotations to
   execute.*/
static Tnode* balanceTree(Tnode *node, int value);

/* Left and Right rotate should only be used in balanceTree that
   and balanceTree should only be called by insert and delete.*/
static Tnode* leftRotate(Tnode *node);
static Tnode* rightRotate(Tnode *node);

/* Returns the height of the node, the counting starts
   at 1. If a NULL pointer is given, it will return 0*/
static int getHeight(Tnode *node);

/* Returns the balance of the node, which is calculated by
   subtracting the height of the left son by the height of
   the right son*/
static int balanceOutput(Tnode *node);

/*=============LOCAL AND AUXILIARY FUNCTIONS======================*/

/* Auxiliary function should only be used by their "parent" functions.*/
static Tnode* auxInsertTree(Tnode *node, void *elem, int (*cmp)(const void *a, const void *b));

static char* decodeOrder(enum Order val);
static void auxPrintTree(Tnode *node, void (*print)(const void *elem), enum Order val);

static void auxByLevel(Tnode *node, int cur, int lim, void (*print)(const void *elem));

/*=======================THE ACTUAL CODE=========================*/

/*-------------------------ALLOCATE------------------------------*/
Tree *allocTree(int (*cmp)(const void *a, const void *b))
{
  Tree *tree = (Tree*)calloc(1, sizeof(Tree));

  if ( tree == NULL )
    perror("allocTree");

  tree->cmp = cmp;

  return tree;
}

static Tnode* allocTnode(void *elem)
{
  Tnode *node = (Tnode*)calloc(1, sizeof(Tnode));

  if ( node == NULL )
    {
      perror("allocTnode");
      return NULL;
    }

  node->elem = elem;

  node->height = 0;

  return node;
}

/*---------------------------INSERT-------------------------*/
Tree* insertTree(Tree *tree, void *elem)
{
  tree->root = auxInsertTree(tree->root, elem, tree->cmp);

  tree->root->height = getHeight(tree->root);

  tree->root = balanceTree(tree->root, balanceOutput(tree->root));

  tree->min = tree->min == NULL ? elem: ( tree->cmp(tree->min, elem) > 0 ? elem: tree->min );

  tree->max = tree->max == NULL ? elem: ( tree->cmp(tree->max, elem) <= 0 ? elem: tree->max );

  return tree;
}

static Tnode* auxInsertTree(Tnode *node, void *elem, int (*cmp)(const void *a, const void *b))
{
  if ( node == NULL )
    return allocTnode(elem);

  else if ( cmp(node->elem, elem) > 0 )
    node->left = auxInsertTree(node->left, elem, cmp);

  else
    node->right = auxInsertTree(node->right, elem, cmp);

  node->height = getHeight(node);

  return balanceTree(node, balanceOutput(node));
}

/* --------------------------BALANCE TREE---------------------------*/
static Tnode* balanceTree(Tnode *node, int value)
{
  if ( value > -2 && value < 2 )
    return node;

  else if ( value > 1 )
    {
      if ( balanceOutput(node->left) < 0 )
	node->left = leftRotate(node->left);

      return rightRotate(node);
    }

  else
    {
      if ( balanceOutput(node->right) > 0 )
	node->right = rightRotate(node->right);

      return leftRotate(node);
    }
}

static Tnode* leftRotate(Tnode *node)
{
  Tnode *temp = node->right;

  node->right = temp->left;

  temp->left = node;

  node->height = getHeight(node);
  temp->height = getHeight(temp);

  return temp;
}

static Tnode* rightRotate(Tnode *node)
{
  Tnode *temp = node->left;

  node->left = temp->right;

  temp->right = node;

  node->height = getHeight(node);
  temp->height = getHeight(temp);

  return temp;
}

int treeHeight(Tree *tree) { return tree == NULL ? 0: getHeight(tree->root); }

static int getHeight(Tnode *node)
{
  return node == NULL ? 0: MAX(HEIGHT(node->left), HEIGHT(node->right)) + 1;
}

static int balanceOutput(Tnode *node)
{
  return node == NULL ? 0: HEIGHT(node->left) - HEIGHT(node->right);
}

/*-------------------------Min of the tree----------------*/
void* minTree(Tree *tree) { return tree == NULL ? NULL: tree->min; }

/*---------------------Max of tree------------------------*/
void* maxTree(Tree *tree) { return tree == NULL ? NULL: tree->max; }

/*------------------------SEARCH--------------------------*/
void* searchTree(Tree *tree, void *elem)
{
  int cmpValue;

  Tnode *cur = tree == NULL ? NULL: tree->root;

  while ( cur != NULL && (cmpValue = tree->cmp(cur->elem, elem)) != 0)
    cur = cmpValue > 0 ? cur->left: cur->right;

  return cur == NULL ? NULL: cur->elem;
}

/*--------------------------PRINT-------------------------*/
void printTree(Tree *tree, void (*print)(const void *elem), enum Order order)
{
  printf("Start of %s\n", decodeOrder(order));

  if ( tree != NULL )
    auxPrintTree(tree->root, print, order);

  printf("End of %s\n", decodeOrder(order));
}

static char* decodeOrder(enum Order order)
{
  return order == PREORDER ? "PreOrder": ( order == INORDER ? "InOrder": "PostOrder");
}

static void auxPrintTree(Tnode *node, void (*print)(const void *elem), enum Order order)
{
  if ( node == NULL )
    return;

  switch( order )
    {
    case PREORDER:
      print(node->elem);
      auxPrintTree(node->left, print, order);
      auxPrintTree(node->right, print, order);
      break;

    case INORDER:
      auxPrintTree(node->left, print, order);
      print(node->elem);
      auxPrintTree(node->right, print, order);
      break;

    default:
      auxPrintTree(node->left, print, order);
      auxPrintTree(node->right, print, order);
      print(node->elem);
      break;
    }
}

void byLevel(Tree *tree, void (*print)(const void *elem))
{
  printf("Start of byLevel\n");

  for( int i=0; i <= getHeight(tree->root); i++ )
    {
      printf("Level %d\n", i);

      auxByLevel(tree->root, 0, i, print);
    }

  printf("End of byLevel\n\n");
}

static void auxByLevel(Tnode *node, int cur, int lim, void (*print)(const void *elem))
{
  if ( cur > lim )
    return;

  else if ( node == NULL )
    return;

  else if ( cur == lim )
    print(node->elem);

  else
    {
      auxByLevel(node->left, ++cur, lim, print);
      auxByLevel(node->right, cur, lim, print);
    }
}
