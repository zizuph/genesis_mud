/* forest36.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;
object animal, elf;

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
    
}

void
create_forest()
{
    add_my_desc("\n");
    
    OUTSIDE;

    add_exit(FDIR + "forest33.c", "northwest", 0, 2);
    add_exit(FDIR + "forest34.c", "north", 0, 2);
    add_exit(FDIR + "forest35.c", "west", 0, 2);
    add_exit(FDIR + "forest37.c", "east", 0, 2);
    add_exit(FDIR + "path8.c", "northeast", 0, 2);

    reset_qualinesti_room();

}
