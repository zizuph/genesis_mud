/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("Bottom of a staircase");
    set_long("This is a narrow staircase winding up and a passage leading " +
	     "north. Walls, stairs and everything is stone and cold to the " +
	     "touch; and the air feels just as cold. There is water on the " +
	     "floor here, it is some brownish mud, really.\n");
    
    add_exit(CAVERN + "b6","up");
    add_exit(CAVERN + "a4","north");
    
    DARK;
    add_prop(OBJ_I_CONTAIN_WATER, 50000);
    
    add_item(({"mud","water","ground"}),
	     "It's dark brown water, very muddy, on the ground here. You " +
	     "can't see anything in it, but since the water is only a few " +
	     "inches deep, there probably isn't anything there.\n");
    add_search(({"mud","water","ground"}),30,/*long search!*/
	       "You search everything but in vain. There is nothing here.\n");
}
