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
    add_my_desc("Broken bones lay scattered around here, and buried by " +
        "the collapsed grave.\n");

    set_underground();

    add_exit(GRAVE2_DIR + "gr2_07", "east");
    add_exit(GRAVE3_DIR + "gr3_06", "down");

    reset_room();
}

void
reset_room()
{

}