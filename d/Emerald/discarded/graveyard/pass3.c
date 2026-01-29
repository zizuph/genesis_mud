inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Cold passage under graveyard");
    set_long( "You are walking along a cold tunnel below the "+
        "graveyard. To the southeast you can just make out a glimpse of "+
        "light.\n" );
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "pass2","west",0,1);
    add_exit(GRAVEYARD_DIR + "cave8","southeast",0,1);
}
