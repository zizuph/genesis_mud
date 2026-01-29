/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * road11.c
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
    set_long("You are standing at the end of the eastern village road. " +
	     "The sea covers the whole southern horizon. " +
	     "South from here is a pier going out in the sea, " +
	     "and to the west you see a cozy wooden hut. " +
	     "There is a distinct smell in the air.\n");
    
    add_item(({"pier", "wooden pier"}), 
	     "It's a very robust wooden pier that will withstand " +
	     "the fierce storms that occasionally strike the village.\n");
    
    add_item(({"sea"}), 
	     "It looks cold and blue. Gazing south you see no trace " +
	     "of land - only a few sailing ships struggling in the " +
	     "brisk western wind.\n");
    
    add_item(({"hut", "wooden hut", "cozy hut"}), 
	     "The cozy wooden hut looks very inviting.\n");

    add_exit(PORT_DIR + "road10",  "north", 0);
    add_exit(PORT_DIR + "epier_n", "south", 0);
    add_exit(PORT_DIR + "pub",     "west",  0);
}
