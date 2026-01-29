/*
    An outside room in the mountains between the Gelan and Argos areas.   

    Bishop, July 2003.
*/

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include "defs.h"

void
create_room()
{
    set_short("Winding mountain path");
    
    set_long("You stand on a rugged path that trails along a mountain" +
        " ridge. To the north, obscured by some boulders, you can see" +
        " a marble road. To the south the path disappears around an" +
        " outcropping.\n");
        
    add_item("path", "The path is just barely visible. It appears to" +
        " start near the marble road to the north, and snakes around" +
        " an outcropping to the south.\n");
    add_item("outcropping", "It is just a natural bulge in the ridge" +
        " that obscures your view of where the path ends up.\n");
    add_item("boulders", "Huge mounds of granite, these boulders dot"  +
        " the mountains and their foothills, interspersed with the trees" +
        " of the forest.\n"); 
    add_item("ridge", "This ridge runs along the side of the mountain." +
        " You are closer to the base of the mountain than to the top.\n");
        
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_HIDE, 50);
    
    add_exit("/d/Calia/argos/nwterr/rooms/r8", "north", 0);
    add_exit(TOWER + "tower_outside1.c", "south", 0);
}
       