/*
 * The forest road of Faerie
 * By Finwe, August 2004
 */
 
#include "defs.h"
 
inherit FOREST_BASE;

string extra_line = "To the west is a small orchard. It looks well tended " +
        "and seems out of place in the forest. The road runs northeast " +
        "and southwest.";

void
create_forest_room()
{
    set_short("Along the Trade Road");
    set_long(forest_desc1(extra_line)); 
    add_std_herbs("forest");
    reset_room();
    set_add_oak_trees();

    add_exit(FOREST_DIR + "ctroad01",  "northeast");
    add_exit(GO_DIR + "road07n2", "southwest");

    reset_room();

}

/*
 * Function name:	init
 * Description	:	
 */
public void
init()
{
    ::init();

}
void
reset_room()
{
}
