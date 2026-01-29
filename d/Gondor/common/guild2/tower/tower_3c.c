/*
 * /d/Gondor/morgul/tower/tower_3c.c
 * The central room on the third floor of the Morgul Tower
 *
 * Olorin, 10-jan-1994
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

void 
create_morgul_tower_room()
{
    set_level(3);
    set_room_type("staircase");
    set_extra_long("There is a spiral staircase running up and " +
        "down here, and dark passages leading into gloomy rooms " +
        "are to the north and south.");

    add_walls();
    add_no_roof();
    add_floor();
    add_staircase();

    add_exit(MAGES_DIR  + "post",           "north", 0, 1);
    add_exit(MAGES_DIR  + "tower/tower_3e", "east",  0, 1);
    add_exit(MAGES_DIR  + "boardroom",      "south", 0, 1);
    add_exit(MAGES_DIR  + "tower/tower_3w", "west",  0, 1);
    add_exit(MAGES_DIR  + "tower/tower_4c", "up",    0, 4);
    add_exit(TOWER_DIR  + "tower_2c",       "down",  0, 2);
}

