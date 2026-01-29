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
    add_my_desc("Puddles of sickly looking water have gathered on " +
        "the ground. Holes have been clawed into the wall, that lead up " +
        "and out of the grave.\n");

    set_underground();
    set_add_ladder();

    add_exit(GRAVE2_DIR + "gr2_11", "northeast");
    add_exit(GRAVE1_DIR + "gr1_16", "up");

    reset_room();
}

void
reset_room()
{

}