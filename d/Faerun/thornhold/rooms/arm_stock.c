/*
 * Thornhold
 * -- Twire/Gnim June 2016
 */
//#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_KEEP;

void
create_house()
{
    set_short("A locked caravan");
    set_long("This is the locked store room where the most valuable " +
             "items are stored from a caravan merchant.\n");
	
    add_exit(ROOM_DIR + "courtyard_north",  "out");

    reset_room();
}

void
reset_room()
{
   ::reset_room();
}
