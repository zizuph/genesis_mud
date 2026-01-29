/*
 * The graveyard of Faerie
 * By Finwe, September 1999
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
    set_long(grave_above1);
    add_my_desc("The trees bend in the wind, casting long shadows across the ground.\n");

    set_aboveground();
    headstone_moved = 2; // no headstone here

    add_exit(GRAVE1_DIR + "gr1_06",  "south");
    add_exit(GRAVE1_DIR + "gr1_01",  "northeast");
    add_exit(FOREST_DIR + "ctroad13",  "southwest");

    reset_room();
}

void
reset_room()
{
    add_npcs(0);
}

