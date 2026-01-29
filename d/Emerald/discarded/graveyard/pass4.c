inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Small tunnel");
    set_long( "You are walking along a narrow passage. To the south"
        +" the tunnel seems to open up into a cave and there is a junction "+
        "to the north.\n" );
 
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);
 
 
    add_exit(GRAVEYARD_DIR + "pass2","north",0,1);
    add_exit(GRAVEYARD_DIR + "cave2","south",0,1);
}
