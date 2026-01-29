/*
 * The graveyard of Faerie
 * By Finwe, September 1999
 */
 
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>

inherit "/std/room"; 
inherit GIB_BASE;
 
void
create_gib_room()
{

    add_exit(GIB_DIR + "gib21",  "south");
    add_exit(GIB_DIR + "gib16",  "northeast");


    reset_room();
}

void
reset_room()
{
    add_npcs();
}

