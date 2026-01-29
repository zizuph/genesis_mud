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
    set_long(grave_under3);
    add_my_desc("Puddles of sickly looking water have gathered on the ground.\n");

    set_underground();

    add_exit(GRAVE3_DIR + "gr3_17", "south");
    add_exit(GRAVE3_DIR + "gr3_11", "west");
    add_exit(GRAVE3_DIR + "gr3_13", "east");

    reset_room();
}

void
reset_room()
{
    add_npcs(2);
}