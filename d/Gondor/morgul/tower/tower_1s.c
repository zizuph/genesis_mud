/*
 * /d/Gondor/morgul/tower/tower_1s.c
 * The south room on the first floor of the Morgul Tower
 *
 * Olorin, 10-jan-1994
 */
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"

void 
create_morgul_tower_room()
{
    set_level(1);
    set_room_type("dark passage");
    set_extra_long("To the north, the passage opens onto a hall, while it " +
        "leads out of the tower in the other direction.");

    add_walls();
    add_roof();
    add_floor();

    add_exit(TOWER_DIR  + "tower_1c",         "north", 0, 1);

    clone_object(MORGUL_DIR + "tower/doors/southwall_in")->move(TO);

    // This is necessary to preserve the locked/unlocked status of the door.
    add_prop(ROOM_I_NO_CLEANUP, 1);
}
