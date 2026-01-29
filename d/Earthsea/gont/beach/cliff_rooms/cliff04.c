/*
 * Cliff on Gont beach
 * By Finwe
 * May 1997
 */

#pragma strict_types
#pragma no_clone

#include "default.h"
#include <stdproperties.h>

inherit CLIFFS_ROOM;

public void
create_cliffs()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("The side of a cliff");
    set_long( "The path levels out here, affording an excellent " +
      "view of the ocean, like a lookout point for those " +
      "looking out to sea. Unlike the rest of the cliffs, the " +
      "rock is smooth here. The sea can be heard crashing " +
      "below against the sides of the cliffs.\n");

    add_exit("cliff05", "east");
    add_exit("cliff03", "northeast");
}
