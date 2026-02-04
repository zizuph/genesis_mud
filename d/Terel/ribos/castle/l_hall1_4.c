/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * l_hall1_4.c
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
	     "It continues northeast and south.  There is" +
	     " a coat of arms hanging near the door.\n");
    
    add_item(({"coat", "coat of arms", "arms"}), 
	     "This coat of arms is in the shape of a shield.  " +
	     "It is yellow in colour, with a thick red stripe, " +
	     "bordered by a thin black line, extending from the " +
	     "upper left to the lower right.  Within this " +
	     "stripe you can see three white lions.  They look to " +
	     "be climbing up the stripe.  You can see a tree atop, " +
	     "and a tree below, the red stripe.  These trees almost " +
	     "look like a stalk of broccoli.\n");
    
    add_exit(CASTLE_DIR + "l_hall1_5", "northeast", 0);
    add_exit(CASTLE_DIR + "l_hall1_3", "south",     0);

    clone_object(DOOR_DIR + "guest4_in")->move(TO);    
}
