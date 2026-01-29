/*
 * Caves beneath the Mountains of Mirkwood
 * Varian - February 2015
 */

#pragma save_binary
#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <files.h>
#include <composite.h>
#include <filter_funs.h>

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "caves/base";

void
create_mirkwood_cave_room()
{

    add_long("You notice that against the east wall of this cave, the webs " +
        "have piled up to form a rather intimidating nest. \n\n", LIGHT_ALL);

    add_item_light(({"nest", "spider nest", "large nest"}),
        "The spider webs seem to clump up into a massive hive against " +
        "the east wall in this cave, creating what appears to be a rather " +
        "impressive looking spider nest. By intention or accident, it " +
        "appears that you have reached the very heart of this spider " +
        "lair, and you are getting a bad feeling about this.\n", LIGHT_ALL);

    add_exit(MIRKWOOD_CENTRAL_FOREST_DIR + "caves/cave15", "northwest", webs);

}
