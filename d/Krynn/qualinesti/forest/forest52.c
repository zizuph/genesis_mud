/* forest52.c
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

    add_exit(FDIR + "forest47.c", "northwest", 0, 2);
    add_exit(FDIR + "forest48.c", "north", 0, 2);
    add_exit(FDIR + "forest49.c", "northeast", 0, 2);
    add_exit(FDIR + "forest51.c", "west", 0, 2);
    add_exit(FDIR + "forest53.c", "east", 0, 2); 
    
    reset_qualinesti_room();

}
