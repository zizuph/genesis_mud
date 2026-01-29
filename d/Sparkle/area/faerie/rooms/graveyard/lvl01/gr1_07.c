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
    add_my_desc("A dark feeling seems to settle over everything here in " +
    "the graveyard. To the northeast is a large crypt.\n");

    set_aboveground();
    headstone_moved = 2; // no headstone here

    add_exit(GRAVE1_DIR + "gr1_11",  "south");
    add_exit(GRAVE1_DIR + "gr1_06",  "west");
    add_exit(GRAVE1_DIR + "crypt01",  "northeast");
    add_exit(GRAVE1_DIR + "gr1_12",  "southeast");

    add_item(({"crypt", "large crypt"}),
        "It is a large building to the northeast. It looks evil and dangerous.\n");

    reset_room();
}

void
reset_room()
{
    add_npcs(0);
}

