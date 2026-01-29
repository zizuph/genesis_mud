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
    add_my_desc("Eerie sounds echo throughout the graves.\n");

    set_underground();

    add_exit(GRAVE3_DIR + "gr3_04", "west");
    add_exit(GRAVE3_DIR + "gr3_09", "southeast");
    add_exit(GRAVE2_DIR + "gr2_05", "up");


    reset_room();
}

void
reset_room()
{

}