/* path8.c
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
	
    add_exit(FDIR + "path7.c", "northwest", 0, 2);
    add_exit(CDIR + "ambush1.c", "east", 0, 2);
    add_exit(FDIR + "forest13.c", "northeast", 0, 2);
    add_exit(FDIR + "forest34.c", "west", 0, 2);
    add_exit(FDIR + "forest36.c", "southwest", 0, 2);
    add_exit(FDIR + "forest37.c", "south", 0, 2);
    add_exit(FDIR + "forest38.c", "southeast", 0, 2);
    
    reset_qualinesti_room();
}

string
my_desc()
{	    
    
    if (skill_check(TP))
    {
    	return "\nIt seems there is a clearing not so far to the east, " +
    	    "maybe you should check it. The trail leads to the northwest.\n";
    }
    
    return "\n";
}

	    