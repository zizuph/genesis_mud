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
    add_exit(ELEMENTALIST_TEMPLE + "meditation", "west", "@@cannot_enter_middle_circle", 1, "@@cannot_see_middle_circle");
    add_exit(ELEMENTALIST_TEMPLE + "diabrecho", "north");
    add_exit(ELEMENTALIST_TEMPLE + "outer12", "south"); 
}
