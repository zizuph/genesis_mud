/*
 * THIS ROOM POINTS TO THE START LOCATIONS
 * The Trade Road of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit FOREST_BASE;

string extra_line = "";

void
create_forest_room()
{
    FIXEUID;
    set_short("Deep in a dark forest");
    set_long(s_desc_sky_outside_sky() + "The forest is thick with " +
        "tall trees but thins to the north. The trees reach to the sky. " +
        "Mists flow from the north, creating a serene feeling.\n");
    add_item(({"mists", "mist"}),
        "They are light and gently move around the forest.\n");
    add_std_herbs("forest");

    add_exit("/d/Genesis/start/elf/room/begin", "north");
    add_exit(FOREST_DIR + "road03", "south");

}

public void
init()
{
    ::init();

}
void
reset_room()
{
}

