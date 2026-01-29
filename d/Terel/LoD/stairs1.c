/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * stairs1.c
 *
 * Stairs down to legion of darkness quarter. Mortricia 920917
 * modified by Sorgum 941015
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "legion_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Stairs");
    set_long("You are standing in a staircase. It's lit up by a torch.\n");

    add_item(({"stair", "stairs"}), "The stairs are made of stone.\n");

    add_item(({"torch"}), "It's a simple looking torch, firmly attached " +
	     "to the wall.\n");

    add_item(({"wall", "walls"}), "The walls are made out of large " +
	     "stones. The stones must have been cut by an expert, since " +
	     "there are almost no gaps between them.\n");

    add_item(({"gap", "gaps"}), "Small amounts of dirty water emerges " +
	     "from the gaps.\n");
       
    add_exit("/d/Terel/common/town/mansion/wing_s4", "up", "@@go_up");
    add_exit(LOD_DIR + "stairs2", "down", 0);
}

public int
go_up()
{
    string name = TP->query_race_name();
    
    if (name == "dog" || name == "bat") return 1;
    return 0;
}
