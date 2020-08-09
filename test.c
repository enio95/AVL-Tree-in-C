#include "avlTree.h"
#include "time.h"

#define TESTNUMBER 10000

int* allocInt(int n)
{
  int *p = (int*)malloc(sizeof(int));

  *p = n;

  return p;
}

int cmp(const void *a, const void *b)
{
  return *(int*)a - *(int*)b;
}

void print(const void *pointer)
{
  if ( pointer == NULL )
    printf("NONE\n");

  else
    printf("%d\n", *(int*)pointer);
}


Atree* insertTest(Atree *tree)
{
  printf("START: Insert Test\n");

  for( int i = TESTNUMBER; i; i-- )
    tree = insertAtree(tree, allocInt(rand()%100000), cmp);

  checkSorted(tree, cmp);
  checkBalanced(tree);

  printf("END: Insert Test\n");

  return tree;
}

Atree* deleteTest(Atree *tree)
{
  printf("START: Delete Test\n");

  int n;

  for( int i = TESTNUMBER/(rand()%100); i; i-- )
    {
      n = rand()%100000;
      tree = deleteAtree(tree, &n, cmp);
    }

  checkSorted(tree, cmp);
  checkBalanced(tree);

  printf("END: Delete Test\n");

  return tree;
}

int main()
{
  Atree *tree = allocAtree();

  srand(time(NULL));
  tree = insertTest(tree);
  tree = deleteTest(tree);

  return 0;
}
