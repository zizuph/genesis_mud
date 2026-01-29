
/*
    
    This is a dark room.

*/

inherit "/std/room";

#include <stdproperties.h>  // required for ROOM_I_LIGHT

public void
create_room()
{
    set_short("A filthy a cave");
    set_long("This is a filthy cave.  If you have a light, you can see.\n");

    add_prop(ROOM_I_LIGHT, 0);    
}
