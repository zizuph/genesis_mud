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
    set_long(forest_desc2(extra_line));
    add_std_herbs("forest");

    add_exit(FOREST_DIR + "road04", "north");
    add_exit(FOREST_DIR + "road02", "south");
    add_exit(FOREST_DIR + "road05", "northeast");
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
