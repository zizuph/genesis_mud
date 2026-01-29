/* forest44.c
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
//    set_animal();
    
}

void
create_forest()
{
    add_my_desc("\n");
    
    OUTSIDE;

    add_exit(FDIR + "forest39.c", "northwest", 0, 2);
    add_exit(FDIR + "forest40.c", "north", 0, 2);
    add_exit(FDIR + "forest41.c", "northeast", 0, 2);
    add_exit(FDIR + "forest43.c", "west", 0, 2);
    add_exit(FDIR + "forest45.c", "east", 0, 2);
    
    reset_qualinesti_room();

}
