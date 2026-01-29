/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * road4.c
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
    set_long("You are standing on the Village road. It continues " +
	     "in the northeast and south directions. " +
	     "To the east you see a river, and beyond it, at the " +
	     "eastern river bank you see another road. Some distance " +
	     "to the south you see the sea. There is a distinct smell " +
	     "in the air.\n");
    
    add_item(({"river"}), "The river floats in the southern direction.\n");
    
    add_item(({"sea"}), "The sea looks cold and blue.\n");
    
    add_item(({"smell"}), "How can you examine a smell?\n");

    add_exit(PORT_DIR + "road3", "northeast", 0);
    add_exit(PORT_DIR + "road5", "south",     0);
}
