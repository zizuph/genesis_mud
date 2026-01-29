/* forest9.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;

object animal;

void
reset_qualinesti_room()
{

    if ( !animal )
    {
        animal = random_animal();
        animal->move(TO, 1);
    }
    
}

void
create_forest()
{
    add_my_desc("\n");
    
    OUTSIDE;

    add_exit(FDIR + "forest8.c", "west", 0, 2);
    add_exit(FDIR + "forest10.c", "east", 0, 2);
    add_exit(FDIR + "forest13.c", "southeast", 0, 2);
    add_exit(FDIR + "path7.c", "southwest", 0, 2);

    set_up_herbs( ({ GOHERB + "attanar", GOHERB + "suranie" }), 
        ({ "growth", "forest", "herb growth", }), 3);

    reset_qualinesti_room();

}
