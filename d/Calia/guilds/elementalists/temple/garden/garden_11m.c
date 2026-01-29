/*
 * Garden Room of the Elemental Garden of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "../defs.h"

inherit GARDEN_ROOM_BASE;

// Defines

// Prototypes

public void
create_garden_room()
{
    add_exit(ELEMENTALIST_GARDEN + "garden_10m", "north");
    add_exit(ELEMENTALIST_GARDEN + "garden_11l", "west");
    add_exit(ELEMENTALIST_GARDEN + "pyros_g", "southeast");
}
