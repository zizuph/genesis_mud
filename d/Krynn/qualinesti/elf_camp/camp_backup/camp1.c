/* camp1.c
 * An elven encampment in the Qualinesti forest.
 * You see an oak with a sharpshooter sitting on it, to the west of here.
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
    add_my_desc("You see a big oak to the west of here.\n");
	
    add_item(({"oak", "tree", "big tree", "big oak"}),
	"That tree is much bigger than other ones growing in this area " +
	"and you think it would make an excellent place for a lookout.\n");
    add_cmd_item(({"oak", "big oak", "tree", "big tree"}), "climb", 
	"Don't you think it would be better to go a bit west first?\n");
		
    OUTSIDE;
	
    add_exit(CDIR + "ambush1.c", "west", 0, 2);
    add_exit(CDIR + "camp2.c", "east", 0, 2);

    reset_qualinesti_room();	
}

       

