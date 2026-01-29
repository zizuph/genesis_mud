/*
 * RUNEGAME.c
 * This is a game of rune-stones which resembles in many ways the classic
 * Windows game of Mine Sweeper. 
 *
 * Objective: To turn over all of the stones possible without turning over any
 *            of the stones marked with the fire rune. If you turn over a fire
 *            rune, you lose the game and will take damage. You can 'mark' a stone
 *            as one you think contains a fire rune, and you can 'turn' over a stone,
 *            hoping that it will not reveal a fire rune. In addition, if you change
 *            your mind you can 'unmark' a stone.
 *
 * This Code assumes that it is located in the obj sub-directory of the coramar
 * directory root. (Currently /d/Emerald/coramar/obj/)
 *
 * - Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include <stdproperties.h>
#include "../coramar.h"
#include "../dirheader.h"

#ifndef NO
#define NO 0
#endif
#ifndef YES
#define YES 1
#endif

/* The dimensions of the playing board */
#define NCX    10
#define NCY    10

/* The three status types that a square can have */

#define STATUS_MARKED   1
#define STATUS_REVEALED 2
#define STATUS_CLOSED   3

#define ValueAt(x,y)  value_array[ (x+(y-1)*NCY)-1 ]
#define StatusAt(x,y) status_array[ (x+(y-1)*NCY)-1 ]

#define SqOpen(x,y) ( status_array [ (x+(y-1)*NCY)-1 ] == STATUS_REVEALED )
#define SqMark(x,y) ( status_array [ (x+(y-1)*NCY)-1 ] == STATUS_MARKED )

/* The pre-defined constant to define a value of RUNE */
#define RUNE            99

inherit "/std/object";

int *value_array;
int *status_array;

/*
 * Global Status Variables
 */
int SquaresClosed;
int game_in_progress = 0;

/* Function Prototypes */

void PlantFireRunes(int numrunes);
void OpenSquare(int x, int y);
void End_Game();
void Win_Game();

/* Add_Action Function Prototypes */
int turn_stone(string str);
int mark_stone(string str);
int unmark_stone(string str);
int new_game(string str);

void
create_object()
{ 
    value_array = allocate(NCX*NCY);
    status_array = allocate(NCX*NCY);    

    set_name("game");
}

init()
{
    ::init();
    add_action(turn_stone, "turn");
    add_action(mark_stone, "mark");
    add_action(unmark_stone, "unmark");
    add_action(new_game, "new");
}

/*
 * Function   : turn_stone
 * Description: This function handles the user input of 'turn x,y' to flip over a stone
 * Arguments  : str - the string typed on the command line following 'turn'
 * Returns    : 1 if handled the command, 0 if command failure.
 */
int
turn_stone(string str)
{
}

/*
 * Function   : mark_stone
 * Description: This function handles the user input of 'mark x,y' to mark a stone as
 *              a potential candidate for being a fire rune.
 * Arguments  : str - String typed on the command line
 * Returns    : 1 if handled the command, 0 if command failure.
 */
int
mark_stone(string str)
{
}

/*
 * Function   : unmark_stone
 * Description: This function will unmark a previously marked fire rune position by the
 *              player. Player gets nice message if the stone is already unmarked or
 *              already revealed.
 * Args,Returns: See above.
 */
int
unmark_stone(string str)
{
}

/*
 * Function   : new_game
 * Description: Begins a new game
 * Arguments  : str - Command-line input from player
 * Returns    : 1 if succesfull handling of command input, 0 if failure.
 */
int
new_game(string str)
{
}


/*
 * Function   :   PlantFireRunes
 * Description:   Lays down all of the mines on the field, and then performs a routine
 *                which configures the value of the surrounding squares.
 * Arguments  :   numrunes - The number of fire runes to place on the board.
 */

void
PlantFireRunes(int numrunes)
{
    int i, x, y, a, b;

    SquaresClosed = NCX*NCY - numrunes;

    for (i=NCX*NCY; i>0; i--)
    {
       value_array[i] = NO; 
       status_array[i] = STATUS_CLOSED;
    }

    /* The following routine randomly places the runes */

    for (i=numrunes; i>0; i--) {
	x=random(NCX); y=random(NCY);
	if (ValueAt(x,y) != RUNE)
	  ValueAt(x,y)=RUNE;
    }

    /* The following routine updates the values of the blocks surrounding
     * each rune
     */

    for (x=NCX-1; x>=0; x--) {
       for (y=NCY-1; y>=0; y--) {
          if (ValueAt(x,y) == RUNE)
	     continue;
          a=x-1;
          b=y-1;
          if (a>=0 && b>=0 && a<NCX && b<NCY)
		ValueAt(x,y) += (ValueAt(a,b) == RUNE);
	  a++;
	  if (a>=0 && b>=0 && a<NCX && b<NCY)
		ValueAt(x,y) += (ValueAt(a,b) == RUNE);
          a++;
	  if (a>=0 && b>=0 && a<NCX && b<NCY)
		ValueAt(x,y) += (ValueAt(a,b) == RUNE);
	  b++;
	  if (a>=0 && b>=0 && a<NCX && b<NCY)
		ValueAt(x,y) += (ValueAt(a,b) == RUNE);
	  a-=2;
	  if (a>=0 && b>=0 && a<NCX && b<NCY)
		ValueAt(x,y) += (ValueAt(a,b) == RUNE);
	  b++;
	  if (a>=0 && b>=0 && a<NCX && b<NCY)
		ValueAt(x,y) += (ValueAt(a,b) == RUNE);
	  a++;
	  if (a>=0 && b>=0 && a<NCX && b<NCY)
		ValueAt(x,y) += (ValueAt(a,b) == RUNE);
          a++;
	  if (a>=0 && b>=0 && a<NCX && b<NCY)
		ValueAt(x,y) += (ValueAt(a,b) == RUNE);
	}
    }
} /* FUNCTION PlantFireRunes */


/*
 * Function   :    OpenSquare
 * Arguments  :    x - X Co-ordinate on board of 'square' to open
 *                 y - Y co-Ordinate on board of 'square' to open
 * Description:    Reveals the underlying contents of a stone on the board. If the
 *                 underlying contents are blank, the player sees a ' ', otherwise
 *                 they will see a number of lines, indicating the number of nearby
 *                 fire runes. If they turn over a fire rune, end of game.
 */
void
OpenSquare(int x, int y)
{
    int a, b, c;

    /* Reveal the square */

    StatusAt(x,y) == STATUS_REVEALED;

    /* If the value of this item is 0, then we need to recursively open up
     * surrounding squares... Watch it! If this board is created too large,
     * you'll get recursion errors.
     */

    if (ValueAt(x,y) == RUNE) {
	End_Game();
	return;
    }

    if (ValueAt(x,y) != 0) {
	// do something if the value is higher than 0.
	// This stops the recursion!
	return;
    } else {
      a=x-1;
      b=y-1;
      if (a>=0 && b>=0 && a<NCX && b<NCY && !SqOpen(a,b) && SqMark(a,b)!=1) {
	SquaresClosed--;
	OpenSquare(a,b);
      }
      a++;
      if (a>=0 && b>=0 && a<NCX && b<NCY && !SqOpen(a,b) && SqMark(a,b)!=1) {
	SquaresClosed--;
	OpenSquare(a,b);
      }
      a++;
      if (a>=0 && b>=0 && a<NCX && b<NCY && !SqOpen(a,b) && SqMark(a,b)!=1) {
	SquaresClosed--;
       	OpenSquare(a,b);
      }
      b++;
      if (a>=0 && b>=0 && a<NCX && b<NCY && !SqOpen(a,b) && SqMark(a,b)!=1) {
	SquaresClosed--;
	OpenSquare(a,b);
      }
      a-=2;
      if (a>=0 && b>=0 && a<NCX && b<NCY && !SqOpen(a,b) && SqMark(a,b)!=1) {
	SquaresClosed--;
	OpenSquare(a,b);
      }
      b++;
      if (a>=0 && b>=0 && a<NCX && b<NCY && !SqOpen(a,b) && SqMark(a,b)!=1) {
	SquaresClosed--;
	OpenSquare(a,b);
      }
      a++;
      if (a>=0 && b>=0 && a<NCX && b<NCY && !SqOpen(a,b) && SqMark(a,b)!=1) {
	SquaresClosed--;
	OpenSquare(a,b);
      }
      a++;
      if (a>=0 && b>=0 && a<NCX && b<NCY && !SqOpen(a,b) && SqMark(a,b)!=1) {
	SquaresClosed--;
	OpenSquare(a,b);
      }
   } /* Else */

   if (!SquaresClosed) {
	Win_Game();
	return;
   }
} /* OpenSquare */
       

/*
 * Function   : End_Game
 * Description: Terminates the game because the player lost by turning over
 *              a fire Rune.
 * Arguments  : None.
 */

void
End_Game()
{
    /*
     * 1. Remove property from player indicating they're playing
     * 2. Set game variables back to defaults in this object
     * 3. Reset this object's pointer to the player
     * 4. Inform player of loss.
     */
}

    
/*
 * Function    : Win_Game
 * Description : Terminates the game because the player uncovered the last 
 *               square in the game which was not a mine.
 * Arguments   : None.
 */

void
Win_Game()
{
    /*
     * 1. Add player to rankings list.
     * 2. Reward quest experience to player if they do not already have this quest.
     * 3. Reveal hidden door in environment()
     */

}



    