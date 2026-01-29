/* path14.c
 * The path leading to the elf camp.
 *
 * Blizzard, 01/2003
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;

string my_desc();

void
reset_qualinesti_room()
{
    
}
    
void
create_forest()
{
    add_my_desc("@@my_desc");
	
    add_item("trail", 
    	"A barely noticable animal trail, leading through the forest.\n");	
	
    OUTSIDE;
	
    add_exit(FDIR + "path13.c", "northwest", 0, 2);
    add_exit(FDIR + "nentrance.c", "southeast", 0, 2);
    add_exit(FDIR + "forest23.c", "north", 0, 2);
    add_exit(FDIR + "forest24.c", "northeast", 0, 2);
    add_exit(FDIR + "forest25.c", "east", 0, 2);
    add_exit(FDIR + "forest49.c", "west", 0, 2);
    add_exit(FDIR + "forest53.c", "southwest", 0, 2);
    add_exit(FDIR + "forest54.c", "south", 0, 2); 
    
    reset_qualinesti_room();
}

string
my_desc()
{	    
    
    if (skill_check(TP))
    {
    	return "\nYour skilled eye notices something, what might be an " +
    	    "animal trail leading to the northwest. It also goes southeast, " +
    	    "back towards civilization.\n";
    }
    
    return "\n";
}

	    