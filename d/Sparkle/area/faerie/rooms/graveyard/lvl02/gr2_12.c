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
    set_long(grave_under5);
    add_my_desc("\n");

    set_underground();

    add_exit(GRAVE2_DIR + "gr2_17", "south");
    add_exit(GRAVE2_DIR + "gr2_13", "east");
    add_exit(GRAVE2_DIR + "gr2_11", "west");
    add_exit(GRAVE2_DIR + "gr2_07", "northwest");

    reset_room();
}

void
reset_room()
{

}