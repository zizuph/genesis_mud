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
    set_room_type("dark passage");
    set_extra_long("To the east, the passage opens onto a hall, while it " +
        "leads out of the tower in the other direction.");

    WALLS
    ROOF
    FLOOR

    add_exit(TOWER_DIR  + "tower_1c",         "east",  0, 1);

    clone_object(TOWER_DIR + "doors/westwall_in")->move(TO);
}

