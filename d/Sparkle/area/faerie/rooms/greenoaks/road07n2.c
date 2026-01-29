/*
 * Outdoor room in Green Oaks
 * By Finwe, August 2004
 */
 
#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit FOREST_BASE;

string extra_line = "To the west is a small orchard. It looks well tended " +
        "and seems out of place in the forest. The road runs northeast " +
        "and southwest.";
 
void
create_forest_room()
{
    set_short("Along the Trade Road");
    set_long(forest_desc2(extra_line)); 
    add_std_herbs("forest");
    reset_room();
    set_add_oak_trees();
    set_add_orchard();
        
   
    add_exit(GO_DIR + "road07n3", "northeast");
    add_exit(GO_DIR + "road07n1", "southwest");

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
