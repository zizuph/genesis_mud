inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("damp tunnel");
    set_long( "This is a dark, cool tunnel, with many puddles "+
        "on the floor.\n" );
 
    add_item(({"puddles","puddle"}), "The puddles look dark and "+
        "murky.\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "pass10","northwest",0,1);
    add_exit(GRAVEYARD_DIR + "cave7","east",0,1);
}
