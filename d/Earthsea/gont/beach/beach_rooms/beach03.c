/*
 * Beach in Gont
 * By Finwe
 * April 1997
 */

#pragma strict_types 
#pragma no_clone

#include "default.h"
#include <stdproperties.h>
#include <macros.h>

inherit SANDY;

public void
create_beach()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");

    add_my_desc( "Rocks and boulders that have fallen from the " +
        "cliffs above are scattered around the beach. A trail " +
        "leads up into the cliffs.\n");

    add_item (({"beach", "sandy beach"}),
        "The beach is warm yet rough. You feel the crunch of " +
        "broken rocks and the scratching of sand under your feet.\n");
    add_item(({"path", "trail"}),
        "The trail winds itself up into the dark cliffs. It is " +
        "well worn from constant travel.\n");
    add_item(({"cliff", "cliffs"}),
        "They are imposing as they rise up from the depths " +
        "of the sea.\n");

    add_exit(CLIFF_DIR + "cliff05", "up", "@@up_cliff@@");
    add_exit("beach04", "northeast");
}
 
public int
up_cliff()
{
    write ("You follow the path up into the cliffs.\n");
    say(QCTNAME(this_player()) + " climbs up into the cliffs.\n");
    return 0;
}
