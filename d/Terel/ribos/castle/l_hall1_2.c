/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * l_hall1_2.c
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit CASTLE_DIR + "hall_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();

    set_long(query_long() +
	     "It continues north, and ends in the dining " +
	     "room to the south.  There is a coat of arms beside the door.\n");
    
    add_item(({"coat", "coat of arms", "arms"}), 
	     "This coat of arms is circular in shape.  At its center, " +
	     "stands the sun, partially eclipsed by a castle.  All " +
	     "around the edges are runes and symbols, and you know not " +
	     "how to translate them.\n");
    
    add_exit(CASTLE_DIR + "l_hall1_3", "north", 0);
    add_exit(CASTLE_DIR + "l_hall1_1", "south", 0);

    clone_object(DOOR_DIR + "guest2_in")->move(TO);    
}
