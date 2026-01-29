/*
 * Hallway of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;

// Defines

// Prototypes

public void
create_temple_room()
{
    set_short("Elemental Temple Connecting Hallway");
    set_long("This small connnecting hallway provides passage between the "
        + "stairway and the conduit chamber.\n\n");
                   
    add_exit(ELEMENTALIST_TEMPLE + "stairwell4", "north");
    add_exit(ELEMENTALIST_TEMPLE + "conduit", "south"); 
}
