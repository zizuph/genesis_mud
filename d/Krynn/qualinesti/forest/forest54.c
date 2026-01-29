/* forest54.c
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

    add_exit(FDIR + "forest25.c", "northeast", 0, 2);
    add_exit(FDIR + "forest49.c", "northwest", 0, 2);
    add_exit(FDIR + "forest53.c", "west", 0, 2);
    add_exit(FDIR + "path14.c", "north", 0, 2);
    add_exit(FDIR + "nentrance.c", "east", 0, 2); 
    
    reset_qualinesti_room();

}
