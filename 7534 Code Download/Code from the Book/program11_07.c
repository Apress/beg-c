/* Program 11.7 Sorting integers using a binary tree */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Function prototypes */
struct Node *createnode(long value);                  /* Create a tree node */
struct Node *addnode(long value, struct Node* pNode); /* Insert a new node  */
void listnodes(struct Node *pNode);                   /* List all nodes     */
void freenodes(struct Node *pNode);                   /* Release memory     */

/* Defines a node in a binary tree sotring integers */
struct Node
{
  long item;                 /* The data item            */
  int count;                 /* Number of copies of item */
  struct Node *pLeft;        /* Pointer to left node     */
  struct Node *pRight;       /* Pointer to right node    */
};

/* Function main - execution starts here */
int main(void)
{
  long newvalue = 0;
  struct Node *pRoot = NULL;
  char answer = 'n';
  do
  {
    printf("Enter the node value: ");
    scanf(" %ld", &newvalue);
    if(pRoot == NULL)
      pRoot = createnode(newvalue);
    else
    addnode(newvalue, pRoot);
    printf("\nDo you want to enter another (y or n)? ");
    scanf(" %c", &answer);
  } while(tolower(answer) == 'y');

  printf("The values in ascending sequence are: ");
  listnodes(pRoot);          /* Output the contents of the tree */
  freenodes(pRoot);          /* Release the heap memory         */

  return 0;
}

struct Node *createnode(long value)
{
  struct Node *pNode = (struct Node *)malloc(sizeof(struct Node));
  pNode->item = value;                      /* Set the value          */
  pNode->count = 1;                         /* Set the count          */
  pNode->pLeft = pNode->pRight = NULL;      /* No left or right nodes */
  return pNode;
}

/* Add a new node to the tree */
struct Node *addnode(long value, struct Node* pNode)
{
  if(pNode == NULL)                        /* If there's no node              */
    return createnode(value);              /* ...create one and return it     */

  if(value ==pNode->item)
  {                                        /* Value equals current node       */
    ++pNode->count;                        /* ...so increment count and       */
    return pNode;                          /* ...return the same node         */
  }

  if(value < pNode->item)                  /* If less than current node value */
  {
    if(pNode->pLeft == NULL)               /* and there's no left node        */
    {
      pNode->pLeft = createnode(value);    /* create a new left node and      */
      return pNode->pLeft;                 /* return it.                      */
    }
    else                                   /* If there is a left node...      */
      return addnode(value, pNode->pLeft); /* add value via the left node     */
  }
  else                                     /* value is greater than current   */
  {
    if(pNode->pRight == NULL)              /* so the same process with        */
    {                                      /* the right node.                 */
      pNode-> pRight = createnode(value);
      return pNode-> pRight;
    }
    else
      return addnode(value, pNode-> pRight);
  }
}

/* List the node values in ascending sequence */
void listnodes(struct Node *pNode)
{
  if(pNode->pLeft != NULL)
    listnodes(pNode->pLeft);

  for(int i = 0; i<pNode->count ; i++)
    printf("\n%10ld", pNode->item);

  if(pNode->pRight != NULL)
    listnodes(pNode->pRight);
}

/* Release memory allocated to nodes */
void freenodes(struct Node * pNode)
{
  if(pNode == NULL)                    /* If there's no node...        */
    return;                            /* we are done.                 */

  if(pNode->pLeft != NULL)             /* If there's a left sub-tree   */
    freenodes(pNode->pLeft);           /* free memory for those nodes. */

  if(pNode->pRight != NULL)            /* If there's a right sub-tree  */
    freenodes(pNode->pRight);          /* free memory for those nodes. */

  free(pNode);                         /* Free current node memory     */
}

