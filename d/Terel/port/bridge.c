/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * bridge.c
 *
 * A bridge near the port. 
 */

#include "/d/Terel/include/Terel.h"
inherit PORT_DIR + "port_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("On wooden bridge");
    set_long("You are standing on the wooden bridge. The road " +
	     "continues in the northwest and southeast directions. " +
	     "The river floats from northeast to southwest where it " +
	     "reaches the sea. There is a distinct smell in the air.\n");
    
    add_item(({"bridge", "wooden bridge"}), "It's a robust wooden bridge.\n");
    add_item(({"river"}), "The river streams gently.\n");
    add_item(({"sea"}), "Far south you catch a glimpse of the sea.\n");

    add_exit(PORT_DIR + "road3", "northwest", 0);
    add_exit(PORT_DIR + "road9", "southeast", 0);
}
