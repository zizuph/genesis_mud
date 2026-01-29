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

inherit ROCKY;

public void
create_beach()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    add_my_desc( "Rocks and boulders that have fallen from the " +
        "cliffs above are scattered around the beach. Birds " +
        "scream overhead as they fly around the cliffs. A trail " +
        "leads up into the cliffs.\n");
 
    add_item(({"birds", "seabirds"}),
        "You can see seagulls, terns, puffins, and other " +
        "seabirds flying around the top of the cliffs.\n");
    add_item(({"seagulls", "gulls", "terns", "puffins"}),
        "They swoop around the cliffs as they head out to sea " +
        "and back from fishing.\n");
    add_item (({"beach", "rocky beach"}),
        "The beach is covered with broken boulders from the " +
        "hills and from rocks that have come in with the tide.\n");
    add_item(({"path", "trail"}),
        "The trail winds itself up into the dark cliffs. It is " +
        "well worn from constant travel.\n");
    add_item(({"cliff", "cliffs"}),
        "They are imposing as they rise up from the depths " +
        "of the sea.\n");
 
    add_exit(CLIFF_DIR + "cliff01", "up", "@@up_cliff@@");
    add_exit("beach01", "northwest");
}
 
public int
up_cliff()
{
    write("You follow the path up into the cliffs.\n");
    say(QCTNAME(this_player()) + " climbs up into the cliffs.\n");
    return 0;
}
