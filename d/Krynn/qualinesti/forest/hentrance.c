/* hentrance.c
 * An entrance to the Qualinesti forest from the Solace-Haven road.
 *
 * Blizzard, 01/2003
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;
object animal;

void
reset_qualinesti_room()
{
    if ( !animal )
    { 
        animal = clone_object(NPC + "rabbit");
        animal->move(TO, 1);
    }
}
    
void
create_forest()
{
    add_my_desc("The trees thin out towards the edge of the forest and " +
        "you notice some animal trails leading into the woods. " +
        "The road to Solace and Haven must be somewhere to the north or " +
        "rather to the northeast? You can not be sure.\n");
	
    add_item(({"trails", "trail", "woods"}),
        "There are a few trails, left probably by animals, leading " +
        "into the forest. One of them goes southeast.\n");
	
    OUTSIDE;
	
    add_exit(FDIR + "path1.c", "southeast", 0, 2);
    add_exit(FDIR + "forest0.c", "south", 0, 2); 
    add_exit(FDIR + "forest1.c", "east", 0, 2); 
    
// Connect with a road Haven-Solace.    
    add_exit("/d/Krynn/haven/road/forest5", "northwest", 0, 2);

    reset_qualinesti_room();
}

	    