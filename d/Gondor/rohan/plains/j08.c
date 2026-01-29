/*
 *	/d/Gondor/rohan/plains/j08.c
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
    set_geo("open");
    set_wet("high");
    set_grass("thick green");
    set_land("the Westfold");
    set_where("northern");
    set_special(2);
    add_exit("k08", "north", 0, 5);
    add_exit("j09", "east",  0, 5);
    add_exit("i08", "south", 0, 5);
    add_exit("j07", "west",  0, 5);
    
    set_npc_file(ROH_DIR + "npc/westfoldorc");
    set_npc_number(1);

    reset_room();
}
