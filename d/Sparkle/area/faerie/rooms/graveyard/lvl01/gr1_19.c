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
    set_long(grave_above3);
    add_my_desc("Trees and tombstones rise out of the fog, like dark " +
        "sentinals.\n");

    set_aboveground();
    headstone_moved = 2; // no headstone here

    add_exit(GRAVE1_DIR + "gr1_18",  "west");
    add_exit(GRAVE1_DIR + "gr1_15",  "northeast");
    add_exit(GRAVE1_DIR + "gr1_22",  "southeast");

    reset_room();
}

void
reset_room()
{
    add_npcs(0);
}

