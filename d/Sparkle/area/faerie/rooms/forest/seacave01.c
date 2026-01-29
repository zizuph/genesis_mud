/*
 * A sea cave tunnel in Faerie
 * By Finwe, August 2004
 */

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit SEA_CAVE_BASE;

void
create_sea_cave_room()
{
    set_short("An opening of a cave");
    set_long(short() + ". Light filters in from the outside, illuminating " +
        "the cave. It goes deeper into the earth to the southwest and " +
        "disappears. Rocks and pebbles lay strewn around the ground. " +
        "They were probably washed in from the sea.\n");

    set_cave_room();
    reset_room();

    add_exit(FOREST_DIR + "beach04n", "out");
    add_exit(FOREST_DIR + "seacave02", "southwest");
}

public void
init()
{
    ::init();

}
