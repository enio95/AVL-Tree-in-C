#include "tree.h"
#include <time.h>

void myPrint(const void *elem)
{
  if ( elem!=NULL )
    printf("%d\n",*(int*)elem);

  else
    printf("NULL\n");
}

int myCmp(const void *a, const void *b)
{
  return *(int*)a - *(int*)b;
}

int myCmp2(const void *a, const void *b)
{
  return *(int*)a - *(int*)b;
}

int* newInt(int n)
{
  int *temp = (int*)malloc(sizeof(int));

  *temp = n;

  return temp;
}

void myFree(int *n)
{
  free(n);
}

int main()
{
  srand(time(NULL));

  Tree *tree = allocTree(myCmp);

  for( int i=0; i<10; i++ )
    insertTree(tree, newInt(rand()%20));

  //byLevel(tree, myPrint);

  myPrint(maxTree(tree));
  myPrint(minTree(tree));

  /* preOrderTree(tree, myPrint); */
  /* inOrderTree(tree, myPrint); */
  /* postOrderTree(tree, myPrint); */
  byLevel(tree, myPrint);

  myPrint(searchTree(tree, newInt(3)));

  tree->cmp = myCmp2;

  return 0;
}
