/*
 * The Trade Road of Faerie
 * By Finwe, August 2004
 */
 
#include "defs.h"
 
inherit FOREST_BASE;

string extra_line = "Oak trees grow here, too. They aren't as numerous as " +
    "the fir trees, but grow in small groups among the fir trees.";
 
void
create_forest_room()
{
    FIXEUID;
    set_short("Along the Central Trade Road");
    set_long(forest_desc4(extra_line)); 
    add_std_herbs("forest");
    reset_room();

    add_exit(FOREST_DIR + "road02",  "north");
    add_exit(GO_DIR + "road07n3", "southwest");

}
void
reset_room()
{
}
