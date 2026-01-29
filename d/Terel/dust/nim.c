/*
 * 920822 by dust. common nim-game with strategy
 */
inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

int	nbr_heaps;	/* number of heaps with stones */
int	*heaps;		/* actual sizes of the heaps */
int     total;          /* total number of stones */
object	npc;		/* opponent of human player */

void
set_opponent(object opp) {
  npc = opp;
}

/*
 * int *best_move(): Using nbr_heaps and heaps, calculates a
 * winning move if possible, or another one. Returns it as
 * an array ({ heap-number, number-of-stones }).
 */
int *
best_move()
{
    int result,temp,i,j;
    int max_heap,max_nbr, max_result;

    /* nim-strategy: calc xor of all heaps */
    for (i=0; i<nbr_heaps; i++)
	result ^= heaps[i];

    /* try to make the result to zero in a heap */
    for (i=0; i<nbr_heaps; i++)
    {
	temp = heaps[i] - (result ^ heaps[i]);
	if (temp > 0)
	    return(({i, temp}));
    } /* if we reach this point, no winning move is possible */

    /* try to minimize problem: xor-sum as big as possible */
    max_heap=0; max_nbr=0; max_result=-1;
    for (i=0; i<nbr_heaps; i++)
	for (j=1; j<=heaps[i]; j++)
	{
	    temp = result ^ heaps[i] ^ j;
	    if (temp > max_result)
	    {
		max_result = temp; max_heap = i; max_nbr = j;
	    }
	}
    return(({max_heap, max_nbr}));
}

/*
 * init_game(): make a new game: 3-8 heaps, each 5-15 stones
 */
void
init_game()
{
    int i;

    total = 0;
    nbr_heaps = random(6) + 3;
    heaps = allocate(nbr_heaps);
    for (i=0; i<nbr_heaps; i++)
	total += (heaps[i] = random(11)+5);
}

create_object()
{
    set_name("nim");
    set_name("game");
    set_name("nim-game");
    set_short("NIM-game");
    init_game();
    set_long("@@long_desc");
    add_prop(OBJ_I_NO_GET,1);
}

string
long_desc()
{
    string result;
    int i;

    result = "This is a NIM-game. At the moment it consists of " +
	nbr_heaps + " heaps. The numbers of stones they contain are";
    for (i=0; i<nbr_heaps; i++)
	result = result + " " + heaps[i];
    result = result + ".\n";
    return(break_string(result,70));
}

void
init()
{
    ::init();
    add_action("do_remove","remove");
    add_action("do_remove","rem");
    add_action("start_nim","nim");
}


void
describe()
{
    string result;
    int i,j;

    result = "You count the stones and find those heaps : ";
    for (i=0, j=1; i<nbr_heaps; i++, j++)
	result = result + heaps[i] + " ";
    result = result + "\n";
    write(break_string(result,70));
    say(break_string(result,70));
}

int
start_nim(string str)
{
    write("The guard collects the stones and builds new heaps.\n");
    say("The guard collects the stones and builds new heaps.\n");
    init_game();
    describe();
    return 1;
}

int
do_remove(string str)
{
    int index, nbr;
    int *move;

    if (!parse_command(str,environment(),
	"%d [stone] [stones] [from] [heap] %d", nbr, index))
        return 0;
    if (index > nbr_heaps)
    {
        notify_fail("But there are not so many heaps.\n");
	return 0;
    }
    if (index < 1)
    {
        notify_fail("Heap numbers must be bigger that 0.\n");
	return 0;
    }
    if (heaps[index-1] < nbr)
    {
        notify_fail("But heap " + index + " contains only " +
		    heaps[index-1] + " stones.\n");
	return 0;
    }
    if (nbr < 1)
    {
        notify_fail("You must remove at least one stone.\n");
	return 0;
    }
    write("You remove " + nbr + " stones from heap number " + index + ".\n");
    say(QCTNAME(this_player()) + " removes " + nbr +
	" stones from heap number " + index + ".\n");
    index--;
    heaps[index] -= nbr;
    total -= nbr;
    describe();
    if (total <= 0)
    {
        write("Congratulations! You removed the last stone and " +
	      "win this game!\n");
	say(QCTNAME(this_player()) + " has just removed the last stones " +
	    "and wins!\n");
	if (npc) npc->frustrate();
	return 1;
    }
    move = best_move();
    heaps[move[0]] -= move[1];
    total -= move[1];
    move[0]++;
    if (npc)
    {
        write("The guard removes " + move[1] +
	      " stones from heap number " + move[0] + ".\n");
        say("The guard removes " + move[1] +
	    " stones from heap number " + move[0] + ".\n");
     } else
     {
         write("Your opponent removes " + move[1] +
	       " stones from heap number " + move[0] + ".\n");
         say("Your opponent removes " + move[1] +
	     " stones from heap number " + move[0] + ".\n");
     }
     describe();
     if (total <= 0)
     {
         write("The guard removes the last stone and you loose!\n");
	 say("The guard removes the last stone and " +
	     QCTNAME(this_player()) + " looses.\n");
	 start_nim(" ");
     }
     return 1;
}
