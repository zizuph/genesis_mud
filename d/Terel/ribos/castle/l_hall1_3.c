/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * l_hall1_3.c
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
	     "It continues north and south.  There is a " +
	     "coat of arms hanging near the door.\n");
    
    add_item(({"coat", "coat of arms", "arms"}),
	     "This coat of arms is in the shape of a shield.  Its coloured " +
	     "green all around, except for the thick black border.  " +
	     "A banner starts from the upper left, and makes its way " +
	     "down to the lower right, and the banner says 'May the " +
	     "gods bless all of our sons.  Atop the banner you see " +
	     "a golden hoop.  Below it, you see a large stone.\n");

    add_exit(CASTLE_DIR + "l_hall1_4", "north", 0);
    add_exit(CASTLE_DIR + "l_hall1_2", "south", 0);

    clone_object(DOOR_DIR + "guest3_in")->move(TO);    
}
