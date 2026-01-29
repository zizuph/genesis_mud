/*
 * The Trade Road of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit FOREST_BASE;

string extra_line = "The tree is tall with branches that hang over the " +
    "road. They block your view below but look large enough so that " +
    "you can climb further up into the tree. ";

void
create_forest_room()
{
    FIXEUID;
    set_short("Up in a tree above the road");
    set_long(short() + ". " + s_desc_sky_outside_sky() + extra_line + 
        "Bees buzz around the top most branches.\n");
    add_std_herbs("forest");
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
