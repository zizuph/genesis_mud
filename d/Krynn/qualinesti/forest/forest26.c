/* forest26.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;

object animal, animal2;

void
reset_qualinesti_room()
{

    if ( !animal )
    {
        animal = random_animal();
        animal->move(TO, 1);

    }

    if ( !animal2 )
    {
        animal2 = random_animal();
        animal2->move(TO, 1);

    }

}

void
create_forest()
{
    add_my_desc("\n");
    
    OUTSIDE;

    add_exit(FDIR + "forest0.c", "northwest", 0, 2);
    add_exit(FDIR + "forest27.c", "east", 0, 2);
    add_exit(FDIR + "path1.c", "north", 0, 2);
    add_exit(FDIR + "path2.c", "northeast", 0, 2);

    reset_qualinesti_room();

}
