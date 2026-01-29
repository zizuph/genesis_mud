/*
 *	/d/Gondor/rohan/plains/j05.c
 *
 *	Coded by Olorin.
 *
 */
#pragma strict_types

inherit "/d/Gondor/rohan/plains/plain";

#include "/d/Gondor/defs.h"


public void
create_plain()
{
    set_geo("rocky");
    set_wet("high");
    set_grass("high dark green");
    set_land("the Westfold");
    set_where("southern");
    set_special(5);
    add_exit("k05", "north", 0, 5);
    add_exit("j06", "east",  0, 5);
    add_exit(ROH_DIR + "road/wr3",   "south", 0, 2);
    add_exit("j04", "west",  0, 5);

    set_npc_file(NPC_DIR + "deer");
    set_npc_number(2 + random(3));

    reset_room();
}
