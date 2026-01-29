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
    add_exit(ELEMENTALIST_TEMPLE + "psuchae", "east");
    add_exit(ELEMENTALIST_TEMPLE + "outer1a", "west"); 
}
