/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * road7.c
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
    set_long("You are standing on the village road. It continues " +
	     "in the northeast and south directions. To the west " +
	     "a path opens up, and to the east you see a small bay. " +
	     "On the other side of the bay you see some houses. " +
	     "To the south you see something that looks like a pier " +
	     "going out in the sea. " +
	     "There is a distinct smell in the air.\n");
    
    add_item(({"path"}), "It looks pretty muddy.\n");
    
    add_item(({"bay"}),
	     "To the northeast of the bay, a river floats out into it. " +
	     "Out on the bay you see some small fishing boats sailing.\n");
    
    add_item(({"houses", "other side"}), 
	     "There are houses on the east side of the bay, but you " +
	     "cannot figure out there use from here.\n");
    
    add_item(({"sea"}),	"The sea looks blue and cold.\n");
    
    add_item(({"pier"}), 
	     "It looks like a rather sturdy wooden pier. It must have " +
	     "endured quite many storms.\n");

    add_exit(PORT_DIR + "road6", "northeast", 0);
    add_exit(PORT_DIR + "road8", "south",     0);
    add_exit(PORT_DIR + "path1", "west",      0);
}

