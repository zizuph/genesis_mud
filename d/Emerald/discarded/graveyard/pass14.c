inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Dead end");
    set_long( "The tunnel here looks like it once continued"+
        " to the east, but now that way is blocked by fallen rocks.\n" );
 
    add_item(({"rocks","rock","rockfall"}), "The rockfall is "+
        "blocking the east exit. It looks much too large to clear, so it "+
        "looks like the only way out is back south.\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "pass13","south",0,1);
}
