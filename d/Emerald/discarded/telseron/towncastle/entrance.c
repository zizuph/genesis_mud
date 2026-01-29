inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    object drawbridge;
 
    set_short("Castle entrance");
    set_long( "You are inside the entrance of a rather old-"+
	     "looking castle. Off to one side, there is a stairway while "+
	     "further in you can see a rather large hall.\n" );
 
    add_item( ({ "stairway", "stairs" }),
	      "It is a narrow stairway with steep steps leading upwards.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TCASTLE_DIR + "hall", "south");
    add_exit(TCASTLE_DIR + "stairs", "up");
 
    drawbridge=clone_object(TCASTLE_DIR + "doors/drawbridge_a");
    drawbridge->move(this_object());
}
