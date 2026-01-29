/*
 * The graveyard of Faerie
 * By Finwe, August 2004
 */
 
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/std/room"; 
inherit GRAVEYARD_BASE;
 
void
create_graveyard_room()
{
    set_long(grave_under4);
    add_my_desc("Claw marks are in the walls and ceiling at this end " +
        "of the tunnels.\n");

    set_underground();

    add_exit(GRAVE3_DIR + "gr3_04", "north");
    add_exit(GRAVE3_DIR + "gr3_13", "south");

    reset_room();
}

void
reset_room()
{
    add_npcs(2);
}