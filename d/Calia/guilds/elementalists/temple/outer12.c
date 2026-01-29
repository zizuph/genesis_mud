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
        + "of the Elementals of Calia. To the southeast you spot a room "
        + "inlaid with gold and gemstones that you suspect is the temple "
        + "treasury.\n\n"); 

    try_item( ({ "southeast", "treasury", "gnomes" }),
        "The room to your southeast appears to be even more sparkly than "
      + "the rest of the temple, if that's even possible. You suspect that "
      + "it is the temple treasury given the gnomes that are busying "
      + "themselves there.\n");
      
    add_exit(ELEMENTALIST_TEMPLE + "outer10", "north");
    add_exit(ELEMENTALIST_TEMPLE + "pyros", "southwest"); 
    add_exit(ELEMENTALIST_TEMPLE + "bank", "southeast"); 
}
