/* forest48.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;

object elf1, animal;

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
}

void
create_forest()
{
    add_my_desc("\n");
    
    OUTSIDE;

    add_exit(FDIR + "forest47.c", "west", 0, 2);
    add_exit(FDIR + "forest49.c", "east", 0, 2);
    add_exit(FDIR + "forest51.c", "southwest", 0, 2);
    add_exit(FDIR + "forest52.c", "south", 0, 2);
    add_exit(FDIR + "forest53.c", "southeast", 0, 2); 
    add_exit(FDIR + "path11.c", "northwest", 0, 2); 
    add_exit(FDIR + "path12.c", "north", 0, 2); 
    add_exit(FDIR + "path13.c", "northeast", 0, 2); 
            
    reset_qualinesti_room();

}
