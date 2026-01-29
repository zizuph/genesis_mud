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
        + "outer and middle circles of the Elemental Temple. Bare walls "
        + "line the north and south part of the hallway. The hallway leads "
        + "west to the outer circle and east to the middle circle.\n\n");
                   
    add_exit(ELEMENTALIST_TEMPLE + "middle6", "east");
    add_exit(ELEMENTALIST_TEMPLE + "aeria", "west"); 
}
