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
    set_long(grave_above1);
    add_my_desc("A chilly feeling permeates the graveyard.\n");

    set_aboveground();
    headstone_moved = 2; // no headstone here

    add_exit(GRAVE1_DIR + "gr1_15",  "south");
    add_exit(GRAVE1_DIR + "gr1_09",  "west");

    reset_room();
}

void
reset_room()
{

}

