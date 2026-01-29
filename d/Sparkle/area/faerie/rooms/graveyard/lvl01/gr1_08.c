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
    set_long(grave_above2);
    add_my_desc("A howling wind blows through the graveyard. It blows " +
        "around you then leaves.\n");

    set_aboveground();
    headstone_moved = 2; // no headstone here

    add_exit(GRAVE1_DIR + "gr1_04",  "north");
    add_exit(GRAVE1_DIR + "gr1_13",  "south");
    add_exit(GRAVE1_DIR + "gr1_14",  "southeast");

    reset_room();
}

void
reset_room()
{

}

