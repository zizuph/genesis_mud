/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave08.c
 *
 * A cave room.
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
	    "They all were deserted long ago.  There is a sign on the " +
	     "wall.\n");

    DARK;
    
    add_item("sign", "It says: Property of the Terel orc family.\n");

    add_cmd_item("sign", "read", "\"Property of the Terel orc family.\"\n");

    add_exit(ORC_CAVE_DIR + "cave07", "southwest");
    add_exit(ORC_CAVE_DIR + "cave09", "north");
    add_exit(ORC_CAVE_DIR + "cave12", "southeast");
}
