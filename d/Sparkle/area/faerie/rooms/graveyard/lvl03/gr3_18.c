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
    add_my_desc("The passage ends here with broken bones scattered " +
        "around the coffins.\n");

    set_underground();

    add_exit(GRAVE3_DIR + "gr3_19", "east");
    add_exit(GRAVE3_DIR + "gr3_14", "north");

    reset_room();
}

void
reset_room()
{
    add_npcs(2);
}