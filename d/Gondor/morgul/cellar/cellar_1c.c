/*
 * /d/Gondor/morgul/cellar/cellar_1c.c
 * The central room on the first floor of dungeons below the Morgul Tower
 *
 * Olorin, 12-jul-1994
 */
inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

void
create_morgul_cellar_room()
{
    set_level(1);
    set_room_type("dark dungeon");
    set_extra_long("There is a spiral staircase running up here. " +
        "A dark passage opens to the east, and archways lead " +
        "north and south.");

    add_walls();
    add_floor();
    add_passage("east");
    add_archways("north", "south");
    add_item(({"staircase","stairs","spiral staircase","stairway"}), BSN(
        "The spiral staircase disappears into the ceiling here, leading up " +
        "to the ground level of the Tower."));
    add_item(({"ceiling", "roof"}), BSN(
        "The vaulted ceiling rises high above you. The stairway disappears " +
        "into it."));

    add_exit(CELLAR_DIR + "dung_1wn", "north", 0, 1);
    add_exit(CELLAR_DIR + "pass_1w1", "east",  0, 1);
    add_exit(CELLAR_DIR + "dung_1ws", "south", 0, 1);
    add_exit(TOWER_DIR  + "tower_0c", "up",    0, 4);

    (CELLAR_DIR + "pass_1e1")->load_me();
}

