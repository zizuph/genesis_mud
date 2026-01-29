/*
 * A sea cave tunnel in Faerie
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
    set_short("A tunnel in a sea cave");
    set_long(short() + ". The tunnel is long and dark looking. The ground " +
        "is uneven but worn from constant use. Tunnels lead north, east, " +
        "and west.\n");

    remove_prop(ROOM_I_LIGHT);
    set_cave_room();
    reset_room();

    add_exit(FOREST_DIR + "seacave03n1", "north");
    add_exit(FOREST_DIR + "seacave02", "east");
    add_exit(FOREST_DIR + "seacave04", "west");
}

public void
init()
{
    ::init();
}
