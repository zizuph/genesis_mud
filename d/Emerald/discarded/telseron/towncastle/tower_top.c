inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    set_short("Top of tower");
    set_long( "There are openings in the wall all the way around "+
	     "the room. Through them, you can see out on a vast area around "+
	     "the castle.\n" );
 
    add_item( ({ "area", "vast area", "view" }),
	      "Just below the castle to the north, you can see a small " +
              "township. From the township there is a small road winding " +
              "away into the forest. In all other directions, all you can " +
              "see is trees.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TCASTLE_DIR + "tower_middle", "down");
}
