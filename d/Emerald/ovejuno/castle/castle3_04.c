/* Corridor-Stairs Third floor (4).
 * Coded by Marisol (12/8/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types

#include "../defs.h"

inherit CASTLE_OV3;

void
create_castle_room()
{
    set_em_long("A persistent silence wraps up the old, dusty corridor. "+
        "Some dusty lamps are hanging on the wall unlit. The walls are "+
        "in a sorry condition, all dirty and abandoned. A lonely window "+
        "stands high at the end of this corridor. The corridor "+
        "intersects another passage one that runs from north to south. "+
        "The smell of dust is quite strong here.\n");

    add_item("corridor",
        "You are standing on a dusty corridor on the third floor of "+
        "the castle.\n");    

   add_item("window",
        "A glass window hangs on the west wall. The window is "+
        "painted all in black even the glass.\n");

   add_item("west wall",
        "The west wall doesn't differ much from the rest of the walls "+
        "in the corridor. The only difference is the glass window "+
        "set high on the wall.\n");

    add_exit("castle3_03", "south");
    add_exit("castle3_06", "north");
    add_exit("castle3_05", "east");
}      
