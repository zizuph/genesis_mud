inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Tunnel");
    set_long( "You are walking along a damp, uneven tunnel that "
        +"winds its way into the depths of the earth.\n" );
 
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);
 
    add_exit(GRAVEYARD_DIR + "junction","north",0,1);
    add_exit(GRAVEYARD_DIR + "pass2","southeast",0,1);
}
