/* Program 11.9 Generating a bar chart */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define PAGE_HEIGHT  20
#define PAGE_WIDTH   40

typedef struct barTAG
{
  double value;
  struct barTAG *pnextbar;
}bar;

typedef unsigned int uint;     /* Type definition*/

/* Function prototype */
int bar_chart(bar *pfirstbar, uint page_width, uint page_height, char *title);

int main(void)
{
  bar firstbar;            /* First bar structure */
  bar *plastbar = NULL;    /* Pointer to last bar */
  char value[80];          /* Input buffer        */
  char title[80];          /* Chart title         */

  printf("\nEnter the chart title: ");
  gets(title);             /* Read chart title    */

  for( ;; )                /* Loop for bar input  */
  {
    printf("Enter the value of the bar, or use quit to end: ");
    gets(value);

    if(strcmp(value, "quit") == 0)   /* quit entered?       */
     break;                          /* then input finished */

    /* Store in next bar */
    if(!plastbar)                /* First time?             */
    {
      firstbar.pnextbar = NULL;  /* Initialize next pointer */
      plastbar = &firstbar;      /* Use the first           */
    }
    else
    {
      /* Get memory */
      if(!(plastbar->pnextbar = malloc(sizeof(bar))))
      {
        printf("Oops! Couldn't allocate memory\n");
        return -1;
      }
      plastbar = plastbar->pnextbar;    /* Old next is new bar  */
      plastbar->pnextbar = NULL;        /* New bar next is NULL */
    }
    plastbar->value = atof(value);      /* Store the value      */
  }

  /* Create bar-chart */
  bar_chart(&firstbar, PAGE_WIDTH, PAGE_HEIGHT, title);

  /* We are done, so release all the memory we allocated */
  while(firstbar.pnextbar)
  {
    plastbar = firstbar.pnextbar;           /* Save pointer to next */
    firstbar.pnextbar = plastbar->pnextbar; /* Get one after next   */
    free(plastbar);                         /* Free next memory     */
  }
  return 0;
}

int bar_chart(bar *pfirstbar, uint page_width, uint page_height,
                                                       char *title)
{
  bar *plastbar = pfirstbar;  /* Pointer to previous bar         */
  double max = 0.0;           /* Maximum bar value               */
  double min = 0.0;           /* Minimum bar value               */
  double vert_scale = 0.0;    /* Unit step in vertical direction */
  double position = 0.0;      /* Current vertical position on chart */
  uint bar_count = 1;         /* Number of bars - at least 1     */
  uint barwidth = 0;          /* Width of a bar                  */
  uint space = 2;             /* spaces between bars             */
  uint i = 0;                 /* Loop counter                    */
  uint bars = 0;              /* Loop counter through bars       */
  char *column = NULL;        /* Pointer to bar column section   */
  char *blank = NULL;         /* Blank string for bar+space      */
  bool axis = false;          /* Indicates axis drawn            */
  /* Find maximum and minimum of all bar values */

  /* Set max and min to first bar value */
  max = min = plastbar->value;

  while((plastbar = plastbar->pnextbar) != NULL)
  {
    bar_count++;              /* Increment bar count */
    max = (max < plastbar->value)? plastbar->value : max;
    min = (min > plastbar->value)? plastbar->value : min;
  }
  vert_scale = (max - min)/page_height; /* Calculate step length */

  /* Check bar width */
  if((barwidth = page_width/bar_count - space) < 1)
  {
    printf("\nPage width too narrow.\n");
    return -1;
  }

  /* Set up a string that will be used to build the columns */

  /* Get the memory */
  if((column = malloc(barwidth + space + 1)) == NULL)
  {
    printf("\nFailed to allocate memory in barchart()"
                           " - terminating program.\n");
    exit(1);
  }
  for(i = 0 ; i<space ; i++)
    *(column+i)=' ';         /* Blank the space between bars */
  for( ; i<space+barwidth ; i++)
    *(column+i)='#';         /* Enter the bar characters     */
  *(column+i) = '\0';        /* Add string terminator        */

  /* Set up a string that will be used as a blank column */

  /* Get the memory */
  if((blank = malloc(barwidth + space + 1)) == NULL)
  {
    printf("\nFailed to allocate memory in barchart()"
                           " - terminating program.\n");
    exit(1);
  }

  for(i = 0 ; i<space+barwidth ; i++)
    *(blank+i) = ' ';        /* Blank total width of bar+space */
  *(blank+i) = '\0';         /* Add string terminator          */

    printf("^ %s\n", title);   /* Output the chart title      */

  /* Draw the bar chart */
  position = max;
  for(i = 0 ; i <= page_height ; i++)
  {
    /* Check if we need to output the horizontal axis */
    if(position <= 0.0 && !axis)
    {
      printf("+");           /* Start of horizontal axis    */
      for(bars = 0; bars < bar_count*(barwidth+space); bars++)
        printf("-");         /* Output horizontal axis      */
      printf(">\n");
      axis = true;           /* Axis was drawn              */
      position -= vert_scale;/* Decrement position           */
      continue;
    }
    printf("|");             /* Output vertical axis        */
    plastbar = pfirstbar;    /* start with the first bar    */

    /* For each bar... */
    for(bars = 1; bars <= bar_count; bars++)
    {
      /* If position is between axis and value, output column */
      /* otherwise output blank                               */
      printf("%s", position <= plastbar->value &&
                    plastbar->value >= 0.0 && position > 0.0 ||
                    position >= plastbar->value &&
                    plastbar->value <= 0.0 &&
                    position <= 0.0 ? column: blank);
      plastbar = plastbar->pnextbar;
    }
    printf("\n");            /* End the line of output        */
    position -= vert_scale;  /* Decrement position            */
  }
  if(!axis)            /* Have we output the horizontal axis? */
  {                    /* No, so do it now                    */
    printf("+");
    for(bars = 0; bars < bar_count*(barwidth+space); bars++)
      printf("-");
    printf(">\n");
  }

  /* Code for rest of the function...  */
  free(blank);               /* Free memory for blank string   */
  free(column);              /* Free memory for column string  */
  return 0;
}

