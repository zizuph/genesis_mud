/* Corridor-Stairs Third floor (3).
 * Coded by Marisol (12/7/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types

#include "../defs.h"

inherit CASTLE_OV3;

#include <stdproperties.h>

void
create_castle_room()
{

    set_em_long("A persistent silence wraps up the old, dusty corridor. "+
        "Some dusty lamps are hanging on the walls unlit. The walls are "+
        "in a sorry condition, all dirty and abandoned. The smell of "+
        "dust is quite strong here. The corridor intersects "+
        "another passage that runs from east to west.\n");

    add_item("corridor",
        "You are standing on a dusty corridor on the third floor of "+
        "the castle.\n");    

    add_exit("castle3_02", "south");
    add_exit("castle3_06", "north");
    add_exit("castle3_05", "east");
    add_exit("castle3_04", "west");
}                                                                         

