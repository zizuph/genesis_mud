inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Ant passage");
    set_long( "This is a rocky tunnel that slopes down to the "+
        "southeast.\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "pass7","north",0,1);
    add_exit(GRAVEYARD_DIR + "cave5","southeast",0,1);
}
