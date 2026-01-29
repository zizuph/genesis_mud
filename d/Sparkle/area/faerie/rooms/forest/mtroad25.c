/*
 * The mountain road between Sparkle and Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit FOREST_BASE;

string extra_line = " ";

void
create_forest_room()
{
    set_short("A track in the forest");
    set_long(mt_desc3(extra_line));

    set_add_valley();
    add_std_herbs("forest");
    reset_room();
    set_conifer_trees();
    set_add_forest_debris();

    add_exit(FOREST_DIR + "mtroad24", "northwest");
    add_exit(GO_DIR + "road01", "southeast");
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
