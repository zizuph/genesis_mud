/* forest34.c
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

    add_exit(FDIR + "forest33.c", "west", 0, 2);
    add_exit(FDIR + "forest35.c", "southwest", 0, 2);
    add_exit(FDIR + "forest36.c", "south", 0, 2);
    add_exit(FDIR + "forest37.c", "southeast", 0, 2);
    add_exit(FDIR + "path6.c", "northwest", 0, 2);
    add_exit(FDIR + "path7.c", "north", 0, 2);
    add_exit(FDIR + "path8.c", "east", 0, 2);
    
    reset_qualinesti_room();

}
