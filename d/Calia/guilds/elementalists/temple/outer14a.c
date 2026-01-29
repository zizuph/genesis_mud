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
    add_exit(ELEMENTALIST_TEMPLE + "seeker_start", "north", "@@cannot_enter_middle_circle", 1, "@@cannot_see_middle_circle");
    add_exit(ELEMENTALIST_TEMPLE + "pyros", "east"); 
    add_exit(ELEMENTALIST_TEMPLE + "outer14", "west");
    add_exit(ELEMENTALIST_TEMPLE + "library", "south","@@cannot_enter_restrict_resource_banned",1, "@@cannot_see_restrict_resource_banned");
}
