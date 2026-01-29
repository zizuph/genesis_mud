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

    add_exit(GIB_DIR + "gib10",  "northeast");
    add_exit(GIB_DIR + "gib09",  "northwest");
    add_exit(GIB_DIR + "gib14",  "southwest");
    add_exit(GIB_DIR + "gib15",  "down");

    reset_room();
}

void
reset_room()
{
    add_npcs();
}

