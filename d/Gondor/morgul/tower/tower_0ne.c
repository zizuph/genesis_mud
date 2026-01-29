/*
 * /d/Gondor/morgul/tower/tower_0c.c
 * The northeast room on the ground floor of the Morgul Tower
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
    set_extra_long("This is the northeast end of the hall, close to the " +
        "main entrance. From here, two rows of mighty pillars run through " +
        "the hall as far as one can see. ");

    add_item(({"hall"}), BSN(
        "The halls extends to the southwest as far as you can see by " +
        "the shine of your light source. Two rows of mighty pillars " +
        "divide the hall into three parts. Right now you are in the " +
        "central part between the two rows. Walking through the pillars " +
        "to the west, you can reach the northwestern part, walking south " +
        "the southeastern part."));
    add_item(({"columns", "pillar", "pillars", "row", "rows", "row of pillars", "rows of pillars"}), BSN(
        "The two rows of pillars run diagonally across the large hall from " +
        "the northeast to the southwest. They divide the hall into three " +
        "parts. Each of the pillars is several yards thick and made of " +
        "black stone."));

    NO_ROOF
    FLOOR
    WALLS

    add_exit(TOWER_DIR  + "tower_entrance", "northeast", 0, 1);
    add_exit(TOWER_DIR  + "tower_0e",       "south",     0, 1);
    add_exit(TOWER_DIR  + "tower_0c",       "southwest", 0, 1);
    add_exit(TOWER_DIR  + "tower_0n",       "west",      0, 1);
}

