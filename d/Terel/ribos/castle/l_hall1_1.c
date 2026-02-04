/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * l_hall1_1.c
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
	     "It continues north, and ends in the dining room to the " +
	     "south.  There is a coat of arms beside the door.\n");
    
    add_item(({"coat", "coat of arms", "arms"}), 
	     "This coat of arms is set upon a shield.  The shield is yellow " +
	     "with a red stripe extending from the upper right to the lower " +
	     "left quadrants of the shield.  On the top portion, there is " +
	     "a sword, and on the bottom portion there is a singing angel.  " +
	     "all along the red stripe there are various musical symbols.\n");
    
    add_exit(CASTLE_DIR + "l_hall1_2",   "north", 0);
    add_exit(CASTLE_DIR + "dining_room", "south", 0);
    add_exit(CASTLE_DIR + "court", "east", 0);

    clone_object(DOOR_DIR + "guest1_in")->move(TO);
}
