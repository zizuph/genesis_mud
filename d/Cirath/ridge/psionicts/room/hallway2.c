#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"

void
create_room()
{
    	set_short("a small tunnel");
   	set_long("You are in a small tunnel carved in a rock formation. "+
            "Light eminates from the tunnel walls and a tunnel leads "+
            "north and south from here.\n"); 
            
    INSIDE
    
    add_exit(PSION_ROOM+"hallway3.c", "north", 0, 1);
    add_exit(PSION_ROOM+"hallway1.c", "south", 0, 1);
}