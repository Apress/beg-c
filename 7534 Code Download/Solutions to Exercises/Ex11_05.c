/* Exercise 11.5 Sorting names using a binary tree */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const int FIRST_MAX = 30;
const int SECOND_MAX = 50;


/* Defines a name */
typedef struct NName
{
  char first[FIRST_MAX];
  char second[SECOND_MAX];
} Name;

/* Defines a node in a binary tree sotring integers */
typedef struct NNode
{
  Name *pName;                /* Pointer to a name        */
  int count;                  /* Number of copies of item */
  struct NNode *pLeft;        /* Pointer to left node     */
  struct NNode *pRight;       /* Pointer to right node    */
} Node;

/* Function prototypes */
Name *readname();                                     /* Read a name        */
int compare(Name *pName1, Name *pName2);              /* Compare names      */
void printname(Name *pName);                          /* Output a name      */
Node *createnode(Name *pName);                        /* Create a tree node */
Node *addnode(Name *pName, Node* pNode);              /* Insert a new node  */
void listnodes(Node *pRootNode);                      /* List all nodes     */
void freenodes(Node *pRootNode);                      /* Release memory     */


/* Function main - execution starts here */
int main(void)
{
  Name *pNewName = NULL;
  Node *pRoot = NULL;
  char answer = 'n';
  do
  {
    pNewName = readname();
    if(!pRoot)
      pRoot = createnode(pNewName);
    else
    addnode(pNewName, pRoot);
    printf("\nDo you want to enter another (y or n)? ");
    scanf(" %c", &answer);
    fflush(stdin);                    /* Get rid of the newline */
  } while(tolower(answer) == 'y');

  printf("The names in ascending sequence are:\n");
  listnodes(pRoot);          /* Output the contents of the tree */
  freenodes(pRoot);          /* Release the heap memory         */

  return 0;
}

/*****************************************
 * Creates a Name object on the heap and *
 * reads the first and second names from *
 * stdin.                                *
 * The freenodes() function takes care   *
 * of releasing the memory for names.    *
 *****************************************/
Name *readname()
{
  Name *pName = malloc(sizeof(Name));
  printf("Enter the first name: ");
  fgets(pName->first, FIRST_MAX, stdin);
  size_t len = strlen(pName->first);
  if(pName->first[len-1] == '\n')     /* If there's a newline at the end */
    pName->first[len-1] = '\0';       /* overwrite it.                   */

  printf("Enter the second name: ");
  fgets(pName->second, SECOND_MAX, stdin);
  len = strlen(pName->second);
  if(pName->second[len-1] == '\n')    /* If there's a newline at the end */
    pName->second[len-1] = '\0';      /* overwrite it.                   */
  return pName;
}

/*************************************************
 * Creates a new node on the heap that contains  *
 * the pointer to the name that is passed as     *
 * the argument.                                 *
 *************************************************/
Node *createnode(Name *pName)
{
  Node *pNode = (Node *)malloc(sizeof(Node));
  pNode->pName = pName;                     /* Set the name           */
  pNode->count = 1;                         /* Set the count          */
  pNode->pLeft = pNode->pRight = NULL;      /* No left or right nodes */
  return pNode;
}

/* Add a new node to the tree */
Node *addnode(Name *pName, Node* pNode)
{
  if(!pNode)                               /* If there's no node              */
    return createnode(pName);              /* ...create one and return it     */

  if(compare(pName, pNode->pName) == 0)
  {                                        /* Name equals current node        */
    ++pNode->count;                        /* ...so increment count and       */
    return pNode;                          /* ...return the same node         */
  }

  if(compare(pName, pNode->pName) < 0)     /* If less than current node name  */
  {
    if(!pNode->pLeft)                      /* and there's no left node        */
    {
      pNode->pLeft = createnode(pName);    /* create a new left node and      */
      return pNode->pLeft;                 /* return it.                      */
    }
    else                                   /* If there is a left node...      */
      return addnode(pName, pNode->pLeft); /* add value via the left node     */
  }
  else                                     /* value is greater than current   */
  {
    if(!pNode->pRight)                     /* so the same process with        */
    {                                      /* the right node.                 */
      pNode->pRight = createnode(pName);
      return pNode-> pRight;
    }
    else
      return addnode(pName, pNode->pRight);
  }
}

/**********************************************
 * Lists the node names in ascending sequence *
 **********************************************/
void listnodes(Node *pNode)
{
  if(pNode->pLeft)
    listnodes(pNode->pLeft);

  for(int i = 0; i<pNode->count ; i++)
    printname(pNode->pName);

  if(pNode->pRight)
    listnodes(pNode->pRight);
}

/*************************************
 * Release memory allocated to nodes *
 * including the memory for the name *
 * referenced by the pName member of *
 * each node.                        *
 *************************************/
void freenodes(Node * pNode)
{
  if(!pNode)                           /* If there's no node...        */
    return;                            /* we are done.                 */

  if(pNode->pLeft)                     /* If there's a left sub-tree   */
    freenodes(pNode->pLeft);           /* free memory for those nodes. */

  if(pNode->pRight)                    /* If there's a right sub-tree  */
    freenodes(pNode->pRight);          /* free memory for those nodes. */

  free(pNode->pName);                  /* Release name memory          */
  free(pNode);                         /* then current node memory     */
}

/***************************
 * Write a name to stdout. *
 ***************************/
void printname(Name *pName)
{
  printf("%s %s\n", pName->first, pName->second);
}

/*********************************************
 * Compare two Name objects.                 *
 * IF the second names are not equal, return *
 * the result of comparing them. Otherwise   *
 * return the result of comparing the first  *
 * members of the Name objects.              *
 *********************************************/
int compare(Name *pName1, Name *pName2)
{
  int result = strcmp(pName1->second, pName2->second);
  if(result != 0)
    return result;
  return strcmp(pName1->first, pName2->first);
}
