/* path1.c
 * The path leading to the elf camp.
 *
 * Blizzard, 01/2003
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;

object animal;

string my_desc();

void
reset_qualinesti_room()
{
    if ( !animal )
    {
        animal = random_animal();
        animal->move(TO, 1);
    }
    
}
    
void
create_forest()
{
    add_my_desc("@@my_desc");
	
    add_item("trail", 
    	"A barely noticable animal trail, leading through the forest.\n");	
	
    OUTSIDE;
	
    add_exit(FDIR + "hentrance.c", "northwest", 0, 2);
    add_exit(FDIR + "path2.c", "east", 0, 2);
    add_exit(FDIR + "forest0.c", "west", 0, 2);
    add_exit(FDIR + "forest1.c", "north", 0, 2);
    add_exit(FDIR + "forest2.c", "northeast", 0, 2);
    add_exit(FDIR + "forest26.c", "south", 0, 2);
    add_exit(FDIR + "forest27.c", "southeast", 0, 2);
    
    reset_qualinesti_room();
}

string
my_desc()
{	    
    
    if (skill_check(TP))
    {
    	return "\nYour skilled eye notices something, what might be an " +
    	    "animal trail leading to the east. It also goes northwest, " +
    	    "back towards civilization.\n";
    }
    
    return "\n";
}

	    