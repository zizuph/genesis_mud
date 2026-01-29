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
    add_my_desc("An unholy feeling emanates from the south.\n");

    set_underground();

    add_exit(GRAVE3_DIR + "crypt03", "south");
    add_exit(GRAVE3_DIR + "gr3_01", "west");
    add_exit(GRAVE3_DIR + "gr3_00", "northeast");

    reset_room();
}

void
reset_room()
{
    add_npcs(2);
}