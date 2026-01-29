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

    add_exit(MIRKWOOD_CENTRAL_FOREST_DIR + "caves/cave7", "southeast", webs);
    add_exit(MIRKWOOD_CENTRAL_FOREST_DIR + "caves/cave5", "north", webs);

}
