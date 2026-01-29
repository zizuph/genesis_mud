/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * road6.c
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
	     "in the north and southwest directions. " +
	     "To the west you see some houses and to the east you see " +
	     "a river meeting a small bay. " +
	     "There is a distinct smell in the air.\n");
    
    add_item(({"houses"}), 
	     "The houses seem to make up the main body of the small " +
	     "fishing village.\n");
    
    add_item(({"bay"}),
	"You see some small fishing boats sailing out on the bay.\n");
    
    add_item(({"river"}), "It is quite wide here where it meets the bay.\n");

    add_exit(PORT_DIR + "road5",         "north",     0);
    // add_exit(PORT_DIR + "stable/stable", "west",      0);
    add_exit(PORT_DIR + "road7",         "southwest", 0);
}
