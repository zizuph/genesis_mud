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
    add_exit(ELEMENTALIST_TEMPLE + "sacristy", "north", "@@cannot_enter_middle_circle", 1, "@@cannot_see_middle_circle");
    add_exit(ELEMENTALIST_TEMPLE + "outer13", "east");
    add_exit(ELEMENTALIST_TEMPLE + "gu", "west");
    add_exit(ELEMENTALIST_TEMPLE + "chapel", "south"); 
}
