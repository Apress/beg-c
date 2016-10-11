/* Exercise 11.3 Using a linked list of structures representing a person's name. */
/*
   You could link the PhoneRecord structures in a list by adding a pointer member.
   I chose to define a Node structure that is a node in a linked list. Each Node
   structure will contain a pointer to a PhoneRecord structure and a pointer to
   the next Node structure. Memory for Node and PhoneRecord structures are allocated
   dynamically. You could extend this to allocate memory for names and numbers too.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define FIRST_NAME_LEN  31
#define SECOND_NAME_LEN 51
#define NUMBER_LEN      16


/* Structure defining a name */
struct Name
{
  char firstname[FIRST_NAME_LEN];
  char secondname[SECOND_NAME_LEN];
};

/* Structure defining a phone record */
struct PhoneRecord
{
  struct Name name;
  char number[NUMBER_LEN];
};

/* Structure defining a node in a linked list of PhoneRecord structures */
struct Node
{
  struct PhoneRecord *pRecord;     /* Pointer to a PhoneRecord structure   */
  struct Node *pNext;              /* Pointer to the next node in the list */
};

struct Name read_name();                /* Read a name from the keyboard      */
void show(struct PhoneRecord *pRecord); /* Output a phone record              */
bool has_name(struct PhoneRecord record, struct Name name); /* Test for a name */
struct Node* create_node();             /* Create a new list node             */
struct PhoneRecord* create_record();    /* Create a new phone record          */
void insert_node(struct Node *pNode);   /* Insert a node in the list          */
int compare_records(struct PhoneRecord *pFirst, struct PhoneRecord *pSecond);  /* Compare records */
int compare_names(struct Name first, struct Name second); /* Compare two names                     */
void list_numbers(struct Name name);    /* List all numbers for a Name structure */

struct Node *pStart = NULL;

int main(void)
{
  char answer = 'n';
  struct Node *pNode = NULL;                /* Pointer to a list node              */
  struct PhoneRecord *pRecord = NULL;       /* Pointer to a PhoneRecord structure  */
  bool found = false;                       /* Records when a name has been found  */

  /* Read an arbitrary number of phone records from the keyboard */
  do
  {
    insert_node(create_node());      /* Create and insert new node */

    printf("Do you want to enter another(y or n)?: ");
    scanf(" %c", &answer);
  }while(tolower(answer) == 'y');

  /* Search the list of phone records for a number */
  do
  {
    printf("\nEnter a name for which you want the number.");
    list_numbers(read_name());
    printf("Do you want to search for another (y or n)? ");
    scanf(" %c" , &answer);
  }while(tolower(answer) == 'y');

  /* List all the records in the linked list */
  pNode = pStart;
  do
  {
    show(pNode->pRecord);
  }while((pNode = pNode->pNext) != 0);
  printf("\n");

  /* Don't forget to free the memory! */
  pNode = pStart;
  do
  {
    free(pNode->pRecord);    /* Free memory for the record from the current node */
    pStart = pNode;          /* Save current node address                        */
    pNode = pNode->pNext;    /* Get next node address                            */
    free(pStart);            /* Free memory for the current node                 */
  }while((pNode = pNode->pNext) != 0);

  return 0;
}

/* Read a name from the keyboard and store in a structure */
struct Name read_name()
{
  unsigned long inches = 0;
  struct Name name;
    printf("\nEnter a first name: ");
    scanf(" %s", &name.firstname);
    printf("Enter a second name: ");
    scanf(" %s", &name.secondname);
  return name;
}

/* Output a record */
void show(struct PhoneRecord *pRecord)
{
  printf("\n%s %s   %s", pRecord->name.firstname, pRecord->name.secondname, pRecord->number);
}

bool has_name(struct PhoneRecord record, struct Name name)
{
  return (strcmp(name.firstname, record.name.firstname)==0 && strcmp(name.secondname, record.name.secondname)==0);
}

/* Create a new list node */
struct Node* create_node()
{
  struct Node *pNode = NULL;                         /* Pointer to the new node                 */
  pNode = (struct Node*)malloc(sizeof(struct Node)); /* Allocate memory for node                */
  pNode->pNext = NULL;                               /* No next node yet                        */
  pNode->pRecord = create_record();                  /* Create record and store address in node */
  return pNode;
}

/* Create a new phone record    */
struct PhoneRecord* create_record()
{
  struct PhoneRecord *pRecord = NULL;             /* Pointer to the new record */
  pRecord = (struct PhoneRecord*)malloc(sizeof(struct PhoneRecord)); /* Allocate memory */
  pRecord->name = read_name();                    /* Read the name             */

  /* Get the number for the name */
  printf("Enter the number for this name: ");
  scanf(" %[ 0123456789]",pRecord->number);       /* Read the number - including spaces */
  return pRecord;                                 /* Return the address of the record   */
}

/*
  Compare two PhoneRecord structures
  Returns -1 if the name for the first is < name for the second
  Returns  0 if the name for the first is equal to the name for the second
  Returns +1 if the name for the first is > name for the second
*/
int compare_records(struct PhoneRecord *pFirst, struct PhoneRecord *pSecond)
{
  return compare_names(pFirst->name, pSecond->name);
}

/* Compare two names
  Returns -1 if the  first is < the second
  Returns  0 if the first is equal to tthe second
  Returns +1 if the first is >  the second

  The comparison is by second name. If second names are equal,
  first names are compared.
*/
int compare_names(struct Name first, struct Name second)
{
  int result = 0;
  result = strcmp(first.secondname,second.secondname);
  return (result != 0 ? result : strcmp(first.firstname,second.firstname));
}

/* Insert a node into the list */
void insert_node(struct Node *pNode)
{
  struct Node *pCurrent = NULL;
  struct Node *pPrevious = NULL;
  struct Node *pTemp = NULL;

  /* Check for empty list */
  if(!pStart)
  {
    pStart = pNode;   /* Store address of the node as the start node */
    return;
  }

  /* Find position to insert the new node */
  pCurrent = pStart;
  while(pCurrent)
  {
    if(compare_records(pNode->pRecord, pCurrent->pRecord) <= 0)
    {                          /* New node goes before current list node */
      pNode->pNext = pCurrent; /* Set new node next pointer to current   */
      if(!pPrevious)           /* If pCurrent is the first node          */
      {
        pNode->pNext = pStart; /* New node next pointer points to current */
        pStart = pNode;        /* New node is the first node              */
      }
      else
      {                           /* Otherwise... */
        pPrevious->pNext = pNode; /* Previous node next pointer points to new node */
        pNode->pNext = pCurrent;  /* New node next pointer points to current       */
      }
      return;
    }
    pPrevious = pCurrent;         /* Previous node will be the current node */
    pCurrent = pCurrent->pNext;   /* Current node is now the next node      */
  }
  /* If we reach here, add pNode to the end */
  pPrevious->pNext = pNode;
}

/* List the numbers for a name */
void list_numbers(struct Name name)
{
  struct Node *pNode = NULL;
  bool found = false;
  int result = 0;

  /* Go through the list comparing names */
  pNode = pStart;
  while(pNode)
  {
    result = compare_names(name, pNode->pRecord->name);
    if(result == 0)
    {
      if(!found)                                    /* If this is the first time      */
      {
        found = true;                               /* Reset found flag               */
        printf("The numbers for this name are:\n"); /* and output the heading         */
      }
      printf("%s\n", pNode->pRecord->number);       /* Output the number for the name */
    }
   else if(result < 0)                              /* If name comes before current   */
      break;                                        /* we are done                    */
    pNode = pNode->pNext;                           /* Otherwise move to next node    */
  }

  if(!found)                                         /* If the name was not found */
    printf("No numbers found for this name.\n");     /* Say so                    */
}
