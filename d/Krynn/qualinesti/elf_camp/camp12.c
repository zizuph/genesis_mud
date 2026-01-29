/* camp12.c
 * An elven encampment in the Qualinesti forest.
 * There is an oak with a sharpshooter sitting on it, to the east of 
 * this room.
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
    add_my_desc("There is a small path leading east through the branches. " +
        "You see also a big tree standing there.\n");
	
    add_item(({"tree", "oak", "big tree", "big oak"}),
	"It is a very old oak. It is quite high and its branches " +
	"are stretched wide, what makes it a nice place for a lookout.\n");
    add_item("path", 
        "There is a small path worn through the branches leading " +
        "to the east.\n");
        
    add_cmd_item(({"oak", "tree",  "big oak", "big tree"}), "climb", 
	"You should go a bit east first.\n");
			
    OUTSIDE;
	
    add_exit(CDIR + "ambush2.c", "east", 0, 2);
    add_exit(CDIR + "camp7.c", "west");
	
    reset_qualinesti_room();
}

       

