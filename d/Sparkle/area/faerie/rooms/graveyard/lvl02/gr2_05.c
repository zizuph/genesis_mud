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
    set_long(grave_under5);
    add_my_desc("Plant roots hang from the ceiling and grow out of " +
        "the walls.\n");

    set_underground();

    add_exit(GRAVE2_DIR + "gr2_04", "west");
    add_exit(GRAVE2_DIR + "gr2_08", "southwest");
    add_exit(GRAVE3_DIR + "gr3_05", "down");

    reset_room();
}

void
reset_room()
{
    add_npcs(1);
}
