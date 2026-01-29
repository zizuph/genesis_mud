/* forest46.c
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

    add_exit(FDIR + "forest42.c", "northwest", 0, 2);
    add_exit(FDIR + "forest47.c", "east", 0, 2);
    add_exit(FDIR + "forest50.c", "south", 0, 2);
    add_exit(FDIR + "forest51.c", "southeast", 0, 2);
    add_exit(FDIR + "path10.c", "north", 0, 2);
    add_exit(FDIR + "path11.c", "northeast", 0, 2);
  
    reset_qualinesti_room();

}
