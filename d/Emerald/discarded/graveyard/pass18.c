inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
 
void
create_room()
{
    set_short("Tunnel");
    set_long( "This tunnel seems to be man made, unlike the "+
        "rest of this area. The walls look to have been labouriously "+
	"chiselled from the solid rock, and although the floor is not "+
        "perfectly smooth, it is much easier to walk here without stumbling"+
        ".\n" );
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
 
    add_exit(GRAVEYARD_DIR + "pass19","northeast",0,1);
    add_exit(GRAVEYARD_DIR + "cave1","south",0,1);
}
