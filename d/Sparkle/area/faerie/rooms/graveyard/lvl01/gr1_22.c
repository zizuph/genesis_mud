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
    set_long(grave_above5);
    add_my_desc("The land is dark, and ominious with the many graves here.\n");

    set_aboveground();
    headstone_moved = 2; // no headstone here

    add_exit(GRAVE1_DIR + "gr1_23",  "east");
    add_exit(GRAVE1_DIR + "gr1_19",  "northwest");

    reset_room();
}

void
reset_room()
{

}

