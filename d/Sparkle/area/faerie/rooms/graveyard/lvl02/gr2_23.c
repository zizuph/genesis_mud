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
    set_long(grave_under1);
    add_my_desc("\n");

    set_underground();

    add_exit(GRAVE2_DIR + "gr2_22", "west");
    add_exit(GRAVE1_DIR + "gr1_23", "up");

    reset_room();
}

void
reset_room()
{
    add_npcs(1);
}