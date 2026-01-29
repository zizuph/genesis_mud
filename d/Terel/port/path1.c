/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * path1.c
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
    set_short("Village path");
    set_long("You are standing on a muddy village path. The path " +
	     "continues in the east-west direction. To the east " +
	     "it connects to a road. You can also enter an old " +
	     "wooden house by going south. To the north there is another " +
	     "house. There is a distinct smell in the air.\n");
    
    add_item(({"house", "houses"}), 
	     "The houses surrounding the path are all made of timber " +
	     "from the forest north of the village.\n");

    add_exit(PORT_DIR + "path2", "west",  0);
    add_exit(PORT_DIR + "road7", "east",  0);
    add_exit(PORT_DIR + "shop",  "south", 0);
    add_exit(PORT_DIR + "hotel", "north", 0);
}
