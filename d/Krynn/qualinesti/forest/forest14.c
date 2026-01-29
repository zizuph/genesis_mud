/* forest14.c
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

    add_exit(FDIR + "forest10.c", "northwest", 0, 2);
    add_exit(FDIR + "forest11.c", "north", 0, 2);
    add_exit(FDIR + "forest12.c", "northeast", 0, 2);
    add_exit(FDIR + "forest13.c", "west", 0, 2);
    add_exit(FDIR + "forest15.c", "east", 0, 2);
    add_exit(FDIR + "forest17.c", "southeast", 0, 2);

    reset_qualinesti_room();

}
