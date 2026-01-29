/*
 *	/d/Gondor/rohan/plains/e11.c
 *
 *	Coded by Olorin.
 *
 */
#pragma strict_types

inherit "/d/Gondor/rohan/plains/plain";

#include "/d/Gondor/defs.h"

static object  Deer;

public void
create_plain()
{
    set_geo("open");
    set_wet("damp");
    set_grass("long, dark green and spicy");
    set_land("the Eastfold");
    set_where("northwest");
    set_special(5);
    add_exit("f11", "north", 0, 5);
    add_exit("e12", "east",  0, 5);
    add_exit(ROH_DIR + "road/er4",   "south", 0, 2);
    add_exit(ROH_DIR + "road/er3",   "west",  0, 2);
    
    set_npc_file(NPC_DIR + "deer");
    set_npc_number(1);

    reset_room();
}
