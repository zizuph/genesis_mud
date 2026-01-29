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
    add_my_desc("It swirls up into haunting forms and disappates, only " +
    "to be replaced by more.\n");

    set_aboveground();
    headstone_moved = 2; // no headstone here

    add_exit(GRAVE1_DIR + "gr1_03",  "north");
    add_exit(GRAVE1_DIR + "gr1_07",  "east");

    reset_room();
}

void
reset_room()
{

}

