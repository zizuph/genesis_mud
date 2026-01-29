/* forest29.c
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

    add_exit(FDIR + "forest6.c", "northeast", 0, 2);
    add_exit(FDIR + "forest28.c", "west", 0, 2);
    add_exit(FDIR + "forest30.c", "southwest", 0, 2);
    add_exit(FDIR + "forest31.c", "south", 0, 2);
    add_exit(FDIR + "forest32.c", "southeast", 0, 2);
    add_exit(FDIR + "path3.c", "northwest", 0, 2);
    add_exit(FDIR + "path4.c", "north", 0, 2);
    add_exit(FDIR + "path5.c", "east", 0, 2);

    reset_qualinesti_room();

}
