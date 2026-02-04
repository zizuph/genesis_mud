/*
 * 920822 by dust. common nim-game with strategy
 */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

#define MIN_HEAPS 3
#define MAX_HEAPS 7
#define MIN_STONES 5
#define MAX_STONES 15

int     nbr_heaps;      /* number of heaps with stones */
int     *heaps;         /* actual sizes of the heaps */
int     total;          /* total number of stones */
object  npc;            /* opponent of human player */
int     aid = 0;

public void
set_opponent(object opp)
{
    npc = opp;
}

public object
query_opponent()
{
    return npc;
}

/*
 * int *best_move(): Using nbr_heaps and heaps, calculates a
 * winning move if possible, or another one. Returns it as
 * an array ({ heap-number, number-of-stones }).
 */
int *
best_move()
{
    int result, temp, i, j;
    int max_heap, max_nbr, max_result;

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
 * init_game(): make a new game: 3-7 heaps, each 5-15 stones
 */
void
init_game()
{
    int i;

    aid = 0;
    total = 0;
    nbr_heaps = MIN_HEAPS + random(MAX_HEAPS-MIN_HEAPS+1);
    heaps = allocate(nbr_heaps);
    for (i=0; i<nbr_heaps; i++)
        total += (heaps[i] = MIN_STONES + random(MAX_STONES-MIN_STONES+1));
}

public void
create_object()
{
    set_name("nim");
    add_name("game");
    add_name("nim-game");
    set_short("NIM-game");
    init_game();
    set_long("@@long_desc");
    add_prop(OBJ_I_NO_GET, 1);
}

public string
long_desc()
{
    string result;
    int i;

    result = "This is a NIM-game. At the moment it consists of " +
        nbr_heaps + " heaps. The numbers of stones they contain are";
    for (i=0; i<nbr_heaps; i++)
        result = result + " " + heaps[i];
    result = result + ".\n";
    return result;
}

public void
describe()
{
    string result;
    int i, j;

    result = "You count the stones and find these heaps : ";
    for (i=0, j=1; i<nbr_heaps; i++, j++)
        result = result + heaps[i] + " ";
    tell_room(environment(this_object()), result + ".\n");
}

public int
start_nim(string str)
{
    if (!npc || aid) return 0;
    
    tell_room(environment(this_object()), QCTNAME(npc) +
              " collects the stones and builds new heaps.\n");
    init_game();
    describe();
    return 1;
}

public void
npc_move()
{
    string str;
    int *move;
    
    move = best_move();
    heaps[move[0]] -= move[1];
    total -= move[1];
    move[0]++;
    
    aid = 0;
    
    if (move[1] == 1)
        str = "stone";
    else
        str = "stones";
    
    if (npc)
    {
        tell_room(environment(this_object()), QCTNAME(npc) +
                  " removes " + move[1] + " " + str +
                  " from heap number " + move[0] + ".\n", npc);
    }
    else
    {
        tell_room(environment(this_object()), "Someone" +
                  " removes " + move[1] + " " + str +
                  " from heap number " + move[0] + ".\n", npc);
    }
    
    describe();
    
    if (total <= 0)
    {
        if (npc)
            tell_room(environment(this_object()), QCTNAME(npc) +
                      " removed the last stone and you lose!\n");
        else 
            tell_room(environment(this_object()), "Someone" +
                      " removed the last stone and you lose!\n");
                      
        if (random(3) == 0 && npc) npc->happy();
        set_alarm(3.0, -1.0, &start_nim(" "));
    }
}

public int
do_remove(string str)
{
    int index, nbr;
    string s;

    if (strlen(str) < 3) return 0;
    
    if (!parse_command(str, environment(),
        "%d [stone] [stones] [from] [heap] %d", nbr, index))
        return 0;
    
    if (aid)
    {
        if (npc)
            npc->command("say Hey! It's my turn!");
        else
            write("It's not your turn!\n");
        return 1;
    }
    
    if (index > nbr_heaps)
    {
        notify_fail("But there are not that many heaps.\n");
        return 0;
    }
    if (index < 1)
    {
        notify_fail("Heap numbers must be bigger than 0.\n");
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
    if (nbr == 1)
        s = "stone";
    else
        s = "stones";
    
    write("You remove " + nbr + " " + s + " from heap number " + index + ".\n");
    say(QCTNAME(this_player()) + " removes " + nbr + " " + s +
        " from heap number " + index + ".\n");
    
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
    
    if (npc)
    {
        if (random(2))
            npc->command("ponder");
        else
            npc->command("hmm");
    }
    
    aid = set_alarm(itof(2 + random(total/8)), -1.0, npc_move);
    
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_remove, "remove");
    add_action(do_remove, "rem");
    add_action(start_nim, "nim");
}

