inherit "/std/room";
 
#include "default.h"
 
void
create_room()
{
    set_short("By moat");
    set_long( "Here it looks like you might be able to wade into "+
	     "the moat. However, the smell is not what you'd call pleasant, "+
	     "and you can't see any way to climb up on the other side. "+
	     "However, there might be something on the other side of the "+
	     "castle. East of here there is a drawbridge that normally is "+
         "used to gain access to the castle.\n");
 
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
 
    add_exit(TCASTLE_DIR + "outside", "east");
    add_exit(TCASTLE_DIR + "moat2", "south");
}
