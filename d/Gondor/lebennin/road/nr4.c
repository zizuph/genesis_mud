/*
 *	/d/Gondor/lebennin/road/nr4.c
 *
 *	This version:
 *	Copyright (c) 1997 by Christian Markus
 *
 *	Modification log:
 *	 2-Feb-1997, Olorin:	General revision,
 *				changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/lebennin/road/road.c";

#include "/d/Gondor/defs.h"

static object  GHop;

public void
create_road()
{
    set_area("northeast");
    set_areadesc("field");
    set_grass("light green");

    add_exit(LEB_DIR + "road/nr3",   "north",     0, 3);
    add_exit(LEB_DIR + "road/ghop2", "south",     0, 2);
    add_exit(LEB_DIR + "road/nr5",   "southwest", 0, 4);

    set_extraline("The road leads north and southwest. South of it " +
	"lies a bushy field.");
    add_rammas();
    add_road(1, "The road runs north to Minas Tirith and southwest " +
	"across the plains of Lebennin towards Pelargir upon Anduin " +
        "in the south.");
    add_ground();
    add_white_mountains("north");

    reset_room();
}

public void
reset_room()
{
    GHop = clone_npc(GHop, NPC_DIR + "grasshopper");
}


