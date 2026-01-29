/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * road9.c
 *
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
    set_short("Village road");
    set_long("You are standing on the eastern village road. " +
	     "It continues to the southeast and to the northwest " +
	     "where it reaches a bridge. " +
	     "There is a distinct smell in the air.\n");
    
    add_item(({"bridge", "wooden bridge"}), "It's a robust wooden bridge.\n");

    add_exit(PORT_DIR + "bridge", "northwest", 0);
    add_exit(PORT_DIR + "road10", "southeast", 0);
}
