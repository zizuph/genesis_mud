/*
 * Outer Circle of the Elemental Temple of Calia
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
    add_exit(ELEMENTALIST_TEMPLE + "refectory", "north");
    add_exit(ELEMENTALIST_TEMPLE + "outer3a", "west");
    add_exit(ELEMENTALIST_TEMPLE + "outer6", "southeast"); 
}
