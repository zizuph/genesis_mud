/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave06.c
 *
 * A cave room.  The stones have no real meaning for now.
 */

#include "/d/Terel/include/Terel.h"
inherit ORC_CAVE_DIR + "cave_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + 
	     "A pile of small stones has been left in the corner.\n");
    
    DARK;
    
    add_item(({"pile", "stones"}),
	     "The stones form an arrow pointing east.\n");

    add_exit(ORC_CAVE_DIR + "cave05", "north");
    add_exit(ORC_CAVE_DIR + "cave07", "east");
}

