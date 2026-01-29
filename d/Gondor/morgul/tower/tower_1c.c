/*
 * /d/Gondor/morgul/tower/tower_1c.c
 * The central room on the first floor of the Morgul Tower
 *
 * Olorin, 10-jan-1994
 */
inherit "/d/Gondor/morgul/tower/tower.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"

void create_morgul_tower_room()
{
    set_level(1);
    set_room_type("hall");
    set_extra_long("There is a spiral staircase running up and " +
        "down here, and dark passages lead south and west.");

    WALLS
    NO_ROOF
    FLOOR
    add_item(({"staircase","stairs","spiral staircase","stairway"}), BSN(
        "The spiral staircase disappears in the floor here, leading down " +
        "to the ground level of the Tower. Upwards it soon disappears " +
        "from view, hidden in the unfathomable darkness above."));

    add_exit(TOWER_DIR  + "warden_room", "east",  0, 1);
    add_exit(TOWER_DIR  + "tower_1s",    "south", 0, 1);
    add_exit(TOWER_DIR  + "tower_1w",    "west",  0, 1);
    add_exit(TOWER_DIR  + "tower_2c",    "up",    0, 4);
    add_exit(TOWER_DIR  + "tower_0c",    "down",  0, 2);
}

