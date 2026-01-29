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
    set_long(grave_above4);
    add_my_desc("The grass moves in the breeze.\n");

    set_aboveground();
    headstone_moved = 2; // no headstone here

    add_exit(GRAVE1_DIR + "gr1_04",  "west");
    add_exit(GRAVE1_DIR + "gr1_09",  "southeast");

    reset_room();
}

void
reset_room()
{
    add_npcs(0);
}

