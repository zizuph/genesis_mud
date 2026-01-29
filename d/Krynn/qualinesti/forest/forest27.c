/* forest27.c
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

    add_exit(FDIR + "forest26.c", "west", 0, 2);
    add_exit(FDIR + "forest28.c", "east", 0, 2);
    add_exit(FDIR + "forest30.c", "southeast", 0, 2);
    add_exit(FDIR + "path1.c", "northwest", 0, 2);
    add_exit(FDIR + "path2.c", "north", 0, 2);
    add_exit(FDIR + "path3.c", "northeast", 0, 2);
    
    reset_qualinesti_room();

}
