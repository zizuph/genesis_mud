/* camp4.c
 * An elven encampment in the Qualinesti forest.
 *
 * Blizzard, 01/2003
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit CAMPBASE;

#define JOINROOM   "/d/Ansalon/guild/elven_archers/joinroom"

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
    add_my_desc("You see a big tree to the north. The center of the " +
    	"camp is to the south.\n");
    
    add_item(({"tree", "big tree", "oak", "big oak"}),
        "There is a big tree north of here. It stretches its " +
    	"branches high and wide.\n");
    
    OUTSIDE;
    
    add_exit(CDIR + "camp2.c", "southwest", 0, 1);    
    add_exit(CDIR + "camp3.c", "west", 0, 1);
    add_exit(CDIR + "camp5.c", "east", 0, 1);
    add_exit(CDIR + "camp6.c", "southeast", 0, 1);
    add_exit(CDIR + "camp10.c", "south", 0, 1);
    add_exit(CDIR + "camp11.c", "north", 0, 1);

 /* Exit to the Elven Archers join room */
    add_exit(JOINROOM, "northwest", 0, 1);
    
    reset_qualinesti_room();
    
}

    