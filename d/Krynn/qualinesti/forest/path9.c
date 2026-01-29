/* path9.c
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
	
    add_exit(FDIR + "path10.c", "southeast", 0, 2);
    add_exit(CDIR + "ambush2.c", "west", 0, 2);
    add_exit(FDIR + "forest17.c", "northwest", 0, 2);
    add_exit(FDIR + "forest18.c", "north", 0, 2);
    add_exit(FDIR + "forest19.c", "northeast", 0, 2);
    add_exit(FDIR + "forest41.c", "southwest", 0, 2);
    add_exit(FDIR + "forest42.c", "south", 0, 2);

    reset_qualinesti_room();
}

string
my_desc()
{	    
    
    if (skill_check(TP))
    {
    	return "\nThere is a small clearing west of here. An animal trail " +
    	    "leads to the southeast.\n";
    }
    
    return "\n";
}

	    