/* forest0.c
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

    add_exit(FDIR + "hentrance.c", "north", 0, 2);
    add_exit(FDIR + "forest1.c", "northeast", 0, 2);
    add_exit(FDIR + "forest26.c", "southeast", 0, 2);
    add_exit(FDIR + "path1.c", "east", 0, 2);

    reset_qualinesti_room();
}
