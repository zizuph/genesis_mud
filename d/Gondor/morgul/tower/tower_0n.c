/*
 * /d/Gondor/morgul/tower/tower_0n.c
 * The north room on the ground floor of the Morgul Tower
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
    set_level(0);
    set_room_type("large hall");
    set_extra_long("This is the north end of the hall. A row of mighty " +
        "pillars to the southeast divides it from the central part. " +
        "To the north, a small passage is leading out of the tower.");

    add_item(({"hall"}), BSN(
        "The halls extends to the southwest along a row of pillars. " +
        "Beyond the pillars lies the central part of the hall, which " +
        "you can reach by walking either south or east."));
    add_item(({"columns", "pillar", "pillars", "row", "rows", "row of pillars", "rows of pillars"}), BSN(
        "A rows of pillars runs diagonally across the large hall from " +
        "the northeast to the southwest. They divide this part of the hall " +
        "from the rest. Each of the pillars is several yards thick and made of " +
        "black stone. One of the pillars is slightly thicker than the others, " +
        "and a spiral stairway is winding its way up round that pillar."));
    add_item(({"spiral stairway","stairs","stairway"}), BSN(
        "A spiral stairway is winding its way up towards the next level of the " +
        "tower around a slightly thicker pillar. From this side, there is no " +
        "way to step onto the stairs, since they begin on the other side " +
        "of the pillar."));

    NO_ROOF
    FLOOR
    WALLS

    add_exit(MORGUL_DIR + "city/square", "north",     0, 1);
    add_exit(TOWER_DIR  + "tower_0ne",   "east",      0, 1);
    add_exit(TOWER_DIR  + "tower_0c",    "south",     0, 1);
    add_exit(TOWER_DIR  + "tower_0w",    "southwest", 0, 1);
}

