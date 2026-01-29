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
    set_short("Inside the Elemental Temple of Calia");
    set_long("You stand inside the Elemental Temple of Calia, an ornately "
        + "constructed building that houses those devoted to the service "
        + "of the Elementals of Calia. To the northwest, you see what "
        + "appears to be a lapidary.\n\n"); 
    
    try_item( ({ "lapidary", "northwest" }),
        "To the northwest you spot a store that houses lots of gems for "
      + "sale, otherwise known as a lapidary.\n");
      
    add_exit(ELEMENTALIST_TEMPLE + "outer1", "northeast");
    add_exit(ELEMENTALIST_TEMPLE + "outer7", "south"); 
    add_exit(ELEMENTALIST_TEMPLE + "lapidary", "northwest", "@@cannot_enter_restrict_resource_banned",1, "@@cannot_see_restrict_resource_banned"); 
}
