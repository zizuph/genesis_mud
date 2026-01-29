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
    set_long(short() + ". It is dark and dank in here from the constant moisture. The shallow stream flows past. Pebbles and rocks are scattered on the ground, making it difficult to move .\n");

    remove_prop(ROOM_I_LIGHT);
    set_add_stream();
    reset_room();

// sets drinking functions
    set_drink_from( ({ "river", "stream"}) );   
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);  

    add_exit(FOREST_DIR + "river03", "east",0,3);
    add_exit(FOREST_DIR + "river01", "northwest",0,3);
}

public void
init()
{
    ::init();
    init_drink();
}
