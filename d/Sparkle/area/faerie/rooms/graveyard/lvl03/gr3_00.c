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
    set_long(grave_under3);
    add_my_desc("Claw marks are in the walls and ceiling.\n");

    set_underground();

    add_exit(GRAVE3_DIR + "gr3_02", "southwest");
    add_exit(GRAVE2_DIR + "gr2_00", "up");

    reset_room();
}

void
reset_room()
{

}