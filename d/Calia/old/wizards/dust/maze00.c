/*
 * entry.c: the entrance room of the lock-maze where the statue is.
 * Dust, February 21, 93
 */


inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>



#include "maze0.h"



/*
 * Declaration of maze-structures
 * maze looks like (numbers: indices x,y of array):
 *
 *                   ___
 *                  |6,6|
 *                  |___|
 *               ___/5,5\___
 *           ___/4,5\___/5,4\___
 *       ___/3,5\___/4,4\___/5,3\___
 *   ___/2,5\___/3,4\___/4,3\___/5,2\___
 *  /1,5\___/2,4\___/3,3\___/4,2\___/5,1\
 *  \___/1,4\___/2,3\___/3,2\___/4,1\___/
 *      \___/1,3\___/2,2\___/3,1\___/
 *          \___/1,2\___/2,1\___/
 *              \___/1,1\___/
 *                  \___/
 *                  |0,0|
 *                  |___|
 */

/* solution[x,y] (x,y in set 0..6): 0 = no exit, 1,2,3 = exits 1,2 or 3:
 *
 *   1 2 3   room=[x,y];   successor 1 = [x,y+1]
 *    \|/                  successor 2 = [x+1,y+1]
 *   room                  successor 3 = [x+1,y]
 *                         condition: 1 <= x',y' <= 5
 *
 * actual, old_actual: same structure for old and new actual openings
 * after a letter has been dialled
 */

int	*solution;
int	*actual;
int	*old_actual;

/* solution-path is also indexed by sol_index_x and sol_index_y;
 * x = sol_index_x[4], y = sol_index_y[4] means:
 * fourth room in the maze is [x,y].
 * maximum length of path is 10, the last one is always [6,6]
 * unused ones are marked with [0,0].
 */

int	*sol_index_x = ({ 0,0,0,0,0,0,0,0,0,0 });
int	*sol_index_y = ({ 0,0,0,0,0,0,0,0,0,0 });

/* password is array of letters of actual password
 */

string	*password;

/* succ_x, succ_y: global return structures for successor
 *   (containing indices of one of teh three successors of a node)
 * succ_array_selection: return variables for
 *   cnt_and_store_succ procedure (see there)
 * seed: global variable to keep the seed for random values
 */

int	succ_x, succ_y;
int	*succ_array_selection = ({ 0,0,0 });
int	seed;

/*
 * Procedures and functions for maze administration
 */

/*
 * sucessor(x,y,index) stores 'index'th successor of node x,y in global
 * variables succ_x, succ_y; if it doesn't exist, the function returns
 * 0; on success it returns 1.
 */

int
successor(int x, int y, int index)
{
    /* calculate succ_x, succ_y depending on index (0=same, or 1-3) */
    if (index >= 1 && index <= 3)
    {
	succ_x = x; succ_y = y;
	if (index >= 2) succ_x = x+1;
	if (index <= 2) succ_y = y+1;
    }
    else if (index == 0) { succ_x = x; succ_y = y; }
    /* check for validity and return success or no-success */
    if (index <= 3 && ( succ_x <= 5 && succ_x >= 1 &&
                        succ_y <= 5 && succ_y >= 1  ||
			succ_x == 6 && succ_y == 6 ) && index >= 0)
	return 1;
    return 0;
}

/*
 * cnt_succ(x,y) returns number of successors for any node
 */

int
cnt_succ(int x, int y)
{
    int i,count;

    for (i=1, count=0; i<=3; i++)
	if (successor(x,y,i))  count++;
    return count;
}

/*
 * cnt_and_store_succ(x,y) returns number of possible successors of x,y
 * such that
 * for all successors [x,y] the condition solution[x,y] = 0 is
 * fulfilled (to avoid double solutions in solution-path). All
 * successors are stored in the global structures (arrays)
 * succ_array_selection
 */


int
cnt_and_store_succ(int x, int y)
{
    int i,count;

    for(i=1, count=0; i<=3; i++)
    {
	if (successor(x,y,i) && succ_x<6 && solution[7*succ_x+succ_y] == 0)
	{
	    succ_array_selection[count] = i;
	    count++;
	}
    }
    return count;
}

/*
 * set_seed: use players name to set root seed value. Seed is stored
 * in global variable 'seed'. If an explicit string is given, this is
 * used instead of the players name.
 */

void
set_seed(string str) {
    string *name;
    int i;

    if (strlen(str) > 0) name = explode(str,"");
    else name = explode(this_player()->query_name(),"");
    seed = 3;
    for (i=0; i<sizeof(name); i++)
	seed += i*97*(name[i][0]-32);
    for (i=0; i<17; i++) seed = random(32760,seed);
}

/*
 * my_rand(limit): get next random number of players serie
 */

int
my_rand(int limit)
{
    seed = random(32760,seed);
    return(random(limit,seed));
}

/*
 * calc_solution: calculate solution path; returns length of path.
 * the path is stored in teh global variable 'solution'.
 * the parameter "str" is the players name. If it's "", the name
 * defaults to this_player()'s name (see set_seed()).
 * Note: this function is always called by the dial function
 *        (whenever a player dials a letter).
 */

int
calc_solution(string str)
{
    int x,y,node_x,node_y,count,selection;

    /* remove old solution (clear solution array) */
    for (x=0; x<49; x++) solution[x] = 0;

    /* we start path at node = [0,0], clear count, re-set seed. We
     * search until we reach [6,6]. Each step is counted in 'count'. */
    for (node_x=node_y=count=0, set_seed(str); node_x != 6; count++)
    {
	sol_index_x[count] = node_x; /* Store actual node in path */
	sol_index_y[count] = node_y;
	do selection = my_rand(3)+1; /* get possible exit (1,2 or 3) */
	while (!successor(node_x,node_y,selection));  /* until valid */
	solution[7*node_x+node_y] = selection; /* store path in maze */
	node_x = succ_x; node_y = succ_y;      /* get next node */
    }
    return count;
}

/*
 * set_password(string): sets password to string
 */

void
set_password(string str)
{
    password = explode(str,"");
}

/*
 * calc_password: choose password of corresponsing length (can be
 * exported to other rooms togetehr with set_seed and my_rand).
 * As length the return variable of calc_solution should be used
 * so the password has the same length as the solution path.
 * The passwords are stored in the files len6, len7, len8, len9,
 * and len10, depending on the wished length. The number of words
 * in each file was counted (wc -l) and stored in the code below.
 */

void
calc_password(int count)
{
    string word;

    set_seed(""); /* Use this_player()'s name as seed */
    /* Get random password out of corresponding file */
    if (count == 6) word = read_file(WORDS + "6", my_rand(2880)+1,1);
    if (count == 7) word = read_file(WORDS + "7", my_rand(3090)+1,1);
    if (count == 8) word = read_file(WORDS + "8", my_rand(2860)+1,1);
    if (count == 9) word = read_file(WORDS + "9", my_rand(2590)+1,1);
    if (count ==10) word = read_file(WORDS +"10", my_rand(1700)+1,1);
    set_password(word);
}

/*
 * string query_password(string) retruns the user-dependent password.
 * It can be called from other places where the user is supplied with
 * his/her password. It gets the players name as parameter (whose
 * password is wished). Can also be used by wizards (Call here ....).
 */

string
query_password(string name)
{
    string word;
    int count;

    count = calc_solution(name);
    set_seed(name);
    if (count == 6) word = read_file(WORDS + "6", my_rand(2880)+1,1);
    if (count == 7) word = read_file(WORDS + "7", my_rand(3090)+1,1);
    if (count == 8) word = read_file(WORDS + "8", my_rand(2860)+1,1);
    if (count == 9) word = read_file(WORDS + "9", my_rand(2590)+1,1);
    if (count ==10) word = read_file(WORDS +"10", my_rand(1700)+1,1);
    word = explode(word,"\n")[0]; /* Remove trailing newline */
    return(word);
}


/*
 * set_transitions: after all calculations have been done, set the exits
 * in all rooms or in debug mode print out all information to screen.
 * It is called as last procedure in teh dial function. It expects the
 * global variables old_actual and actual to be set accordingly
 * (containing the old and new state).
 */


void
set_transitions()
{
    int x,y,x2,y2,index;

    /* clear the transition fields in all maze rooms */
    for (x=0; x<=6; x++) for (y=0; y<=6; y++)
	if ((x>0 && x<6 && y>0 && y<6) || (x==0 && y==0) || (x==6 && y==6))
	    (MAZE + x + y)->clear_transitions();

    /* Second step: inform all rooms about their old and newexits.
     * Note: We're using a translation of the exit numbers used above
     * (0=none, 1=northwest, 2=north, 3=northeast) so all six exits
     * can be covered and the sum of the codes of two opposite
     * exits sum up to 5 (so it's easy to set the exit in the other room
     * by the '5-index' operation). The following scheme for 'index'
     * is used:           To recall, this is actual/old_actual's encoding:
     *
     *    3 0 1              1 2 3
     *     \|/                \|/
     *     /|\
     *    4 5 2
     *
     * -1 means: no exit
     */
    for (x=0; x<6; x++) for (y=0; y<6; y++)
	if ((x>0 && y>0) || (x==0 && y==0))
	{
		/* Translate old_actual entry in maze to index */
		index = ({-1,3,0,1})[old_actual[7*x+y]];
		if (index>=0)	/* Only if an exist (to north) exists */
		{
		    /* Inform room about an old open exit */
		    (MAZE + x + y)->set_old_state(index);
		    /* Calculate other room of exit */
		    x2 = ({ 1, 1, 0, 0,-1,-1})[index] + x;
		    y2 = ({ 1, 0,-1, 1, 0,-1})[index] + y;
		    /* Inform other room about old open exit
		     * note: 5-index is used as exit-code (opposite)
		     */
		    (MAZE + x2 + y2)->set_old_state(5 - index);
		}
		/* the same repeats for open exits in new state */
		index = ({-1,3,0,1})[actual[7*x+y]];
		if (index>=0)
		{
		    (MAZE + x + y)->set_new_state(index);
		    x2 = ({ 1, 1, 0, 0,-1,-1})[index] + x;
		    y2 = ({ 1, 0,-1, 1, 0,-1})[index] + y;
		    (MAZE + x2 + y2)->set_new_state(5 - index);
		}
	}

    /* Third step: all rooms now know their transitions. They are
     * triggered now in each room (each rooms takes care itself for
     * the minimal number of transitions and messages sent to players
     * in the room).
     */
    for (x=0; x<=6; x++) for (y=0; y<=6; y++)
	if ((x>0 && x<6 && y>0 && y<6) || (x==0 && y==0) || (x==6 && y==6))
	    (MAZE + x + y)->do_transitions(x,y);
}

/*
 * dial(string): set global variable 'actual' depending on password and
 * the selected letter, calculate transitions for each room.
 */

int
dial(string str)
{
    int x,y,i,count,selection,len;
    string *strtab,letter;

    /* Extract letter */
    notify_fail("Which letter You like to dial (from a to z)?\n");
    if (strlen(str) < 1) return 0;
    strtab = explode(str,"");
    letter = strtab[sizeof(strtab)-1];
    if (member_array(letter,({"a","b","c","d","e","f","g","h",
	"i","j","k","l","m","n","o","p","q","r","s","t","u",
	"v","w","x","y","z"})) == -1) return 0;
    write("You turn the statue so it points to the letter '" + letter +
	"'.\n");
    say(QCTNAME(this_player()) + " turns the statue so it points " +
	"to the letter '" + letter + "'.\n");

    /* Copy actual state to old state (for transitions),
     * mark all exits in new state as closed
     */
    for (i=0; i<49; i++)
    {
	old_actual[i] = actual[i]; /* copy old exits */
	actual[i] = 0;	/* clear all actual exits */
    }
    calc_password(len=calc_solution("")); /* Determine user's solution */

    /* For each letter in the user's password identical to the
     * dialled one (eventually several) set the right exit on the
     * solution path stored in solution.
     */
    for (i=0; i<len; i++) if (password[i] == letter)
    {
	actual[7*sol_index_x[i]+sol_index_y[i]] =
	solution[7*sol_index_x[i]+sol_index_y[i]];
    }

    /* Change seed depending on the letter dialled (so teh remaining
     * exits are different for different wrong letters)
     */
    for (i=0; i < letter[0]; i++) seed = random(32760,seed);

    /* Set remaining exits; in all actual rooms that still have 0,
     * fill entry with 0,1,2, or 3, but so that no path leads to
     * any room on the solution path (but paths may lead from solution
     * rooms to others).
     */
    for (x=0; x<=5; x++) for (y=0; y<=5; y++)
	if ((x>0 && y>0 || (x==0 && y==0)) && actual[7*x+y] == 0)
	{
	    count = cnt_and_store_succ(x,y); /* count 'allowed' exits */
	    /* the possible directions (1,2, or 3) are stored in
             * succ_array_selection[i] (i up to 3),
	     * count+1 coz 0 (no exit) is also allowed
	     */
	    if((selection = my_rand(count+1)) > 0)
		actual[7*x+y] = succ_array_selection[count-1];
	}
    /* Now trigger the transitions in all rooms */
    set_transitions();
    return 1;
}


create_room()
{
    solution = allocate(49);
    actual = allocate(49);
    old_actual = allocate(49);
    set_short("A room with a statue");
    set_long(break_string("This is a very small room. You can " +
	"see a statue with its left hand pointing to a scale " +
	"containing the letters from a to z. It seems you can " +
	"turn the statue so it points to different letters...\n",70));
    add_prop(ROOM_I_LIGHT,0);
}

init()
{
    ::init();
    add_action("dial","dial");
    add_action("dial","select");
    add_action("dial","turn");
}

/*
 * The following procedures are only for debug reasons;
 * Call here sol: prints the actual solution path (can also be used
 *                after Call here query_password xxx)
 * Call here act: prints teh actual configuration of a maze (can
 *                only be called after a dial command)
 * the mazes are printed such that the starting room is to the upper
 * left and the target to the lower right, so translate the directions
 * as follows (the output is rotated for simplicity of code):
 * 
 *   s  sw  nw
 *    \  |  /
 *    /  |  \
 *   se  ne  n
 */

void sol()
{
    int x,y;
    write("solution-path:\n\n");
    for (x=0; x<=6; x++)
    {
	for (y=0; y<=6; y++)
	{
	    if ((x>0 && x<6 && y>0 && y<6) || (x==0 && y==0) || (x==6 && y==6))
		write("*");
	    else
		write(" ");
	    if (solution[7*x+y] == 1) write("-"); else write(" ");
	}
	write("\n");
	for (y=0; y<=6; y++)
	{
	    if (solution[7*x+y] == 3) write ("|"); else write(" ");
	    if (solution[7*x+y] == 2) write ("\\"); else write(" ");
	}
	write("\n");
    }
}

void act()
{
    int x,y;
    write("\n\nactual path:\n\n");
    for (x=0; x<=6; x++)
    {
	for (y=0; y<=6; y++)
	{
	    if ((x>0 && x<6 && y>0 && y<6) || (x==0 && y==0) || (x==6 && y==6))
		write("*");
	    else
		write(" ");
	    if (actual[7*x+y] == 1) write("-"); else write(" ");
	}
	write("\n");
	for (y=0; y<=6; y++)
	{
	    if (actual[7*x+y] == 3) write ("|"); else write(" ");
	    if (actual[7*x+y] == 2) write ("\\"); else write(" ");
	}
	write("\n");
    }
}

