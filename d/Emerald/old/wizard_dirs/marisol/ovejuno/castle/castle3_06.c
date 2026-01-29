/* Corridor-Stairs Third floor (6).
 * Coded by Marisol (12/8/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types
#include "defs.h"
inherit CASTLE_OV3;


void
create_castle_room()
{

    set_em_long("A persistent silence wraps up the old, dusty corridor. "+
        "Some dusty lamps are hanging on the wall unlit. The walls are "+
        "in a sorry condition, all dirty and abandoned. A lonely window "+
        "stands high at the end of this corridor. There are two closed "+
        "doors on both sides of the walls. The corridor intersects "+
        "another passage that runs from east to west. The smell of dust "+
        "is quite strong here.");

    add_item("corridor",
        "You are standing on a dusty corridor on the third floor of "+
        "the castle.\n");    

   add_item("window",
        "A glass window hangs on the north wall. The window is "+
        "painted all in black even the glass.\n");

   add_item("north wall",
        "The north wall doesn't differ much from the rest of the walls "+
        "in the corridor. The only difference is the glass window "+
        "set high on the wall.\n");

    add_exit("castle3_03.c", "south");
    add_exit("castle3_05.c", "east");
    add_exit("castle3_04.c", "west");
    

    reset_room();

}                                                                         

          
