/*
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
    set_short("Along the Central Trade Road");
    set_long(forest_desc1(extra_line));
    add_std_herbs("forest");

    add_exit(FOREST_DIR + "road12",     "west");
    add_exit(GRAVE1_DIR + "gr1_03", "northeast");
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
