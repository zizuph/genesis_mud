#include "defs.h"

object slab;

CONSTRUCT_ROOM 
{
    set_short("You are in the golden room");
    set_long("You are in the golden room! Everything in here shines as if "+
	     "it was pure gold. Unfortunately, there are only huge slabs "+
	     "of rocks which you cannot possibly carry, unless you bring in "+
	     "a couple of trolls as helpers. In the middle of the floor is "+
	     "a hole down to a dark room. One other exit is ascending "+
	     "southwards through a hole up in the wall.\n");
    add_item("room","It shines as if it is of pure gold!");
    add_item("gold","You know... Gold!!");
    add_item(({"rock","rocks"}),"They are far too heavy to carry.");
    add_item("hole","It leads down into the darkness.");
    add_item("wall",
	     "They shine of gold!\nSouth there is a hole to a fine room.");
    EXIT("crosroad","south");
    EXIT("mining/mining.20","down");
    add_tell(({"push", "move"}), "[the] [slabs] [of] 'rocks' / 'rock'",
        "$You $try to move the golden rocks, but with no success.\n");
    add_call("feel", "[the] [slabs] [of] 'gold' / 'rock'", "feel_it");
    slab = clone_object(MORIA_OBJ + "gold_slab");
    slab->move(TO);
}

int
feel_it()
{
    write("While feeling the rocks, you somehow realize there is life within!\n");
    say(QCTNAME(TP) + " feels the rocks with " + HIS_HER(TP) + " hands.\n");
    return 1;
}
