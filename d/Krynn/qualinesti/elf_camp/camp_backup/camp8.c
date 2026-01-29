/* camp8.c
 * An elven encampment in the Qualinesti forest.
 *
 * Blizzard, 01/2003
 */

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit CAMPBASE;

object elf1, elf2, elf3;

void
reset_qualinesti_room()
{
    int i = random(10);

  /* There is 50% chance for setting 3 elves and 50% for setting 2 elves. */
    
    if (!elf1)
    {
        elf1 = clone_object(STD + "elf_base");
        elf1->move(TO);
    }
    if (!elf2)
    {
        elf2 = clone_object(STD + "elf_base");
        elf2->move(TO);
    }
    if ( i > 4 )
    {
        if (!elf3)
        {
            elf3 = clone_object(STD + "elf_base");
            elf3->move(TO);
        }
    }

}

void
create_camp()
{
    add_my_desc("The center of the camp is to the north.\n");
    
    OUTSIDE;
    
    add_exit(CDIR + "camp2.c", "northwest", 0, 1);
    add_exit(CDIR + "camp6.c", "northeast", 0, 1);
    add_exit(CDIR + "camp7.c", "east", 0, 1);
    add_exit(CDIR + "camp9.c", "west", 0, 1);
    add_exit(CDIR + "camp10.c", "north", 0, 1);
    
    reset_qualinesti_room();
    
}

    