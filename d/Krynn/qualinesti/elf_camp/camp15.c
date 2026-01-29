/* camp15.c
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
    if (!elf3)
    {
        elf3 = clone_object(STD + "elf_base");
        elf3->move(TO);
    }
}


void
create_camp()
{
    add_my_desc("The main camp is towards the south.\n");
    
    OUTSIDE;
    
    add_exit(CDIR + "camp5.c", "south", 0, 1);
   
    reset_qualinesti_room();
    
}

    