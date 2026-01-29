/*
 * Cliff on Gont beach
 * By Finwe
 * May 1997
 */

#pragma strict_types
#pragma no_clone

#include "default.h"
#include <macros.h>
#include <stdproperties.h>

inherit CLIFFS_ROOM;

public void
create_cliffs()
{   
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("The side of a cliff");
    set_long( "You are at the southwest end of the cliffs. They " +
        "are tall and imposing as they rise skyward out of the " +
        "water. Formed of limestone, the cliffs look like " +
        "columns that were chiseled out of the earth itself by " +
        "the hands of some ancient god. Scarred by the ocean " +
        "wind, numerous ledges and holes have been dug into the " +
        "side. You notice a small pathway leading up alongside " +
        "the cliffs.\n");

    add_exit(BEACH_DIR + "beach03", "down", "@@down_cliff@@");
    add_exit("cliff04", "west");
}

public int
down_cliff()
{
    write("You follow the path out of the cliffs and down to the beach.\n");
    say(QCTNAME(this_player()) + " goes down to the beach.\n");
}
