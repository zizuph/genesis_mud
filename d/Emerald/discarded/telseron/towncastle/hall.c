inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    set_long( "You are in the main hall of the castle. From "+
	     "the east you can make out the smell of food. South of here "+
              "you can see a staircase.\n");
    set_short("Main hall");
 
    add_item("staircase", "It is a normal staircase.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TCASTLE_DIR + "entrance", "north");
    add_exit(TCASTLE_DIR + "kitchen", "east");
    add_exit(TCASTLE_DIR + "tower_bottom", "south");
}
