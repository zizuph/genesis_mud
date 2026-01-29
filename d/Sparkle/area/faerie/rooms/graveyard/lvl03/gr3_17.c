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
    add_my_desc("Eerie sounds echo throughout the graveyard.\n");

    set_underground();

    add_exit(GRAVE3_DIR + "gr3_12", "north");
    add_exit(GRAVE3_DIR + "gr3_21", "southeast");

    reset_room();
}

void
reset_room()
{

}
