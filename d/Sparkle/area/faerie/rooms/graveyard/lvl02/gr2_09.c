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
    set_long(grave_under2);
    add_my_desc("Claw marks are in the walls and ceiling.\n");

    set_underground();

    add_exit(GRAVE2_DIR + "gr2_10", "east");
    add_exit(GRAVE2_DIR + "gr2_14", "southwest");
    add_exit(GRAVE3_DIR + "gr3_09", "down");

    reset_room();
}

void
reset_room()
{
    add_npcs(1);
}