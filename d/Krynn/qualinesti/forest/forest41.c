/* forest41.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;

void
reset_qualinesti_room()
{
    
}

void
create_forest()
{
    add_my_desc("\n");
    
    OUTSIDE;

    add_exit(FDIR + "forest40.c", "west", 0, 2);
    add_exit(FDIR + "forest42.c", "east", 0, 2);
    add_exit(FDIR + "forest44.c", "southwest", 0, 2);
    add_exit(FDIR + "forest45.c", "south", 0, 2);
    add_exit(FDIR + "path9.c", "northeast", 0, 2);

    reset_qualinesti_room();
    
}
