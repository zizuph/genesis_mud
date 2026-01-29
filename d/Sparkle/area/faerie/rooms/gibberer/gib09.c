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

    add_exit(GIB_DIR + "gib08",  "west");
    add_exit(GIB_DIR + "gib05",  "northeast");
    add_exit(GIB_DIR + "gib13",  "southeast");

    reset_room();
}

void
reset_room()
{
    add_npcs();
}

