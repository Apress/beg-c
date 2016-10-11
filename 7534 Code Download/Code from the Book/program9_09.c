/* Program 9.9 REVERSI An Othello type game */
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

const int SIZE =  6;                   /* Board size - must be even */
const char comp_c = '@';               /* Computer's counter        */
const char player_c = 'O';             /* Player's counter          */

/* Function prototypes */
void display(char board[][SIZE]);
int valid_moves(char board[][SIZE], bool moves[][SIZE], char player);
void make_move(char board[][SIZE], int row, int col, char player);
void computer_move(char board[][SIZE], bool moves[][SIZE], char player);
int best_move(char board[][SIZE], bool moves[][SIZE], char player);
int get_score(char board[][SIZE], char player);

int main(void)
{
  char board [SIZE][SIZE] = { 0 };    /* The board          */
  bool moves[SIZE][SIZE] = { false };    /* Valid moves        */
  int row = 0;                        /* Board row index    */
  int col = 0;                        /* Board column index */
  int no_of_games = 0;                   /* Number of games     */
  int no_of_moves = 0;                   /* Count of moves      */
  int invalid_moves = 0;                 /* Invalid move count  */
  int comp_score = 0;                    /* Computer score      */
  int user_score = 0;                    /* Player score        */
  char y = 0;                            /* Column letter       */
  int x = 0;                             /* Row number          */
  char again = 0;                        /* Replay choice input */

  /* Player indicator: true for player and false for computer */
  bool next_player = true;

  printf("\nREVERSI\n\n");
  printf("You can go first on the first game, then we will take turns.\n");
  printf("   You will be white - (%c)\n   I will be black   - (%c).\n",
                                                         player_c, comp_c);
  printf("Select a square for your move by typing a digit for the row\n "
                  "and a letter for the column with no spaces between.\n");
  printf("\nGood luck!  Press Enter to start.\n");
  scanf("%c", &again);

  /* The main game loop */
  do
  {
    /* On even games the player starts; */
    /* on odd games the computer starts */
    next_player = !next_player;
    no_of_moves = 4;                  /* Starts with four counters */

    /* Blank all the board squares */
    for(row = 0; row < SIZE; row++)
      for(col = 0; col < SIZE; col++)
        board[row][col] = ' ';

    /* Place the initial four counters in the center */
    int mid = SIZE/2;
    board[mid - 1][mid - 1] = board[mid][mid] = player_c;
    board[mid - 1][mid] = board[mid][mid - 1] = comp_c;
    /* The game play loop */
    do
    {
      display(board);                     /* Display the board  */
      if(next_player=!next_player)
      { /*   It is the player's turn                    */
        if(valid_moves(board, moves, player_c))
        {
          /* Read player moves until a valid move is entered */
          for(;;)
          {
            printf("Please enter your move (row column): ");
            scanf(" %d%c", &x, &y);    /* Read input        */
            y = tolower(y) - 'a';      /* Convert to column index */
            x--;                       /* Convert to row index    */
            if( x>=0 && y>=0 && x<SIZE && y<SIZE && moves[x][y])
            {
              make_move(board, x, y, player_c);
              no_of_moves++;          /* Increment move count */
              break;
            }
            else
              printf("Not a valid move, try again.\n");
          }
        }
        else                          /* No valid moves */
          if(++invalid_moves < 2)
          {
            printf("\nYou have to pass, press return");
            scanf("%c", &again);
          }
          else
            printf("\nNeither of us can go, so the game is over.\n");
      }
      else
      { /* It is the computer's turn                    */
        if(valid_moves(board, moves, '@')) /* Check for valid moves */
        {
          invalid_moves = 0;               /* Reset invalid count   */
          computer_move(board, moves, '@');
          no_of_moves++;                   /* Increment move count  */
        }
        else
        {
          if(++invalid_moves < 2)
            printf("\nI have to pass, your go\n"); /* No valid move */
          else
            printf("\nNeither of us can go, so the game is over.\n");
        }

      }
    }while(no_of_moves < SIZE*SIZE && invalid_moves<2);

    /* Game is over */
    display(board);                   /* Show final board  */

    /* Get final scores and display them */
    comp_score = user_score = 0;
    for(row = 0; row < SIZE; row++)
      for(col = 0; col < SIZE; col++)
      {
        comp_score += board[row][col] == comp_c;
        user_score += board[row][col] == player_c;
      }
    printf("The final score is:\n");
    printf("Computer %d\n    User %d\n\n", comp_score, user_score);

    printf("Do you want to play again (y/n): ");
    scanf(" %c", &again);             /* Get y or n             */
  }while(tolower(again) == 'y');      /* Go again on y       */

  printf("\nGoodbye\n");

  return 0;
}

/***********************************************
 * Function to display the board in its        *
 * current state with row numbers and column   *
 * letters to identify squares.                *
 * Parameter is the board array.               *
 ***********************************************/
void display(char board[][SIZE])
{
  /* Display the column labels */
  char col_label = 'a';               /* Column label   */
  printf("\n ");                      /* Start top line */
  for(int col = 0 ; col<SIZE ;col++)
    printf("   %c", col_label+col);   /* Display the top line */
  printf("\n");                       /* End the top line     */

  /* Display the rows… */
  for(int row = 0; row < SIZE; row++)
  {
     /* Display the top line for the current row */
    printf("  +");
    for(int col = 0; col<SIZE; col++)
      printf("---+");
    printf("\n%2d|",row + 1);

    /* Display the counters in current row */
    for(int col = 0; col<SIZE; col++)
      printf(" %c |", board[row][col]);  /* Display counters in row */
    printf("\n");
  }

  /* Finally display the bottom line of the board */
  printf("  +");                      /* Start the bottom line   */
  for(int col = 0 ; col<SIZE ;col++)
    printf("---+");                   /* Display the bottom line */
  printf("\n");                       /* End the bottom  line    */
}

/***********************************************
 * Calculates which squares are valid moves    *
 * for player. Valid moves are recorded in the *
 * moves array - true indicates a valid move,  *
 * false indicates an invalid move.            *
 * First parameter is the board array          *
 * Second parameter is the moves array         *
 * Third parameter identifies the player       *
 * to make the move.                           *
 * Returns valid move count.                   *
 **********************************************/
int valid_moves(char board[][SIZE], bool moves[][SIZE], char player)
{
  int rowdelta = 0;                   /* Row increment around a square    */
  int coldelta = 0;                   /* Column increment around a square */
  int x = 0;                          /* Row index when searching         */
  int y = 0;                          /* Column index when searching      */
  int no_of_moves = 0;                /* Number of valid moves            */

  /* Set the opponent            */
  char opponent = (player == player_c)? comp_c : player_c;

  /* Initialize moves array to false */
  for(int row = 0; row < SIZE; row++)
    for(int col = 0; col < SIZE; col++)
      moves[row][col] = false;

  /* Find squares for valid moves.                           */
  /* A valid move must be on a blank square and must enclose */
  /* at least one opponent square between two player squares */
  for(int row = 0; row < SIZE; row++)
    for(int col = 0; col < SIZE; col++)
    {
      if(board[row][col] != ' ')      /* Is it a blank square?  */
        continue;                     /* No - so on to the next */

      /* Check all the squares around the blank square  */
      /* for the opponents counter                      */
      for(rowdelta = -1; rowdelta <= 1; rowdelta++)
        for(coldelta = -1; coldelta <= 1; coldelta++)
        {
          /* Don't check outside the array, or the current square */
          if(row + rowdelta < 0 || row + rowdelta >= SIZE ||
             col + coldelta < 0 || col + coldelta >= SIZE ||
                                      (rowdelta==0 && coldelta==0))
            continue;

          /* Now check the square */
          if(board[row + rowdelta][col + coldelta] == opponent)
          {
            /* If we find the opponent, move in the delta direction  */
            /* over opponent counters searching for a player counter */
            x = row + rowdelta;       /* Move to          */
            y = col + coldelta;       /* opponent square  */

            /* Look for a player square in the delta direction */
            for(;;)
            {
              x += rowdelta;          /* Go to next square */
              y += coldelta;          /* in delta direction*/

              /* If we move outside the array, give up */
              if(x < 0 || x >= SIZE || y < 0 || y >= SIZE)
                break;

              /* If we find a blank square, give up */
              if(board[x][y] == ' ')
                break;

              /*  If the square has a player counter */
              /*  then we have a valid move          */
              if(board[x][y] == player)
              {
                moves[row][col] = true;  /* Mark as valid */
                no_of_moves++;           /* Increase valid moves count */
                break;                   /* Go check another square    */
              }
            }
          }
        }
    }
  return no_of_moves;
}

/********************************************************************
 * Makes a move. This places the counter on a square and reverses   *
 * all the opponent's counters affected by the move.                *
 * First parameter is the board array.                              *
 * Second and third parameters are the row and column indices.      *
 * Fourth parameter identifies the player.                          *
 ********************************************************************/
void make_move(char board[][SIZE], int row, int col, char player)
{
  int rowdelta = 0;                   /* Row increment              */
  int coldelta = 0;                   /* Column increment           */
  int x = 0;                          /* Row index for searching    */
  int y = 0;                          /* Column index for searching */

  /* Identify opponent */
  char opponent = (player == player_c) ? comp_c : player_c;

  board[row][col] = player;           /* Place the player counter   */

  /* Check all the squares around this square */
  /* for the opponents counter                */
  for(rowdelta = -1; rowdelta <= 1; rowdelta++)
    for(coldelta = -1; coldelta <= 1; coldelta++)
    {
      /* Don't check off the board, or the current square */
      if(row + rowdelta < 0 || row + rowdelta >= SIZE ||
         col + coldelta < 0 || col + coldelta >= SIZE ||
                              (rowdelta==0 && coldelta== 0))
        continue;

      /* Now check the square */
      if(board[row + rowdelta][col + coldelta] == opponent)
      {
        /* If we find the opponent, search in the same direction */
        /* for a player counter                                  */
        x = row + rowdelta;           /* Move to opponent */
        y = col + coldelta;           /* square           */

        for(;;)
        {
          x += rowdelta;              /* Move to the      */
          y += coldelta;              /* next square      */

          /* If we are off the board give up */
          if(x < 0 || x >= SIZE || y < 0 || y >= SIZE)
            break;

          /* If the square is blank give up */
          if(board[x][y] == ' ')
            break;

          /* If we find the player counter, go backward from here  */
          /* changing all the opponents counters to player         */
           if(board[x][y] == player)
          {
            while(board[x-=rowdelta][y-=coldelta]==opponent) /* Opponent? */
              board[x][y] = player;   /* Yes, change it */
            break;                    /* We are done    */
          }
        }
      }
    }
}

/*******************************************************************
 * Calculates the score for the current board position for the     *
 * player. player counters score +1, opponent counters score -1    *
 * First parameter is the board array                              *
 * Second parameter identifies the player                          *
 * Return value is the score.                                      *
 *******************************************************************/
int get_score(char board[][SIZE], char player)
{
  int score = 0;                      /* Score for current position */

  /* Identify opponent */
  char opponent = (player == player_c) ? comp_c : player_c;

  /* Check all board squares */
  for(int row = 0; row < SIZE; row++)
    for(int col = 0; col < SIZE; col++)
    {
      score -= board[row][col] == opponent; /* Decrement for opponent */
      score += board[row][col] == player;   /* Increment for player   */
    }
  return score;
}

/*******************************************************************
 * Calculates the score for the best move out of the valid moves   *
 * for player in the current position.                             *
 * First parameter is the board array                              *
 * Second parameter is the moves array defining valid moves.       *
 * Third parameter identifies the player                           *
 * The score for the best move is returned                         *
 *******************************************************************/
int best_move(char board[][SIZE], bool moves[][SIZE], char player)
{
  /* Identify opponent */
  char opponent = (player == player_c) ? comp_c : player_c;

  char new_board[SIZE][SIZE] = { 0 }; /* Local copy of board    */
  int score = 0;                      /* Best score             */
  int new_score = 0;                  /* Score for current move */

  /* Check all valid moves to find the best */
  for(int row = 0 ; row<SIZE ; row++)
    for(int col = 0 ; col<SIZE ; col++)
    {
      if(!moves[row][col])            /* Not a valid move?      */
        continue;                     /* Go to the next         */

      /* Copy the board */
      memcpy(new_board, board, sizeof(new_board));

      /* Make move on the board copy */
      make_move(new_board, row, col, player);

      /* Get score for move */
      new_score = get_score(new_board, player);

      if(score<new_score)             /* Is it better?               */
        score = new_score;            /* Yes, save it as best score  */
    }
  return score;                       /* Return best score           */
}


/*******************************************************************
 * Finds the best move for the computer. This is the move for      *
 * which the opponent's best possible move score is a minimum.     *
 * First parameter is the board array.                             *
 * Second parameter is the moves array containing valid moves.     *
 * Third parameter identifies the computer.                        *
 *******************************************************************/
void computer_move(char board[][SIZE], bool moves[][SIZE], char player)
{
  int best_row = 0;                   /* Best row index          */
  int best_col = 0;                   /* Best column index       */
  int new_score = 0;                  /* Score for current move  */
  int score = 100;                    /* Minimum opponent score  */
  char temp_board[SIZE][SIZE];        /* Local copy of board     */
  int temp_moves[SIZE][SIZE];         /* Local valid moves array */

  /* Identify opponent */
  char opponent = (player == player_c) ? comp_c : player_c;

  /* Go through all valid moves */
  for(int row = 0; row < SIZE; row++)
    for(int col = 0; col < SIZE; col++)
    {
      if(!moves[row][col])
        continue;

      /* First make copies of the board array */
      memcpy(temp_board, board, sizeof(temp_board));

      /* Now make this move on the temporary board */
      make_move(temp_board, row, col, player);

      /* find valid moves for the opponent after this move */
      valid_moves(temp_board, temp_moves, opponent);

      /* Now find the score for the opponent's best move */
      new_score = best_move(temp_board, temp_moves, opponent);

      if(new_score<score)             /* Is it worse?                     */
      {                               /* Yes, so save this move           */
        score = new_score;            /* Record new lowest opponent score */
        best_row = row;               /* Record best move row             */
        best_col = col;               /* and column                       */
      }
    }
  /* Make the best move */
  make_move(board, best_row, best_col, player);
}

