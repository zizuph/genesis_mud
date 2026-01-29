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

string extra_line = "The road is well used by travellers and runs alongside " +
    "an orchard. The road leads into a village to the southwest. It also " +
    "winds its way between the tall oaks in the forest as it runs northeast.";
 
void
create_forest_room()
{
    set_short("A forest road outside of Green Oaks");
    set_long(forest_desc2(extra_line)); 

    add_std_herbs("forest");
    
    reset_room();
    set_add_oak_trees();
    set_add_orchard();
   
    add_exit(GO_DIR + "road07n2", "northeast");
    add_exit(GO_DIR + "road07", "southwest");


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
