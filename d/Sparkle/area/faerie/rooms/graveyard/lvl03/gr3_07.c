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
    add_my_desc("The tunnel ends here. A feeling of death permeates the grave.\n");

    set_underground();

    add_exit(GRAVE3_DIR + "gr3_11", "south");
    add_exit(GRAVE3_DIR + "crypt03", "northeast");

    reset_room();
}

void
reset_room()
{

}