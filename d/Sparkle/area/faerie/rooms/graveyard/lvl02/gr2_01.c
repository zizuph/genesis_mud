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
    add_my_desc("A feeling of death fills the room and seems unnatural.\n");

    set_underground();

    add_exit(GRAVE2_DIR + "gr2_02", "east");
    add_exit(GRAVE2_DIR + "gr2_03", "southwest");

    reset_room();
}

void
reset_room()
{
    add_npcs(1);
}