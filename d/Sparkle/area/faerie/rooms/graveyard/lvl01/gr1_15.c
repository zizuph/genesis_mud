/*
 * The graveyard of Faerie
 * By Finwe, August 2004
 */
 
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>

inherit "/std/room"; 
inherit GRAVEYARD_BASE;
 
void
create_graveyard_room()
{
    set_long(grave_above2);
    add_my_desc("Dead trees dot the land. Their branches cast long " +
        "shadows over the ground.\n");

    set_aboveground();
    headstone_moved = 2; // no headstone here

    add_exit(GRAVE1_DIR + "gr1_10",  "north");
    add_exit(GRAVE1_DIR + "gr1_19",  "southwest");

    reset_room();
}

void
reset_room()
{
    add_npcs(0);
}

