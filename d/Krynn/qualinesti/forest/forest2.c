/* forest2.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;

object elf1, animal, animal2;

void
reset_qualinesti_room()
{ 
    if (!elf1)
    {
        elf1 = clone_object(STD + "scout_base");
        elf1->move(TO);
        elf1->command("hide");
    }
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

    add_exit(FDIR + "forest1.c", "west", 0, 2);
    add_exit(FDIR + "forest3.c", "east", 0, 2);
    add_exit(FDIR + "path1.c", "southwest", 0, 2);
    add_exit(FDIR + "path2.c", "south", 0, 2);
    add_exit(FDIR + "path3.c", "southeast", 0, 2);

    reset_qualinesti_room();
}
