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
    set_long(short() + ". The cold water rushes past as it cuts through the rock. The air is heavy with water, which runs down the walls and drips from above. The dark passage makes it difficult to move here.\n");

    remove_prop(ROOM_I_LIGHT);
    set_add_stream();
    reset_room();

// sets drinking functions
    set_drink_from( ({ "river", "stream"}) );   
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);  

    add_exit(FOREST_DIR + "river04", "east",0,3);
    add_exit(FOREST_DIR + "river02", "west",0,3);
}

public void
init()
{
    ::init();
    init_drink();
}
