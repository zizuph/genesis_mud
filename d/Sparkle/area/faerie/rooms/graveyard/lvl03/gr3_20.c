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
    add_my_desc("Puddles of sickly looking water have gathered on the ground.\n");

    set_underground();

    add_exit(GRAVE3_DIR + "gr3_16", "northwest");

    reset_room();
}

void
reset_room()
{
    add_npcs(2);
}