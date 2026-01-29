/*
 * An underground river near the beach in Faerie
 * By Finwe, August 2004
 */

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit WATER_BASE;
inherit SEA_CAVE_BASE;

void
create_sea_cave_room()
{
    set_short("An underground tunnel");
    set_long(short() + ". It seems deeper here. The current isn't as " +
        "strong and the water gently flows to the east. The air is " +
        "fresher and not as clammy.\n");

    remove_prop(ROOM_I_LIGHT);
    set_add_stream();
    reset_room();

// sets drinking functions
    set_drink_from( ({ "river", "stream"}) );   
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);  

    add_exit(FOREST_DIR + "river04", "north",0,3);
    add_exit(FOREST_DIR + "river06", "east",0,3);
}

public void
init()
{
    ::init();
    init_drink();
}
