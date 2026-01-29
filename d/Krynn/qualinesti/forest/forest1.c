/* forest1.c
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

    add_exit(FDIR + "hentrance.c", "west", 0, 2);
    add_exit(FDIR + "forest0.c", "southwest", 0, 2);
    add_exit(FDIR + "forest2.c", "east", 0, 2);
    add_exit(FDIR + "path1.c", "south", 0, 2);
    add_exit(FDIR + "path2.c", "southeast", 0, 2);

    set_up_herbs( ({ GOHERB + "attanar", GOHERB + "suranie" }), 
        ({ "growth", "forest", "herb growth", }), 3);

    reset_qualinesti_room();
}
