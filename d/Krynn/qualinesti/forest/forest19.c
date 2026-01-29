/* forest19.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;
object animal, animal2, elf;

void
reset_qualinesti_room()
{
    if ( !elf )
    {
        elf = clone_object(STD + "scout_base");
        elf->move(TO, 1);
        elf->command("hide");
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

    add_exit(FDIR + "forest16.c", "northwest", 0, 2);
    add_exit(FDIR + "forest18.c", "west", 0, 2);
    add_exit(FDIR + "forest20.c", "southeast", 0, 2);
    add_exit(FDIR + "path9.c", "southwest", 0, 2);

    reset_qualinesti_room();

}
