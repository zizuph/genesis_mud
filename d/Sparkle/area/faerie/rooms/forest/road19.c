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
    set_short("Along the Northern Trade Road");
    set_long(forest_desc2(extra_line));
    add_std_herbs("forest");

    add_exit(FOREST_DIR + "road20", "north");
    add_exit(FOREST_DIR + "road18", "south");
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
