/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave13.c
 *
 * An empty room in the cave.  The entrance to the cave lower level is here.
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
    set_long(query_long() + "There is a sign on the wall.  In the corner " +
	     "of the cavern is a small tunnel leading downwards.\n");

    add_item("sign", "It says: Don't let the children play near the " +
	     "wolves.\n");
    add_cmd_item("sign", "read", "\"Don't let the children " +
		 "play near the wolves.\"\n");

    DARK;
    
    add_exit(ORC_CAVE_DIR + "cave09", "west");
    add_exit(ORC_CAVE_DIR + "cave15", "northwest");
    add_exit(ORC_CAVE_DIR + "cave17", "down", "@@go_down");    
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "It smells kind of like a dog who has been playing in a sulfur " +
	"andbox.\n";
}

int
go_down()
{
    write("There is too much mud and debris in the way.  It should get " +
	  "cleared away soon.\n");
    return 1;
}
