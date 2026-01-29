/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * road2.c
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
    set_short("Southern road");
    set_long("You are standing on the road to the enchanted forest. " +
	     "The road continues in the northeast and south " +
	     "directions, and to the south it reaches a gate. " +
	     "To the north you see a great forest, and to the south " +
	     "there is a tall wooden fence, in which the gate seems " +
	     "to be the only way to go beyond. Above the fence you " +
	     "see some roofs.\n");

    add_item(({"forest", "enchanted forest"}), 
	     "The forest is great; it covers the whole northern " +
	     "horizon.\n");

    add_item(({"gate"}), "The wooden gate seems to be locked, but you must " +
	     "go closer to be sure.\n");

    add_item(({"fence"}), "The fence is very high, but you can see some " +
	     "rooftops above the rim.\n");
    
    add_exit(PORT_DIR + "road1",  "northeast", 0);
    add_exit(PORT_DIR + "n_gate", "south",     0);
}
