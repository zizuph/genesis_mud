/* forest47.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;
object animal, animal2, animal3;
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
    if ( !animal3 )
    {
        animal3 = random_animal();
        animal3->move(TO, 1);
    }
    
}

void
create_forest()
{
    add_my_desc("\n");
    
    OUTSIDE;

    add_exit(FDIR + "forest46.c", "west", 0, 2);
    add_exit(FDIR + "forest48.c", "east", 0, 2);
    add_exit(FDIR + "forest50.c", "southwest", 0, 2);
    add_exit(FDIR + "forest51.c", "south", 0, 2);
    add_exit(FDIR + "forest52.c", "southeast", 0, 2); 
    add_exit(FDIR + "path10.c", "northwest", 0, 2); 
    add_exit(FDIR + "path11.c", "north", 0, 2); 
    add_exit(FDIR + "path12.c", "northeast", 0, 2); 
        
    reset_qualinesti_room();

}
