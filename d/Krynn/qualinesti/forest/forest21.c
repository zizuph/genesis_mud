/* forest21.c
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

    add_exit(FDIR + "forest20.c", "west", 0, 2);
    add_exit(FDIR + "forest22.c", "east", 0, 2);
    add_exit(FDIR + "path11.c", "southwest", 0, 2);
    add_exit(FDIR + "path12.c", "south", 0, 2);
    add_exit(FDIR + "path13.c", "southeast", 0, 2);

    reset_qualinesti_room();

}
