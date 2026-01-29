inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Twisting passage");
    set_long( "You are standing in a twisting tunnel under the "+
        "the graveyard.\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "cave8","northwest",0,1);
    add_exit(GRAVEYARD_DIR + "pass14","north",0,1);
}
