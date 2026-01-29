/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * road5.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit PORT_DIR + "port_room";

/*
 * Global Variables
 */
object traveller;

/*
 * Function name: reset_room
 * Description:   clone the traveller if necessary
 */
public void
reset_room()
{
    if (!traveller) {
        traveller = clone_object(PORT_DIR + "monster/traveller");
	traveller->move_living("arrives", TO);
    }
}

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
	     "in the north and south directions. " +
	     "To the east you see a river, and beyond it, at the " +
	     "eastern river bank you see another road and some houses. " +
	     "To the south you see the sea. There is a distinct smell " +
	     "in the air.\n");
    
    add_item(({"river"}), 
	     "The river floats gently in the southern direction. It " +
	     "reaches the sea southeast from here.\n");
    
    add_item(({"sea"}), "The sea looks cold and blue.\n");

    add_exit(PORT_DIR + "road4", "north", 0);
    add_exit(PORT_DIR + "road6", "south", 0);

    set_alarm(1.0, -1.0, "reset_room");
}
