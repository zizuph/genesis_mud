/*
 * Filename: /d/Krynn/dargaard/room/f_court.c
 *
 * Describe the front courtyard just south of  Dargaard Keep.
 *
 * 19951004 Vidur
 */

#include "local.h"

inherit OUTROOM; /* This room is out in the open */

/*
 * Function name: create_dargaard_room
 * Description:   Set exits, desc, and proparties for the room.
 */

void
create_dargaard_room() {
    set_short_desc("in the front courtyard of Dargaard's Keep");
    set_long_desc("The dark Dargaard's Keep rises up high into the sky " +
	 "infront of you. It looks like it has been burned a while back " +
	 "in time. "+
	 "To the north you can see the gate of the burned Keep, and " +
	 "south of here there is a cliff. You can also walk along the " +
	 "cliff to the west or to the east, leading into other parts " +
	 "of the courtyard.");
    
    add_item("cliff", "This sheer cliff is now the outer wall of the " +
	     "Keep. The south facing-\"wall\" drop straight down for over " +
	     "300 meters, so be carefull.\n");
    add_item("gate", "The gate seems dark and large from over here. It " +
	     "surely is closed at the moment. To get " +
	     "a better look at the gate, you must move closer.\n");
}

